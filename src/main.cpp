#include "ui/main-window.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    expression_evaluator::ui::MainWindow w;
    w.show();

    return a.exec();
}
