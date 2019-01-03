#ifndef STROKECOMBINATION_HPP
#define STROKECOMBINATION_HPP


/**
 * The StrokeCombination class represents a combination of strokes as a vector
 * along with data regarding that combination, such as classification from the CNN
 *
 **/


#include "char-classifier.hpp"
#include "../ui/sketch-widget.hpp"
#include <QPen>
#include <QString>
#include <QImage>
#include <QPoint>
#include <QSize>
#include <vector>

namespace expression_evaluator { namespace eval {


using ui::Stroke;


class StrokeCombination {
private:    // static constants

    static const QPen kPen;

    static const CharClassifier kClassifier;

    static const QString kSaveFilename;


public:     // c-tor

    StrokeCombination(const std::vector<Stroke> &, const QSize &);

    StrokeCombination() {}

    bool operator<(const StrokeCombination &other) const {
        return this->average_coordinate_ < other.average_coordinate_;
    }


public:     // getters

    const std::vector<Stroke> &getStrokes() const { return strokes_; }

    char getPrediction() const { return prediction_; }

    double getConfidence() const { return confidence_; }


private:    // static methods

    static void drawLine(QImage *, const QPoint &, const QPoint &);

    static void drawStroke(QImage *, const Stroke &);


private:    // methods

    void computeAverageCoordinate();

    void feedToCNN();


private:    // member variables

    std::vector<Stroke> strokes_;

    QSize img_size_;

    int average_coordinate_ = 0;

    char prediction_ = 0;

    double confidence_ = 0;

};


} }


#endif // STROKECOMBINATION_HPP
