#ifndef POP3CLIENT_H
#define POP3CLIENT_H
<<<<<<< HEAD
#include <iostream>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/POP3ClientSession.h>
#include <QDateTime>
#include <QString>
#include <QSharedPointer>
#include <string>
#include <vector>
#include "Account.h"
#include "ReceiveMailClient.h"
#include "MailBody.h"
#include "Attachment.h"
=======

#include "Account.h"
#include "ReceiveMailClient.h"
#include "MailBody.h"
#include "Attachment.h"
#include "Utils.h"

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/MultipartReader.h>
#include <Poco/Net/POP3ClientSession.h>
#include <Poco/String.h>

#include <QDateTime>
#include <QString>
#include <QSharedPointer>

#include <iostream>
#include <string>
#include <vector>


using Poco::toUpper;
using Poco::toLower;
using Poco::Net::MultipartReader;
>>>>>>> repairing_pop3_decode

class POP3Client : public ReceiveMailClient{
private:
    typedef QSharedPointer<Poco::Net::POP3ClientSession> SESSION_PTR;
public:

    POP3Client(QString host,
               QString port = QString::number (Poco::Net::POP3ClientSession::POP3_PORT)) {
<<<<<<< HEAD
        this->_session = new Poco::Net::POP3ClientSession(host,port);
=======
        this->_session = SESSION_PTR::create(host.toStdString(),port.toInt());
>>>>>>> repairing_pop3_decode
        this->_host = host;
        this->_port = port;
    }


    bool login(QString _user, QString _passwd,bool requireSSL) override{
        try{
<<<<<<< HEAD
            //SSL登陆
            if (requireSSL){
                initializeSSL();
                // always accept even if error occurred
                SharedPtr<InvalidCertificateHandler> ptrHandler = new AcceptCertificateHandler(false);
                Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
                SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
                SocketAddress socketAddress(host, port);
                SecureStreamSocket socket(socketAddress, ptrContext);
                this->_session = new Poco::Net::POP3ClientSession(socket);
            }
=======
//            qDebug() <<
>>>>>>> repairing_pop3_decode
            _session->login(_user.toStdString (), _passwd.toStdString ());
            return true;
        }
        catch(Poco::Net::POP3Exception & e){
<<<<<<< HEAD
=======
            qDebug() << e.what() << "\n";
>>>>>>> repairing_pop3_decode
            return false;
        }
    }

    int getFolders(QList<QString> & _folders) override{

        QString _name = "Inbox";
        int size = 1;
        _folders.push_back (_name);

        return size;
    }

    int selectFolder(const QString & folder) override{

        _mailList.clear ();

        std::vector<std::string> uids;

        _selectedFolder = folder;

        _session->listMessages(_mailList);

        qDebug() << "In select Folder, folder = "<< folder << ", mailList.size = " << _mailList.size () << "uids.size = " << uids.size ()<< "\n";

<<<<<<< HEAD
        for(int i=0; i<_mailList.size(); i++){
            for(int j=0; j<i; j++){
                Poco::Net::MailMessage message1, message2;
                _session->retrieveMessage((*(_mailList.begin()+j)).id,message1);
                _session->retrieveMessage((*(_mailList.begin()+i)).id,message2);
                if( (*(_mailList.begin()+i)).id == (*(_mailList.begin()+j)).id )
                    qDebug() << QString::fromUtf8(message1.getSubject().c_str()) << " and " << QString::fromUtf8 (message2.getSubject().c_str()) << " has the same uid, subject = " << QString::fromUtf8 (message1.getSubject().c_str()) << "\n";
            }
        }

=======
>>>>>>> repairing_pop3_decode
        _curListIndex = 0;

        return _mailList.size();

    }

