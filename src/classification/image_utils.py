'''
Utilities for reading images and transforming them into Tensors

sources:
https://bit.ly/2qTUhQ3
https://bit.ly/2S5KthH
https://bit.ly/2RDUWAV
https://bit.ly/2QlF4Xv
'''

import cv2
import torch
import numpy as np
from network import CNN

def construct_tensor_from_ndarray(img):
    img = cv2.resize(img, (CNN.W_INPUT, CNN.H_INPUT), interpolation=cv2.INTER_AREA)
    img = img/255 # normalize array values between 0 and 1
    img = img[np.newaxis, :]
    img = torch.from_numpy(img).float()

    return img


def read_image_as_tensor(img_path):
    # read image as grayscale
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)

    # convert to black and white
    (_, img) = cv2.threshold(img, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

    # crop out whitespace
    coords_set = cv2.findNonZero(img)
    x, y, w, h = cv2.boundingRect(coords_set)
    img = img[y:y+h, x:x+w]

    # add padding
    BLACK = [0, 0, 0]
    THICKNESS = 10
    img = cv2.copyMakeBorder(img, 
        THICKNESS, THICKNESS, THICKNESS, THICKNESS, 
        cv2.BORDER_CONSTANT, value=BLACK)

    # convert to PyTorch Tensor
    img = construct_tensor_from_ndarray(img)
    img = img.view(1, 1, CNN.W_INPUT, CNN.H_INPUT)

    return img