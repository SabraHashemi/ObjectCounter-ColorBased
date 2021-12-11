QT       += core gui
RC_ICONS = ico.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CFLAGS += -std=c++11 -fpermissive
QMAKE_CXXFLAGS += -std=c++11 -fpermissive
QMAKE_LFLAGS += -std=c++11 -fpermissive
QT += sql
QT += multimedia
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Blob.cpp \
    ColorPickerActionWidget.cpp \
    ColorPickerToolButton.cpp \
    DomColors.cpp \
    algorithms.cpp \
    insertsql.cpp \
    main.cpp \
    mainwindow.cpp \
    matdisplay.cpp \

HEADERS += \
    Blob.h \
    ColorPickerActionWidget.h \
    ColorPickerToolButton.h \
    DomColors.h \
    ILoadSaveConfig.h \
    algorithms.h \
    common.h \
    imagesaver.h \
    insertsql.h \
    mainwindow.h \
    matdisplay.h \
    myconnectionwrapper.h \
    ui_mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


QT += multimedia
CONFIG += c++11



INCLUDEPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include
INCLUDEPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include\\opencv2
DEPENDPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include


#INCLUDEPATH += C:\Users\ZahRa\AppData\Roaming\Python\Python37\site-packages\numpy\core\include


LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_world420.lib


LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_world420.lib
LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_img_hash420.lib


LIBS += -LD:\opencv-4.2.0\opencv-4.2.0\CudaBuild\lib\Release\
            -lopencv_world420 \
            -lopencv_img_hash420\

        # Projects > Build & Run > Run
        # Check: add build library search path to PATH
        # This allows OpenCV DLLs to be found when running this application
LIBS += -L"D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\bin"
RESOURCES += \
    qdarkstyle/light/lightstyle.qrc \
    src.qrc \
    src.qrc





