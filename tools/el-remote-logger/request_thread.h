#ifndef REQUEST_THREAD_H
#define REQUEST_THREAD_H

#include <QThread>
#include <QByteArray>

class QTcpSocket;

class RequestThread : public QThread {
    Q_OBJECT
public:
    RequestThread(QObject* parent, int handler);
    virtual void run(void);
signals:
    void received(const QByteArray&);
public slots:
    void onReceived(void);
    void onDisconnected(void);
private:
    int m_handler;
    QTcpSocket* m_socket;
};

#endif // REQUEST_THREAD_H
