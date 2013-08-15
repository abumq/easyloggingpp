#include "request_thread.h"
#include "easylogging++.h"
#include <QTcpSocket>

RequestThread::RequestThread(QObject *parent, int handler)
    : QThread(parent), m_handler(handler) {
}

void RequestThread::run(void) {
    m_socket = new QTcpSocket();
    if (!m_socket->setSocketDescriptor(m_handler)) {
        LOG(ERROR) << "Unable to set socket descriptor [" << m_handler << "] " << m_socket->errorString();
        return;
    }
    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReceived()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    exec();
}

void RequestThread::onReceived(void) {
    emit received(m_socket->readAll());
    if (m_socket->isWritable()) {
        m_socket->write("Log received");
    }
}

void RequestThread::onDisconnected(void) {
    m_socket->deleteLater();
    exit(0); // Exit thread
}
