QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cameraconnect.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cameraconnect.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Include Pylon
INCLUDEPATH += "C:\Program Files\Basler\pylon 6\Development\include"
LIBS += -L"C:\Program Files\Basler\pylon 6\Development\lib\x64"
        -l"GCBase_MD_VC141_v3_1_Basler_pylon"
        -l"GenApi_MD_VC141_v3_1_Basler_pylon"
        -l"PylonBase_v6_0"
        -l"PylonC"
        -l"PylonGUI_v6_0"
        -l"PylonUtility_v6_0"

# Include OpenCV
INCLUDEPATH += C:\opencv\include
LIBS += -LC:\opencv\lib\Release\
        -lopencv_core430 \
        -lopencv_highgui430 \
        -lopencv_imgcodecs430 \
        -lopencv_imgproc430 \
        -lopencv_photo430

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
