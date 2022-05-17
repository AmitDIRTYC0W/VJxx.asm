#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May 13 10:48:25 2022

@author: durden
"""

import argparse
from lxml import etree
import os

import VJxx

def isDirectory(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)

if __name__ == '__main__':
    # Parse arguments.
    argsParser = argparse.ArgumentParser(
        description='Convert OpenCV cascade classifiers XML files to VJxx-compatible binaries',
    )
    argsParser.add_argument(
        'input',
        type=argparse.FileType('rb'),
        help='The input OpenCV cascade classifier XML file'
    )
    argsParser.add_argument(
        'output',
        type=isDirectory,
        help='The VJxx src directory to write the output to'
    )

    args = argsParser.parse_args()

    # Parse the XML file.
    elementTree = etree.parse(args.input)
    cascadeElement = elementTree.find('./cascade')

    cascade = VJxx.CascadeClassifier.fromXML(cascadeElement)

    with open('{}/cascade_classifier.vjxx.bin'.format(args.output), 'wb') as f:
        f.write(cascade.pack())

    strongClassifiers = cascade.stages
    with open('{}/strong_classifiers.vjxx.bin'.format(args.output), 'wb') as f:
        f.write(b''.join([c.pack() for c in strongClassifiers]))

    weakClassifiers = [wc for sc in strongClassifiers for wc in sc.classifiers]
    with open('{}/weak_classifiers.vjxx.bin'.format(args.output), 'wb') as f:
        f.write(b''.join([c.pack() for c in weakClassifiers]))

    areas = [a for wc in weakClassifiers for a in wc.feature]
    with open('{}/area.vjxx.bin'.format(args.output), 'wb') as f:
        f.write(b''.join([a.pack() for a in areas]))
