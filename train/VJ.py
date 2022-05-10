import argparse
from enum import IntEnum
import numpy as np
import numpy.typing as npt
import struct

NO_WEAK_CLASSIFIERS = 128
"""This constant defines the amount of weak classifiers in a strong one.
"""

SCALE_RESOLUTION = 3
"""2 to the power of this constant is proportional to the Haar-features scaling
precision.
"""

class WeakClassifier:
    """This class represents a Haar-like feature classifier.
    """
    class FeatureType(IntEnum):
        X2 = 0
        Y2 = 1
        X3 = 2
        Y3 = 3
        X2Y2 = 4

    def __init__(
        self,
        alpha: int,
        threshold: int,
        parity: int,
        featureType: FeatureType,
        relative_x0: int, relative_y0: int,
        width: int, height: int
    ):
        """
        Parameters
        ----------
        alpha : int
            Alpha is the amount of influence of the feature.
        threshold : int
            The threshold is the minimum threshold needed to activate the
            feature.
        parity : int
            Parity must be +1 or -1, it controls whether the activation needs
            to be greater or less than the threshold, accordingly.
        featureType : FeatureType
             This defines type of the Haar-feature.
        relative_x0 : int
            This is distance between the left side of the filter to the left
            side of the feature in pixels, multiplied by 2 to the
            SCALE_RESOLUTION.
        relative_y0 : int
            This is distance between the top side of the filter to the top
            side of the feature in pixels, multiplied by 2 to the
            SCALE_RESOLUTION.
        width : int
            This is width of the feature in pixels, multiplied by 2 to the
            SCALE_RESOLUTION.
        height : int
            This is width of the feature in pixels, multiplied by 2 to the
            SCALE_RESOLUTION.

        Returns
        -------
        None.

        """
        self.alpha = alpha
        self.threshold = threshold
        self.parity = parity
        self.featureType = featureType
        self.relative_x0, self.relative_y0 = relative_x0, relative_y0
        self.width, self.height = width, height

        match featureType:
            case self.FeatureType.X2:
                self.feature = haar_x2
            case self.FeatureType.Y2:
                self.feature = haar_y2
            case self.FeatureType.X3:
                self.feature = haar_x3
            case self.FeatureType.Y3:
                self.feature = haar_y3
            case self.FeatureType.X2Y2:
                self.feature = haar_x2y2

    def classify(
        self,
        picture: npt.NDArray[np.int_],
        window_x0: int, window_y0: int,
        scale: int
    ) -> bool:
        """This function predicts whether a given area is a face or not.

        It is akin to vjxx_weak_classify.

        Parameters
        ----------
        picture : npt.NDArray[np.int_]
            picture must be the integral image of the picture.
        window_x0 : int
            This provides the X coordinate of the left side of the filter
            window in pixels.
        window_y0 : int
            This provides the Y coordinate of the top side of the filter window
            in pixels.
        window_scale : int
            This, divided by 2 to the power of SCALE_RESOLUTION defines the
            coefficient of the width and the height of the filter.

        Returns
        -------
        bool
            It returns whether the classifier is activated or not.
        """
        absolute_x0 = window_x0 + int(scale * self.relative_x0) >> SCALE_RESOLUTION
        aboslute_y0 = window_y0 + int(scale * self.relative_y0) >> SCALE_RESOLUTION
        width = int(scale * self.width) >> SCALE_RESOLUTION
        height = int(scale * self.height) >> SCALE_RESOLUTION

        value = self.feature(picture, absolute_x0, aboslute_y0, width, height)

        return value * self.parity > self.threshold * self.parity * width * height


    def pack(self) -> bytes:
        """This function stores self in a binary format. The format is
        compatible with vjxx_weak_classifier_t.

        Returns
        -------
        bytes
            The classifier in a format compatible with the memory
            representation of vjxx_weak_classifier_t.
        """
        return struct.pack(
            'h i ? b 4I',
            self.alpha,
            self.threshold,
            self.parity,
            self.featureType,
            self.x0,
            self.y0,
            self.width,
            self.height
        )

class StrongClassifier:
    """This class represents a set of weak features, for together they are
    powerful!
    """

    def __init__(self, classifiers: list[WeakClassifier]):
        assert len(classifiers) == NO_WEAK_CLASSIFIERS
        self.classifiers = classifiers

    #def classify(self, picture):


    def pack(self) -> bytes:
        """This function stores self in a binary format that is compatible with
        vjxx_strong_classifier_t.

        Returns
        -------
        bytes
            The classifier in a format compatible with the memory
            representation of vjxx_strong_classifier_t.
        """
        return b''.join(map(WeakClassifier.pack, self.classifiers))

if __name__ == '__main__':
    argsparser = argparse.ArgumentParser(description='Train VJxx models.')
    argsparser.add_argument(
        'output',
        type=argparse.FileType('wb'),
        help='The output file to be incorporated into the binary'
    )
    args = argsparser.parse_args()

    w = WeakClassifier(0, 0, 1, WeakClassifier.FeatureType.X2, 0xFFFFFFFF, 0, 0x69, 69)
    args.output.write(w.pack() * 128)
