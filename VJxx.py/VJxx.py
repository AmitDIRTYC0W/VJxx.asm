#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May 12 21:40:08 2022

@author: Amit Goren
"""

import argparse
import cv2
import numpy as np
import numpy.typing as npt
import struct
from lxml import etree

import tqdm

import matplotlib.pyplot as plt

VALUE_BS = 4
ALPHA_BS = 4

class Rectangle:
    def __init__(
        self,
        x0: int,
        y0: int,
        width: int,
        height: int,
        weight: int
    ):
        self.x0 = x0
        self.y0 = y0
        self.width = width
        self.height = height
        self.weight = weight

    def __call__(
        self,
        picture: npt.NDArray[np.int_],
        window: tuple[int, int, float]
    ) -> float:
        x0 = int(self.x0 * window[2] + window[0])
        y0 = int(self.y0 * window[2] + window[1])
        x1 = x0 + int(self.width * window[2])
        y1 = y0 + int(self.height * window[2])

        value = picture[y1, x1] - picture[y0, x1] - picture[y1, x0] + picture[y0, x0]

        return self.weight * value

    def fromXML(rectElement: etree._Element):
        line = rectElement.text

        if line.endswith('.'):
            line = line[:-1]

        x0, y0, width, height, weight = [int(_) for _ in line.split(' ')[-5:]]

        return Rectangle(x0, y0, width, height, weight)

    def pack(self) -> bytes:
        return struct.pack(
            '5b',
            self.x0,
            self.y0,
            self.width,
            self.height,
            self.weight
        )

class WeakClassifier:
    """
    A Haar-like feature classifier
    """

    def __init__(
        self,
        feature: list[Rectangle],
        activations: tuple[float, float],
        threshold: float,
    ):
        self.feature = feature
        self.activations = activations
        self.threshold = threshold #################################

    def __call__(
        self,
        picture: npt.NDArray[np.int_],
        window: tuple[int, int, float]
    ) -> float:
        value = sum(map(lambda _: _(picture, window), self.feature))

        return self.activations[1] if value <= self.threshold else self.activations[0]
    def fromXML(weakClassifierElement: etree._Element, featureElement: etree._Element):
        feature = [
            Rectangle.fromXML(rectElement)
            for rectElement
            in featureElement.findall('./rects/_')
        ]

        threshold = float(
            weakClassifierElement.find('./internalNodes').text.split(' ')[-1]
        )

        activations = tuple(
            [
                float(_)
                for _
                in weakClassifierElement.find('./leafValues').text.split(' ')[-2:]
            ]
        )

        return WeakClassifier(feature, activations, threshold)

    def pack(self) -> bytes:
        return struct.pack(
            'I i 2h',
            len(self.feature),
            int(self.threshold * (1 << VALUE_BS)),
            int(self.activations[0] * (1 << ALPHA_BS)),
            int(self.activations[1] * (1 << ALPHA_BS))
        )

class StrongClassifier:
    """
    A set of weak features, for together they are powerful!
    """

    def __init__(self, classifiers: list[WeakClassifier], threshold: float):
        self.threshold = threshold ######################################
        self.classifiers = classifiers

    def __call__(
        self,
        picture: npt.NDArray[np.int_],
        window: tuple[int, int, float]
    ) -> bool:
        classifyEach = lambda c: c(picture, window)
        classifications = map(classifyEach, self.classifiers)
        return sum(classifications) <= self.threshold

    def fromXML(stageElement: etree._Element, featureElements: etree._Element):
        threshold = float(stageElement.find('./stageThreshold').text)

        weakClassifierElements = stageElement.findall('./weakClassifiers/_')

        classifiers = [
            WeakClassifier.fromXML(weakClassifierElement, featureElement)
            for weakClassifierElement, featureElement
            in zip(weakClassifierElements, featureElements)
        ]

        return StrongClassifier(classifiers, threshold)

    def pack(self) -> bytes:
        return struct.pack(
            'I i',
            len(self.classifiers),
            int(self.threshold * (1 << ALPHA_BS))
        )

class CascadeClassifier:
    """
    A series of strong classifiers, an image must pass all.
    """

    def __init__(
        self,
        stages: list[StrongClassifier],
        filterSize: int
    ):
        """
        Parameters
        ----------
        stages : List[StrongClassifier]
            The cascade stages
        filterSize : int
            The width and the height of the unscaled filter in pixels

        Returns
        -------
        None.
        """

        self.filterSize = filterSize
        self.stages = stages

    def __call__(
            self,
            picture: npt.NDArray[np.uint8],
            window: tuple[int, int, float]
            ) -> bool:
        for i, stage in enumerate(self.stages):
            if not stage(picture, window):
                #if i > 12: print("Blocked at: {}".format(i))
                return False

        return True

    def fromXML(cascadeElement: etree._Element):
        assert cascadeElement.find('./stageType').text == 'BOOST'
        assert cascadeElement.find('./featureType').text == 'HAAR'

        filterSize = int(cascadeElement.find('./width').text)
        assert filterSize == int(cascadeElement.find('./height').text)

        stageElements = cascadeElement.findall('./stages/_')
        assert len(stageElements) == int(cascadeElement.find('stageNum').text)

        featureElements = cascadeElement.findall('./features/_')

        stages = [
            StrongClassifier.fromXML(stageElement, featureElements)
            for stageElement
            in stageElements
        ]

        return CascadeClassifier(stages, filterSize)

    def pack(self) -> bytes:
        return struct.pack(
            'I',
            len(self.stages)
        )

if __name__ == '__main__':
    # Parse arguments.
    argsParser = argparse.ArgumentParser(
        description='Detect faces in pictures',
    )
    argsParser.add_argument(
        'classifier',
        type=argparse.FileType('rb'),
        help='An OpenCV cascade classifier XML file'
    )
    args = argsParser.parse_args()

    # Parse the XML file.
    elementTree = etree.parse(args.classifier)
    cascadeElement = elementTree.find('./cascade')

    cascade = CascadeClassifier.fromXML(cascadeElement)
