QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    test.cpp \
    ../src/evaluation/char-classifier.cpp

HEADERS += \
    test.hpp \
    ../src/evaluation/char-classifier.hpp

INCLUDEPATH += /Library/Frameworks/Python.framework/Versions/3.7/include/python3.7m

LIBS += -L/Library/Frameworks/Python.framework/Versions/3.7/lib -lpython3.7m
