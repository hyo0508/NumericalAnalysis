import cv2
import numpy as np
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("width", type=int)
    parser.add_argument("height", type=int)
    parser.add_argument("-o", "--output", type=str, required=True)
    args = parser.parse_args()

    inputfile = "Images/1280x720.png"
    outputfile = args.output

    new_height = args.height
    new_width = args.width

    img = cv2.imread(inputfile)
    height, width, _ = img.shape

    new_img = np.zeros((new_height, new_width, 3), dtype=np.uint8)

    x_rate = new_width / width
    y_rate = new_height / height

    for x in range(0, new_width):
        for y in range(0, new_height):
            ix = np.clip(int(x / x_rate), 0, width - 2)
            iy = np.clip(int(y / y_rate), 0, height - 2)

            x1 = x / x_rate - ix
            y1 = y / y_rate - iy
            x2 = 1 - x1
            y2 = 1 - y1

            w1 = x2 * y2
            w2 = x1 * y2
            w3 = x2 * y1
            w4 = x1 * y1

            new_img[y, x, :] = np.clip(
                w1 * img[iy, ix, :]
                + w2 * img[iy, ix + 1, :]
                + w3 * img[iy + 1, ix, :]
                + w4 * img[iy + 1, ix + 1, :],
                0,
                255,
            )

    cv2.imwrite(outputfile, new_img)
    print(f"successfully saved : {outputfile}")
