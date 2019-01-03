#include "char-classifier.hpp"

#include <QString>
#include <utility>

namespace expression_evaluator { namespace eval {


/* static constants */

const char *CharClassifier::kPythonPath =
    "/Users/archiegertsman/Desktop/CS126/Final Project/finalproject-ArchieGertsman/src/classification";

const char *CharClassifier::kClassifierModuleName = "classifier";

const char *CharClassifier::kClassifierClassName = "Classifier";

const char *CharClassifier::kClassifyFunctionName = "classify";


/* c-tor and d-tor */

CharClassifier::CharClassifier() {
    Py_Initialize();

    setPath();

    PyObject *module_name = PyUnicode_FromString(kClassifierModuleName);

    PyObject *module = PyImport_Import(module_name);
    Py_DecRef(module_name);

    PyObject *dict = PyModule_GetDict(module);
    Py_DecRef(module);

    PyObject *python_class = PyDict_GetItemString(dict, kClassifierClassName);
    Py_DecRef(dict);

    if (PyCallable_Check(python_class)) {
        classifier_instance_ = PyObject_CallObject(python_class, nullptr);
    }

    Py_DecRef(python_class);
}


CharClassifier::~CharClassifier() {
    Py_DecRef(classifier_instance_);
    Py_Finalize();
}


/* methods */

std::pair<char, double> CharClassifier::classify(const QString &img_path) const {
    if (!classifier_instance_) {
        return std::make_pair(-1, -1);
    }

    PyObject *result = PyObject_CallMethod(
                classifier_instance_,
                kClassifyFunctionName, "s",
                img_path.toLocal8Bit().data());

    // get prediction
    PyObject *prediction_ptr = PyTuple_GetItem(result, Result::kPredictionIdx);

    char prediction = static_cast<char>(PyLong_AsLong(prediction_ptr));

    Py_DecRef(prediction_ptr);


    // get confidence
    PyObject *confidence_ptr = PyTuple_GetItem(result, Result::kConfidenceIdx);

    double confidence = PyFloat_AsDouble(confidence_ptr);

    Py_DecRef(confidence_ptr);


    Py_DecRef(result);

    return std::make_pair(prediction, confidence);
}


void CharClassifier::setPath() {
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString(kPythonPath));
    Py_DecRef(sys_path);
}


} }
