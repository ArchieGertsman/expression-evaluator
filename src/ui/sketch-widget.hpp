#ifndef SKETCHWIDGET_HPP
#define SKETCHWIDGET_HPP

/**
 * The SketchWidget class is a custom QWidget in which the user draws a sketch
 * with a pen tool
 *
 * sources:
 * https://bit.ly/2Knx1TB
 **/

#include <QWidget>
#include <QMouseEvent>
#include <QPen>
#include <QPoint>
#include <QSize>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QImage>
#include <vector>


namespace expression_evaluator { namespace ui {


typedef QVector<QPoint> Stroke;


class SketchWidget : public QWidget {

    Q_OBJECT

public:     // static constants
    static const QPen kPen;

public:     // c-tor
    explicit SketchWidget(QWidget *parent = nullptr);


public slots:       // slots
    void clearSketch();


private:        // methods
    void drawLineTo(const QPoint &);

    void resizeSketch(const QSize &);


protected:      // overridden QWidget methods
    void mousePressEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;

    void paintEvent(QPaintEvent *) override;

    void resizeEvent(QResizeEvent *) override;


public:     // getters
    const std::vector<Stroke> &getStrokesList() const { return strokes_list_; }


private:        // member variables
    QImage sketch_;

    QPoint last_point_;

    std::vector<Stroke> strokes_list_;

    bool is_sketching_ = false;

};


} }

#endif // SKETCHWIDGET_HPP
