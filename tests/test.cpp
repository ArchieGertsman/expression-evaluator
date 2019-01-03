#include "test.hpp"

#include <QtTest>
#include <QString>
#include <QMap>

namespace expression_evaluator { namespace test {


/* static constants */

const CharClassifier Test::kClassifier = CharClassifier();

const QString Test::kResDir =
        "/Users/archiegertsman/Desktop/CS126/Final Project/finalproject-ArchieGertsman/tests/res/";

const QMap<char, QString> Test::kOperatorNameMap = Test::createMap();


/* static functions */

char Test::classify(const QString &symbol) {
    const auto &result = kClassifier.classify(kResDir + symbol + ".png");
    char prediction = static_cast<char>(result.first);
    return prediction;
}


/* test methods */

void Test::digitClassification() const {
    for (char c = '0'; c <= '9'; ++c) {
        char prediction = classify(QString(c));
        QVERIFY(prediction == c);
    }
}


void Test::operatorClassification() const {
    for (char c : kOperatorNameMap.keys()) {
        char prediction = classify(kOperatorNameMap[c]);
        QVERIFY(prediction == c);
    }
}


} }

QTEST_APPLESS_MAIN(expression_evaluator::test::Test)
