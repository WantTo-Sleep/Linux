#include <memory>

#include "udpClient.hpp"

void Usage()
{
    std::cout << "Usage:\n\t./udpClient ip port\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage();
        exit(3);
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    std::unique_ptr<sjx::udpClient> cli(new sjx::udpClient(ip, port));

    cli->initClient();
    cli->runClient();

    return 0;
}