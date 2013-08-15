#include "request_handler.h"
#include "easylogging++.h"
#include "request_thread.h"
#include "request.h"
RequestHandler::RequestHandler(QObject *parent) :
    QTcpServer(parent) {
}

void RequestHandler::start(int port) {
    bool listening = listen(QHostAddress::Any, port);
    CHECK(listening) << "Unable to start server on port [" << port << "]. Please make sure this port is free."
                                              " You can specify server port by specifying argument [-p]";
    LOG_IF(listening, INFO) << "Listening port: " << port;
}

void RequestHandler::incomingConnection(qintptr handler) {
    RequestThread* requestThread = new RequestThread(this, handler);
    QObject::connect(requestThread, SIGNAL(received(QByteArray)), this, SLOT(onReceived(QByteArray)), Qt::DirectConnection);
    QObject::connect(requestThread, SIGNAL(finished()), requestThread, SLOT(deleteLater()));
    requestThread->start();
}

void RequestHandler::onReceived(const QByteArray &data) {
    LOG(INFO) << "Request received: [\n" << data << "\n]";
}
