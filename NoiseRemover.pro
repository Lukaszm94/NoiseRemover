QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++11 Wall

#windows
INCLUDEPATH += "D:/Libraries/opencv/release/install/include"
LIBS += "-LD:/Libraries/opencv/release/install/x86/mingw/bin" -lopencv_highgui310 -lopencv_core310 -lopencv_imgproc310 -lopencv_imgcodecs310
#linux
#LIBS += -L/usr/local/lib
#LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui  -lopencv_imgcodecs


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scrollablecvimagewidget.cpp \
    loadimagewidget.cpp \
    manualnoiseremovalwidget.cpp \
    noiseremoverapplication.cpp \
    noiseremover.cpp \
    saveimageswidget.cpp

HEADERS += \
    cvimagewidget.h \
    mainwindow.h \
    scrollablecvimagewidget.h \
    loadimagewidget.h \
    manualnoiseremovalwidget.h \
    masktype.h \
    noiseremoverapplication.h \
    noiseremover.h \
    frequencydomainimage.h \
    distancetype.h \
    saveimageswidget.h
