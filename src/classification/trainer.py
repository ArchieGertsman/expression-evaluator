import torch
import torch.nn as nn
import torch.optim as optim
from network import CNN
from character_dataset import CharacterDataset

class Trainer:

    def __init__(self, num_epochs=5, batch_size=4, lr=0.001):
        self.num_epochs = num_epochs

        trainset = CharacterDataset()
        self.trainloader = torch.utils.data.DataLoader(
            trainset, batch_size=batch_size, shuffle=True, num_workers=2)

        self.net = CNN()
        self.criterion = nn.CrossEntropyLoss()
        self.optimizer = optim.SGD(self.net.parameters(), lr=lr, momentum=0.9)

    
    def train(self):
        for epoch in range(self.num_epochs):
            for i, data in enumerate(self.trainloader, 0):
                # get the inputs
                inputs, labels = data

                # zero the parameter gradients
                self.optimizer.zero_grad()

                # forward + backward + optimize
                outputs = self.net(inputs)
                loss = self.criterion(outputs, labels)
                loss.backward()
                self.optimizer.step()


    def test_model_against_trainset(self):
        correct = 0
        total = 0

        with torch.no_grad():
            for data in self.trainloader:
                images, labels = data

                outputs = self.net(images)
                _, predicted = torch.max(outputs.data, 1)

                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        return correct/total


    def save_model(self, filepath='res/model.pt'):
        torch.save(self.net.state_dict(), filepath)
