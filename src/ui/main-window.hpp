#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../evaluation/tokenizer.hpp"
#include <QMainWindow>
#include <QWidget>
#include <QString>

namespace expression_evaluator { namespace ui {


/* Sticking to the Qt convention to have Ui::MainWindow
 * despite being in another `ui` project namespace */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:     // c-tor & d-tor

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:    // methods

    void displayExpression(const QString &) const;


private slots:      // slots

    void on_evaluatePushButton_clicked();


private:    // member variables

    Ui::MainWindow *ui_; // the designer doesn't like smart pointers :(

};


} }

#endif // MAINWINDOW_HPP
