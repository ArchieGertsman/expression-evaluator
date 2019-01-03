'''
Classifier class which classifies skeches as characters from the CHARSET
'''

import torch

class Classifier:

    def __init__(self, model_path='/Users/archiegertsman/Desktop/CS126/Final Project/finalproject-ArchieGertsman/src/classification/res/model.pt'):
        from network import CNN

        # load a model
        self.model = CNN()
        self.model.load_state_dict(torch.load(model_path))
        self.model.eval()


    def classify(self, img_path):
        from character_dataset import CharacterDataset
        import image_utils as iu

        # load image
        img = iu.read_image_as_tensor(img_path)

        # make prediction using model
        output = self.model(img)
        prediction_idx = torch.argmax(output).item()
        confidence = torch.max(output).item()

        # returns ascii value of predicted character
        return (ord(CharacterDataset.CHARSET[prediction_idx]), confidence)
