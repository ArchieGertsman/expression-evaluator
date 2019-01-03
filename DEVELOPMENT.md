## Week 1
### Python
- Began following PyTorch's [tutorials on neural networks](https://pytorch.org/tutorials/beginner/blitz/neural_networks_tutorial.html#sphx-glr-beginner-blitz-neural-networks-tutorial-py)
- Modelled a convolutional neural network (CNN) using PyTorch for classifying digits in a class called `CNN`
- Found training data for characters: digits 0-9 and operators +, -, *, /
- Created a class called `CharacterDataset` for reading training data in a format compatible with PyTorch ([Dataset class](https://pytorch.org/docs/stable/data.html#torch.utils.data.Dataset)). Reads from unzipped folders
### Other
- Read first two chapters of Michael Nielsen's [_Neural Networks and Deep Learning_](http://neuralnetworksanddeeplearning.com/) to understand the fundemental concepts of neural networks

## Week 2
### C++
- Decided to use [Qt](https://www.qt.io/) instead of OpenFrameworks for the GUI
- Began to develop a windowed application 
- Implemented a custom [QWidget](http://doc.qt.io/qt-5/qwidget.html) in which the user could sketch with a pen
- Added a functional "Clear Sketch" button
### Python
- Updated `CharacterDataset` to read from a tar file rather than extracted folders
- Updated `CNN` class with a different network structure and put the outputs of the network through the `log_softmax` function before finally returning them

## Week 3
### C++
- Followed [this tutorial](https://docs.python.org/3/extending/embedding.html) to successfully embedded Python 2 in C++
- Eventually embedded Python 3 in C++
- Created a wrapper class for the Python character classifier

### Python
- Created a trainer which trains the network and saves the trained model to a file
- Created a `Classifier` class which loads a model and classifies characters (doesn't work properly yet)

## Week 4
### C++
- Created `Tokenizer` class along with other related classes for segmenting the user's sketch into separate tokens. I like to refer to this as "tokenization"
- Devised and implemented a fairly simple, innacurate tokenization algorithm (v1.0) by keeping track of all of the user's pen strokes
- Divised and implemented a more accurate but buggy tokenization algorithm (v2.0) which considers all the the possible combinations of strokes and uses the network to determine which ones are the most likely to be sensible
- Got rid of bugs in v2.0. Let's call this v2.1
- Optimized v2.1 by looking at fewer combinations. Let's call this v2.2
- Added testing to test that the network can correctly classify some of the data on which it was trained

### Python
- Created a `Trainer` class which trains and saves a model
- Created the `image_utils` module which contains utilities for converting a sketch into an image compatible with the network
- Ran the trainer to generate a somewhat accurate model
- Ran the trainer with more epochs and a larger batch size to generate a more accurate model