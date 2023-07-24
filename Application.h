#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include "Client.h"
#include "Emulator.h"
#include "Server.h"
#include "Widget.h"

class Application
{
public:
    Application();
    int start(int argc, char *argv[]);

private:
    Emulator emulator_;
    Server server_;
    std::stack<Client> stackClient_;
    Widget widget_;
};

#endif // APPLICATION_H