    int getMailBodies(QList<MAILBODY_PTR> & result,int count){
<<<<<<< HEAD
        _mailList.clear ();
        _session->listMessages(_mailList);
=======
>>>>>>> repairing_pop3_decode
        std::string partsPaths;
        int counter = 0;
        for( ; _curListIndex < _mailList.size (); _curListIndex++, counter++) {

            if( counter >= count )
                break;
<<<<<<< HEAD

            auto i = _mailList.at ( _mailList.size () - _curListIndex - 1);
            Poco::Net::MailMessage message;
            _session->retrieveMessage(i.id, message);
            MAILBODY_PTR newMail = MAILBODY_PTR::create(QString::fromUtf8 (message.getSubject().c_str()));
            newMail->setContent(QString::fromUtf8 (message.getContent().c_str()));
            newMail->setSender(QString::fromUtf8 (message.getSender().c_str()));
            QString RecipientsList= "";
//            for (auto i=message.Recipients.begin();i!=message.Recipients.end();i++){
//                RecipientsList.append(QString::fromUtf8(*i));
//            }
//            newMail->addRecipient(message.Recipients[0]);
            newMail->setIsread (false);
            result.push_back (newMail);
=======
            qDebug() << "get Mail Bodies in POP3Client\n";
            auto i = _mailList.at ( _mailList.size () - _curListIndex - 1);
            Poco::Net::MailMessage message;
            try{
                _session->retrieveMessage(i.id, message);
//                if( QString::fromUtf8 (message.getSubject ()).startsWith ("=?") ){

//                }else{

//                }
                auto tmp = QString::fromUtf8 (message.getSubject ().c_str ());
//                qDebug() << QString::fromUtf8 (tmp.substr (tmp).c_str ()) << "\n";
                MAILBODY_PTR newMail = MAILBODY_PTR::create(QString::fromUtf8 (Utils::decoder ( tmp.replace ("\"","").split (' ')[0].toStdString() ).c_str()));
                qDebug() << newMail->getSubject () << "\n";

                newMail->setSender(QString::fromUtf8 (message.getSender().c_str()));

                newMail->setContent(QString::fromUtf8 (message.getContent().c_str()));
                newMail->setHTMLContent ( newMail->getContent () );
//                if( message.getContent ().length () > 0 ){
//                } else {
//                    std::stringstream outs;
//                    Poco::Net::MessageHeader header;

//                    _session->retrieveMessage (i.id, outs);

//                    readMultiPart (header, outs, newMail);

//                    qDebug() << "Subject=" << newMail->getSubject () << "\n Sender=" << newMail->getSender () << "\n isMultipart = " << message.isMultipart ()
//                                            << "\n ContentType = " << QString::fromUtf8(message.getContentType ().c_str ()) << "\n Content = "
//                                            <<  QString::fromUtf8(outs.str ().c_str ())<< "\n";

//                }

//                newMail->addRecipient(RecipientsList);
                newMail->setIsread (false);
                result.push_back (newMail);

            }catch( Poco::Net::POP3Exception & e ){
                std::cout << e.what () << "\n";
            }

>>>>>>> repairing_pop3_decode
        }
        return counter;

    }

<<<<<<< HEAD
=======
    void readMultiPart(const MessageHeader & header, std::istream & stream, MAILBODY_PTR newmail){
//       if( header.has ("Content-Disposition") ){
//          string disp;
//          string filename;
//          string attachment;
//          NameValueCollection params;

//          MessageHeader::splitParameters(messageHeader["Content-Disposition"], disp, params);
//          filename = params.get("filename", "nil");
//          if(filename != "nil") {
//            // Filename might be encoded in Base64 or QuotedPrintable

//            _filenames.push_back(Utils::decoder (filename));
//              StreamCopier::copyToString(stream, attachment);
//              _attachments.push_back(attachment);
//          }
//       }

        std::string contentType = header.get ("Content-Type", "nil");

        if( toLower(contentType).find("multipart") == 0 ){
            MultipartReader multipartReader(stream);

            while( multipartReader.hasNextPart() ){
                MessageHeader subHeader;
                multipartReader.nextPart (subHeader);

                std::string subtype = toLower(subHeader.get("Content-Type","nil"));

                if( subtype == "nil" )
                    continue;
                else if (subtype.find("application") != std::string::npos && subtype.find ("name") != std::string::npos ){

                }else if( subtype.find("boundary") != std::string::npos ){
//                    int start = 0;
//                    if(_myboundary.empty()) {
//                        bStart = subContentType.find('_');
//                        _myboundary = String::FixField(subContentType, bStart, (subContentType.length() - (bStart + 1)));
//                    }
                }else if( subtype.find("text/plain") != std::string::npos ){
                    std::string charset;

                    if( subtype.find ("charset") !=std::string::npos ){

                    }

                }else if( subtype.find ("text/html") != std::string::npos ){

                }


            }

        }

    }

>>>>>>> repairing_pop3_decode
    int DeleteMail (const QList<int> & ids)override{
        return 0;
    }

    void setTimeout (int val)override{
<<<<<<< HEAD
        Poco::Timespan timeout = Poco::Timespan(0,0,0,0,1000 * val);  //该构造函数默认最小是微妙(第五个参数),前四个:day,hour,minute,second,这里的延时我们需要以毫秒计
=======
        Poco::Timespan timeout = Poco::Timespan(0,0,0,0,1000 * val);  //�ù��캯��Ĭ����С��΢��(���������),ǰ�ĸ�:day,hour,minute,second,�������ʱ������Ҫ�Ժ����
>>>>>>> repairing_pop3_decode
        _session->setTimeout(timeout);
    }

    int getTimeout ()override{
        return _session->getTimeout().milliseconds();
    }

    ~POP3Client(){

    }

private:
     Poco::Net::POP3ClientSession::MessageInfoVec _mailList;
     SESSION_PTR _session;
};

#endif // POP3CLIENT_H