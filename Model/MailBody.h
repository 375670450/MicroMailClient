#ifndef MAILBODY_H
#define MAILBODY_H

#include "Attachment.h"
#include "Account.h"

#include <QDateTime>
#include <QVariant>
#include<QSharedPointer>
#include<QDebug>

#include <string>


using namespace std;

class MailBody : public QObject {
private:
    Q_OBJECT

    Q_PROPERTY(QString subject READ GetSubject CONSTANT)

    Q_PROPERTY(QString content READ GetContent CONSTANT)

    Q_PROPERTY(QString sender READ GetSender CONSTANT)

    Q_PROPERTY(QDateTime datetime READ GetDateTime CONSTANT)

    Q_PROPERTY(bool isread READ GetIsread WRITE SetIsread CONSTANT)

//    Q_PROPERTY(QList<QString> recipients READ GetRecipient CONSTANT)


public:


    MailBody(QString _s = "subject", QString _c="content", bool _r = false  ){
        subject = _s;
        content = _c;
        isread = _r;
    }

    QString GetSubject(){
        return subject;
    }

    QString GetContent(){
        return content;
    }

    QString GetSender(){
        return sender;
    }

    QDateTime GetDateTime(){
        return datetime;
    }

    bool GetIsread(){
        return isread;
    }

    void SetIsread(bool val){
        isread = val;
//        qDebug() << "SetIsread: emit dataChanged()";
//        emit(dataChanged ());
    }

    QList<QString> GetRecipients(){
        return recipients;
    }

//    QVector<Attachment> GetAttachements(){
//        return attachements;
//    }

private:

    QString subject;

    QString content;

    QString sender;

    QDateTime datetime;

    QList<QString> recipients;

    bool isread;

//    QVector<Attachment> attachements;

};

typedef QSharedPointer<MailBody> MAILBODY_PTR;
typedef QList<MAILBODY_PTR> MAILBODY_PTR_QLIST;



#endif // MAILBODY_H
