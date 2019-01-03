#include "sketch-widget.hpp"

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QRect>
#include <QSize>
#include <QPoint>

namespace expression_evaluator { namespace ui {


/* static constants */

const QPen SketchWidget::kPen = QPen(
            {Qt::green},
            2, // thickness
            Qt::SolidLine,
            Qt::RoundCap,
            Qt::RoundJoin);


/* c-tor */

SketchWidget::SketchWidget(QWidget *parent) : QWidget(parent) {
    this->setAttribute(Qt::WA_StaticContents);
    sketch_ = QImage({this->size()}, QImage::Format::Format_ARGB32);
    sketch_.fill(Qt::transparent);
}


/* overrides */

void SketchWidget::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        last_point_ = e->pos();
        is_sketching_ = true;
        strokes_list_.push_back(Stroke());
    }
}


void SketchWidget::mouseMoveEvent(QMouseEvent *e) {
    if (this->is_sketching_ && (e->buttons() & Qt::LeftButton)) {
        this->drawLineTo(e->pos());
        last_point_ = e->pos();
        strokes_list_[strokes_list_.size()-1].push_back(e->pos());
    }
}


void SketchWidget::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        this->drawLineTo(e->pos());
        strokes_list_[strokes_list_.size()-1].push_back(e->pos());

        is_sketching_ = false;
    }
}


void SketchWidget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawImage(e->rect(), sketch_, e->rect());
}


void SketchWidget::resizeEvent(QResizeEvent *e) {
    this->resizeSketch(this->size());
    QWidget::resizeEvent(e);
}


/* slots */

void SketchWidget::clearSketch() {
    strokes_list_.clear();
    sketch_.fill(Qt::transparent);
    this->update();
}


/* other methods */

void SketchWidget::drawLineTo(const QPoint &end_point) {
    QPainter painter(&sketch_);
    painter.setPen(kPen);
    painter.drawLine(last_point_, end_point);

    int r = (kPen.width() / 2) + 2; // radius

    this->update(QRect(last_point_, end_point)
                 .normalized()
                 .adjusted(-r, -r, r, r));
}


void SketchWidget::resizeSketch(const QSize &new_size) {
    if (sketch_.size() == new_size) {
        return;
    }

    QImage new_sketch(new_size, QImage::Format_ARGB32);
    new_sketch.fill(Qt::transparent);

    QPainter painter(&new_sketch);
    painter.drawImage(QPoint(0, 0), sketch_);
    sketch_ = new_sketch;
}


} }
