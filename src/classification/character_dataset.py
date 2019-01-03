'''
dataset representing all of the training data for digits 0 through 9 and 
operators +, -, *, and /

sources:
https://bit.ly/2PCFYOJ
https://bit.ly/2ziauDe
'''

import torch
from torch.utils.data.dataset import Dataset
import cv2
import numpy as np
import tarfile

class CharacterDataset(Dataset):

    # relative to the res/ folder
    CURATED_PATH = 'curated/'

    TAR_PATH = 'res/curated.tar.gz'

    CHARSET = '0123456789+-*/'


    def __init__(self):
        self.images = [] # image tensors
        self.labels = [] # ranges from 0 to 13 (inclusive)

        import image_utils as iu

        tar = tarfile.open(CharacterDataset.TAR_PATH, "r:gz")

        for i in range(len(CharacterDataset.CHARSET)):
            # character which we are sampling
            c = CharacterDataset.CHARSET[i]

            # directory containing all the training data for this character
            directory = CharacterDataset.CURATED_PATH + str(ord(c)) + '/'

            # list of all the files in the directory
            img_files_list = CharacterDataset.construct_img_files_list(tar, directory)

            for f in img_files_list:
                # convert image data to an ndarray
                img = np.asarray(bytearray(f.read()))
                img = cv2.imdecode(img, 0)

                img = iu.construct_tensor_from_ndarray(img)

                # add image and corresponding label to dataset
                self.images += [img]
                self.labels += [i]


    @staticmethod
    def construct_img_files_list(tar, directory):
        return [tar.extractfile(member) for member in tar.getmembers() \
            if member.name.startswith(directory) \
            and len(member.name) > len(directory)]


    def __getitem__(self, index):
        return (self.images[index], self.labels[index])


    def __len__(self):
        return len(self.images)
