#include "main-window.hpp"

#include "ui_mainwindow.h"
#include "../lib/exprtk.hpp"
#include <QMainWindow>
#include <QWidget>
#include <QString>


namespace expression_evaluator { namespace ui {


/* c-tor and d-tor */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    this->connect(
            ui_->clearSketchPushButton, SIGNAL(clicked()),
            ui_->sketchWidget,          SLOT(clearSketch()));
}


MainWindow::~MainWindow() {
    delete ui_;
}


/* push-button handlers */

void MainWindow::on_evaluatePushButton_clicked() {
    const auto &strokes_list = ui_->sketchWidget->getStrokesList();
    const auto &img_size = ui_->sketchWidget->size();

    const auto &tokens = eval::Tokenizer(strokes_list, img_size).getTokens();

    QString expr_str;

    for (char tok : tokens) {
        expr_str += tok;
    }

    this->displayExpression(expr_str);
}


/* methods */

void MainWindow::displayExpression(const QString &expr_str) const {
    ui_->expressionLabel->setText(QString("in: ") + expr_str);

    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    if (!parser.compile(expr_str.toUtf8().constData(), expr)) {
        ui_->resultLabel->setText("error");
        return;
    }

    double result = expr.value();

    ui_->resultLabel->setNum(result);
}


} }
