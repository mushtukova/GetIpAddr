QT += core
QT -= gui

CONFIG += c++11

TARGET = snmp_test
CONFIG += console
CONFIG -= app_bundle

LIBS += Snmpapi.lib

TEMPLATE = app

SOURCES += main.cpp \
    mysnmp.cpp

HEADERS += \
    mysnmp.h \
    defines.h
