QT       += core gui printsupport network xml sql widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32:VERSION = 2.1.0.1
else:VERSION = 2.1.0.1

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#INCLUDEPATH += "D:\Qt\Tools\OpenSSL\Win_x86\include"
#LIBS += -LD:\Qt\Tools\OpenSSL\Win_x86\lib -llibcrypto -llibssl
win32:contains(QMAKE_HOST.arch, x86_64) {
    INCLUDEPATH += "D:\Qt\Tools\OpenSSL\Win_x64\include"
    LIBS += -LD:\Qt\Tools\OpenSSL\Win_x64\lib -llibcrypto -llibssl
} else {
    INCLUDEPATH += "D:\Qt\Tools\OpenSSL\Win_x86\include"
    LIBS += -LD:\Qt\Tools\OpenSSL\Win_x86\lib -llibcrypto -llibssl
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = minecraft.ico
RC_CODEPAGE = 1252
RC_LANG = 0x040C
QMAKE_TARGET_COMPANY = "Black Wizard Company"
QMAKE_TARGET_DESCRIPTION = "Suivez vos progres Minecraft !"
QMAKE_TARGET_COPYRIGHT = "Copyright 2019-2020 Black Wizard Company"
QMAKE_TARGET_PRODUCT = "Minecraft Advancements"

SOURCES += \
    dateetheurefilterproxymodel.cpp \
    dia_apropos.cpp \
    main.cpp \
    frm_principale.cpp \
    settings/database.cpp \
    settings/dia_parametres.cpp \
    settings/settings.cpp \
    sqlmodel.cpp \
    statistiques.cpp

HEADERS += \
    dateetheurefilterproxymodel.h \
    dia_apropos.h \
    frm_principale.h \
    settings/database.h \
    settings/dia_parametres.h \
    settings/settings.h \
    sqlmodel.h \
    statistiques.h

FORMS += \
    dia_apropos.ui \
    frm_principale.ui \
    settings/dia_parametres.ui \
    statistiques.ui

TRANSLATIONS += \
    Minecraft-Advancements_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Backup-ChoixVersion.txt \
    Backup-ReadJson.txt \
    Note.txt \
    Old_Slots_avant_2.0.0

RESOURCES += \
    files.qrc \
    img.qrc
