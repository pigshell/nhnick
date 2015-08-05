TARGET = qvnc

CONFIG += qpa/genericunixfontdatabase

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QVNCIntegrationPlugin
load(qt_plugin)

QT += core-private gui-private platformsupport-private network

SOURCES =   main.cpp \
            qvncintegration.cpp \
            qvncscreen.cpp \
            qvncserver.cpp \
            qvnccursor.cpp
HEADERS =   qvncintegration.h \
            qvncscreen.h \
            qvncserver.h \
            qvnccursor.h

OTHER_FILES += vnc.json
