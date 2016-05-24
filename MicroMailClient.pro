
TEMPLATE = app

QT += qml quick webengine

qtHaveModule(widgets) {
    QT += widgets # QApplication is required to get native styling with QtQuickControls
}

CONFIG += c++11

SOURCES += main.cpp \
    Model/IMAPClientSession.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

POCOHOME = "E:\Libs\poco-1.7.3"

INCLUDEPATH += "E:\oopProject\pocolib-all\include"

LIBS += -L"E:\oopProject\pocolib-all\lib"

# Default rules for deployment.

include(deployment.pri)

HEADERS += \
    Model/Account.h \
    Model/Attachment.h \
    Model/IMAPClient.h \
    Model/MailBody.h \
    Model/MailClient.h \
    Model/MailListModel.h \
    Model/Utils.h \
    Model/IMAPClientSession.h
