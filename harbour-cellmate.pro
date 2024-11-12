# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-cellmate

CONFIG += sailfishapp
CONFIG += c++1z

QT = core dbus network positioning
PKGCONFIG += qofono-qt5 qofonoext mlite5

SOURCES += src/harbour-cellmate.cpp \
    CellWatcher.cpp \
    RadioSignal.cpp \
    gsmcellwatcher.cpp \
    gsmradiosignal.cpp \
    jsonloutput.cpp \
    locationprovider.cpp \
    logrecorder.cpp \
    ltecellwatcher.cpp \
    lteradiosignal.cpp \
    nrradiosignal.cpp \
    servingcellwatcher.cpp \
    umtscellwatcher.cpp \
    wcdmaradiosignal.cpp

DISTFILES += qml/harbour-cellscan.qml \
    icons/108x108/harbour-cellmate.png \
    icons/128x128/harbour-cellmate.png \
    icons/172x172/harbour-cellmate.png \
    icons/86x86/harbour-cellmate.png \
    qml/cover/CoverPage.qml \
    qml/pages/FinishRecording.qml \
    qml/pages/GSMSignals.qml \
    qml/pages/InfoField.qml \
    qml/pages/LTECells.qml \
    qml/pages/LTEServingCell.qml \
    qml/pages/LTESignals.qml \
    qml/pages/ServingCell.qml \
    qml/pages/StartRecording.qml \
    qml/pages/TechSelector.qml \
    qml/pages/UMTSSignals.qml \
    rpm/harbour-cellmate.changes.in \
    rpm/harbour-cellmate.changes.run.in \
    rpm/harbour-cellmate.spec \
    translations/*.ts \
    harbour-cellmate.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-cellscan-de.ts

HEADERS += \
    CellWatcher.h \
    RadioSignal.h \
    TechSpecificListModel.h \
    gsmcellwatcher.h \
    gsmradiosignal.h \
    jsonloutput.h \
    locationprovider.h \
    logrecorder.h \
    ltecellwatcher.h \
    lteradiosignal.h \
    nrradiosignal.h \
    servingcellwatcher.h \
    umtscellwatcher.h \
    wcdmaradiosignal.h
