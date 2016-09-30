TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    xml.cpp \
    xsd.cpp

HEADERS += \
    xml.h \
    xsd.h \
    xmlschema.h

LIBS += -lxml2

DISTFILES += \
    assets/config.xml \
    assets/schema.xsd
