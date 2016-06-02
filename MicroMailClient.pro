
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

POCOHOME = "C:\Users\37567\Documents\Visual Studio 2015\Projects\MicroMailClient-QT\PocoLib"

INCLUDEPATH += "E:\oopProject\pocolib-all\include"

<<<<<<< HEAD
LIBS += -L"E:\oopProject\pocolib-all\lib" -lPocoFoundationd
=======
LIBS += -L"$${POCOHOME}\Lib"
>>>>>>> repairing_pop3_decode

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
    Model/IMAPClientSession.h \
    Model/ReceiveMailClient.h \
    Model/SendMailClient.h \
<<<<<<< HEAD
    Exception/MailClientException.h \
    Exception/MailGenerationException.h \
    Exception/MailSendException.h \
    Exception/MailReceiveException.h
=======
    Model/SMTPClient.h \
    Model/POP3Client.h
>>>>>>> repairing_pop3_decode
