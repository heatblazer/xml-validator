TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

LIBS += -lxml2

SOURCES += main.cpp \
    xml.cpp \
    xsd.cpp \
    utils.cpp

HEADERS += \
    xml.h \
    xsd.h \
    utils.h

LIBS += -lxml2

DISTFILES += \
    assets/config.xml \
    assets/schema.xsd \
    README.md
