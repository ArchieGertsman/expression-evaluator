#include "stroke-combination.hpp"

#include <QPainter>
#include <QSize>
#include <QImage>
#include <QPoint>
#include <vector>
#include <utility>
#include <QDebug>

namespace expression_evaluator { namespace eval {


/* static const variables */

const QPen StrokeCombination::kPen = QPen(
            {Qt::green},
            2, // thickness
            Qt::SolidLine,
            Qt::RoundCap,
            Qt::RoundJoin);

const CharClassifier StrokeCombination::kClassifier = CharClassifier();

const QString StrokeCombination::kSaveFilename = "sketch.png";


/* c-tor */

StrokeCombination::StrokeCombination(
        const std::vector<Stroke> &strokes,
        const QSize &img_size) :
    strokes_(strokes),
    img_size_(img_size)
{
    this->computeAverageCoordinate();
    this->feedToCNN();
}


/* methods */

void StrokeCombination::computeAverageCoordinate() {
    int x_avg = 0;
    int y_avg = 0;
    int num_points = 0;

    for (const auto &stroke : strokes_) {
        for (const auto &p : stroke) {
            x_avg += p.x();
            y_avg += p.y();

            ++num_points;
        }
    }

    x_avg /= num_points;
    y_avg /= num_points;

    average_coordinate_ = (x_avg + y_avg) / 2;
}


void StrokeCombination::feedToCNN() {
    QImage img({img_size_}, QImage::Format::Format_ARGB32);
    img.fill(Qt::transparent);

    for (const auto &stroke : strokes_) {
        drawStroke(&img, stroke);
    }

    img.save(kSaveFilename);

    const std::pair<char, double> &result =
            kClassifier.classify(kSaveFilename);

    prediction_ = result.first;
    confidence_ = result.second;

    qDebug() << prediction_ << ", " << confidence_;
}


void StrokeCombination::drawLine(
        QImage *src_img,
        const QPoint &p1,
        const QPoint &p2)
{
    QPainter painter(src_img);
    painter.setPen(kPen);
    painter.drawLine(p1, p2);
}


void StrokeCombination::drawStroke(QImage *src_img, const Stroke &stroke) {
    const auto &points = stroke;
    for (auto i = 0; i < points.size() - 1; ++i) {
        drawLine(src_img, points[i], points[i+1]);
    }
}


} }
