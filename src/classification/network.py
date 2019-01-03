"""
CNN class representing a convolutional neural network (CNN) which will be
trained to classify characters in CharacterDataset.CHARSET


Network structure:

input -> conv layer 1 -> pool layer 1 -> conv layer 2 -> pool layer 2
-> fully connected layer 1 -> fully connected layer 2 
-> fully connected layer 3 -> outputs


sources:
https://bit.ly/2nPU3rN
https://bit.ly/2KghwNe
"""

import torch
import torch.nn as nn
import torch.nn.functional as F

class CNN(nn.Module):

    W_INPUT = 32
    H_INPUT = 32

    def __init__(self):
        super(CNN, self).__init__()

        from character_dataset import CharacterDataset

        self.conv1 = nn.Conv2d(1, 6, 5)
        self.pool1 = nn.MaxPool2d(2, 2)

        self.conv2 = nn.Conv2d(6, 16, 5)
        self.pool2 = nn.MaxPool2d(2, 2)
        
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, len(CharacterDataset.CHARSET))


    def forward(self, x):
        x = F.relu(self.pool1(self.conv1(x)))
        x = F.relu(self.pool2(self.conv2(x)))
        x = x.view(-1, 16 * 5 * 5)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.log_softmax(self.fc3(x), dim=1)
        return x
