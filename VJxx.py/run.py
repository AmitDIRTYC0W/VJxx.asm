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
    argsParser.add_argument(
        'picture',
        type=argparse.FileType('rb'),
        help='The picture to find the faces in'
    )
    args = argsParser.parse_args()

    # Parse the XML file.
    elementTree = etree.parse(args.classifier)
    cascadeElement = elementTree.find('./cascade')

    cascade = CascadeClassifier.fromXML(cascadeElement)

    # Open the picture.
    picture = np.frombuffer(args.picture.read(), dtype=np.uint8)
    picture = cv2.imdecode(picture, cv2.IMREAD_GRAYSCALE)
    toplot = np.array(picture)

    # Pre-process it.
    picture = cv2.integral(picture)

    picture_dim = min(picture.shape)
    for size in range(int(0.4 * picture_dim), picture_dim, int(0.05 * picture_dim)):
        scale = size / cascade.filterSize
        for y in tqdm.trange(0, picture.shape[0] - size, int(0.03 * picture_dim)):
            for x in range(0, picture.shape[1] - size, int(0.03 * picture_dim)):
                if cascade(picture, (x, y, scale)):
                    print(x, y, size)
                    toplot = cv2.rectangle(toplot, (x, y), (x + size, y + size), (255, 0, 0), 2)

    plt.imshow(toplot)
    plt.show()

# TODO rename this file