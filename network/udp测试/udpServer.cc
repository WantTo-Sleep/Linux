#include <memory>

#include "udpServer.hpp"

void callBack(std::string ip, uint16_t port, std::string msg)
{
    std::cout << ip << "[" << port << "]#" << msg << std::endl;
}

void Usage()
{
    std::cout << "Usage:\n\t./udpServer port\n";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage();
        exit(3);
    }
    uint16_t port = atoi(argv[1]);
    std::shared_ptr<sjx::udpServer> ser(new sjx::udpServer(callBack, port));

    ser->initServer();
    ser->startServer();

    return 0;
}