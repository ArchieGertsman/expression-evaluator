#ifndef TST_TEST_HPP
#define TST_TEST_HPP

#include "../src/evaluation/char-classifier.hpp"
#include <QtTest>
#include <QString>
#include <QMap>

namespace expression_evaluator { namespace test {


using eval::CharClassifier;


class Test : public QObject {

    Q_OBJECT

private:

    static const CharClassifier kClassifier;

    static const QString kResDir;

    static const QMap<char, QString> kOperatorNameMap;

    static QMap<char, QString> createMap() {
        QMap<char, QString> m;
        m['+'] = "plus";
        m['-'] = "minus";
        m['*'] = "multiply";
        m['/'] = "divide";
        return m;
    }


private:

    static char classify(const QString &);


private slots:

    /* feeds training data of digits 0 through 9 into CNN and
     * tests to see that the CNN correctly classifies the data
     * (as it probably should, since it was trained on that data)
     */
    void digitClassification() const;

    /* same as `digitClassification` but with operators +, -, *, and / */
    void operatorClassification() const;


};


} }

#endif // TST_TEST_HPP
