#ifndef APPLICATION_H
#define APPLICATION_H

#include "Client.h"
#include "Emulator.h"
#include "Server.h"
#include "Widget.h"

#include <QObject>

#include <memory>
#include <unordered_map>

class Application : public QObject
{
public:
    explicit Application(QQmlContext& context, QObject* parent = Q_NULLPTR);

private slots:
    void onNewClient(QTcpSocket* socket); //
    void onPopClient(int clientId);

private:
    std::unique_ptr<Emulator> emulator_;
    std::unique_ptr<Server> server_;
    std::unordered_map<int, std::shared_ptr<Client>> clientMap_;

    Widget widget_;
};

#endif // APPLICATION_H
