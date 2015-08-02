TARGET = qvnc

CONFIG += qpa/genericunixfontdatabase

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QVNCIntegrationPlugin
load(qt_plugin)

QT += core-private gui-private platformsupport-private

SOURCES =   main.cpp \
            qvncintegration.cpp \
            qvncbackingstore.cpp
HEADERS =   qvncintegration.h \
            qvncbackingstore.h

OTHER_FILES += vnc.json
