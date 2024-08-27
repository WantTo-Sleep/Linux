#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace sjx
{
    class udpClient
    {
    public:
        udpClient(const std::string &serverIp, const uint16_t &serverPort)
            : _ip(serverIp), _port(serverPort)
        {
        }
        ~udpClient()
        {
        }
        void initClient()
        {
            // 1.创建socket
            _socketfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_socketfd == -1)
            {
                perror("socket error:");
                exit(1);
            }
            std::cout << "socket success: " << _socketfd << std::endl;

            // 2.绑定ip和端口号
            // 对于客户端进程，一般不需要程序员自己绑定，在向服务器发出信息时，由操作系统自动绑定
        }
        void runClient()
        {
            struct sockaddr_in server;
            bzero(&server, sizeof(server));
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr(_ip.c_str());
            server.sin_port = htons(_port);

            std::string msg;
            while (true)
            {
                std::cout << "Please Enter# ";
                std::getline(std::cin, msg);

                sendto(_socketfd, msg.c_str(), msg.size(), 0, (struct sockaddr *)&server, sizeof(server));
            }
        }

    private:
        std::string _ip;
        uint16_t _port;
        int _socketfd;
    };
}