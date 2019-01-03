# Expression Evaluator

Expression Evaluator is a desktop application in which the user can sketch a simple mathematical expression, and the application will display the expression's result.

![Image of Expression Evaluator](https://i.imgur.com/C34x9Bz.png)

## Usage

In order to use Expression Evaluator, the following software must be installed on your system:

*C++*
- Qt Creater with Qt 5 framework

*Python*
- Python 3
- PyTorch
- Numpy
- OpenCV

Once these requirements are met, you can then clone this repository. Then you must change some hard-coded directories within the project:

1. in `src/evaluation/char-classifier.cpp`, change `kPythonPath` to your absolute path of `src/classification`
2. in `tests/test.cpp`, change `kResDir` to your absolute path of `tests/res` 
3. in `src/classification/classifier.py`, change `model_path` in the constructor to your absolute path of `src/classification/res/model.pt`