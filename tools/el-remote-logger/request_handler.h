#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <QTcpServer>
#include <QByteArray>

class RequestHandler : public QTcpServer {
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = 0);
    virtual void incomingConnection(qintptr handler);
    void start(int port);
signals:
    void received(const QByteArray&);
public slots:
    void onReceived(const QByteArray&);
};

#endif // REQUEST_HANDLER_H
