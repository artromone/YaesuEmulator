#ifndef YAESUEMULATOR_QTCP_SERVER_H
#define YAESUEMULATOR_QTCP_SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = Q_NULLPTR);

    void start(int port);
    void stop();

    bool isStarted() const;
    bool isOk() const;

signals:
    void onStart(QTcpSocket* socket);
    void newClient(QTcpSocket* socket);
    void stateChanged(bool state);
    void okChanged(bool ok);

public slots:
    void newConnection();

private:
    QTcpServer* server_;
    bool isOk_;
};
#endif
