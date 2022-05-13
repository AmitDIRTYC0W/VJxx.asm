#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May 13 10:48:25 2022

@author: durden
"""

import argparse
from lxml import etree

import VJxx

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
        type=argparse.FileType('wb'),
        help='The output file to be incorporated into the binary'
    )
    args = argsParser.parse_args()

    # Parse the XML file.
    elementTree = etree.parse(args.input)
    cascadeElement = elementTree.find('./cascade')

    cascade = VJxx.CascadeClassifier.fromXML(cascadeElement)

    print(cascade.stages[0].classifiers[0].feature[0].weight)
