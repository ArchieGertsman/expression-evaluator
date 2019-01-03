#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/**
 * Wrapper class for Python Classifier class
 *
 * sources:
 * https://bit.ly/2FZjvXI
 **/

#include <Python.h>
#include <QString>
#include <utility>

namespace expression_evaluator { namespace eval {


class CharClassifier {
private:    // static constants

    static const char *kPythonPath;

    static const char *kClassifierModuleName;

    static const char *kClassifierClassName;

    static const char *kClassifyFunctionName;

    enum Result {
        kPredictionIdx = 0,
        kConfidenceIdx = 1
    };


public:     // c-tors & d-tor

    CharClassifier();

    ~CharClassifier();


public:     // methods

    std::pair<char, double> classify(const QString &img_path) const;


public:     // getters

    bool available() const { return classifier_instance_; }


private:    // static functions

    static void setPath();


private:    // member variables

    PyObject *classifier_instance_ = nullptr;

};


} }

#endif // CLASSIFIER_H
