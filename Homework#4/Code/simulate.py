import sys
import os
import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':

    num = 100
    if len(sys.argv) > 1:
        num = sys.argv[1]
    os.system("rm ./result/uniform.result")
    os.system("rm ./result/gaussian.result")
    os.system(f"./uniform {num} > result/uniform.result")
    os.system(f"./gaussian {num} > result/gaussian.result")

    uniform_values = []
    with open('result/uniform.result') as f:
        for line in f:
            uniform_values.append(float(line))
    plt.figure(1)
    plt.hist(uniform_values, bins=100)
    plt.title('uniform')

    gaussian_values = []
    with open('result/gaussian.result') as f:
        for line in f:
            gaussian_values.append(float(line))
    plt.figure(2)
    plt.hist(gaussian_values, bins=100)
    plt.title('gaussian')

    plt.show()