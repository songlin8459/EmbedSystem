#-------------------------------------------------
#
# Project created by QtCreator 2022-07-16T12:26:15
#
#-------------------------------------------------

QT       += core gui multimedia concurrent androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WarOfAircraft
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        map.cpp \
        gamebutton.cpp \
        mainwindow.cpp \
    myhero.cpp \
    bullet.cpp \
    enemyplane.cpp \
    movevector.cpp \
    displayhp.cpp \
    scoreboard.cpp \
    magazinedisplay.cpp \
    bombchange.cpp

HEADERS += \
        map.h \
        config.h \
        gamebutton.h \
        mainwindow.h \
    myhero.h \
    bullet.h \
    enemyplane.h \
    movevector.h \
    displayhp.h \
    scoreboard.h \
    magazinedisplay.h \
    bombchange.h

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/icon_launcher.png \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
ANDROID_PERMISSIONS += READ_EXTERNAL_STORAGE
