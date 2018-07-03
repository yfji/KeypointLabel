#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T10:26:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeypointLabel
TEMPLATE = app
#CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += I:/SourceCode/opencv-3.3.0/build/install/include

#LIBS += -LI:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib \
#        -lopencv_core330 \
#        -lopencv_highgui330 \
#        -lopencv_imgproc330 \
#        -lopencv_imgcodecs330 \
#        -lopencv_videoio330 \
LIBS += I:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib/opencv_core330d.lib \
        I:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib/opencv_highgui330d.lib \
        I:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib/opencv_imgproc330d.lib \
        I:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib/opencv_imgcodecs330d.lib \
        I:/SourceCode/opencv-3.3.0/build/install/x64/vc14/lib/opencv_videoio330d.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    labelmanager.cpp \
    qimagelabel.cpp \
    previewdialog.cpp

HEADERS  += mainwindow.h \
    labelmanager.h \
    qimagelabel.h \
    previewdialog.h

FORMS    += mainwindow.ui \
    previewdialog.ui
