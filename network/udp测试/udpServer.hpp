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
    static const std::string defaultIp = "0.0.0.0";
    typedef std::function<void(std::string, uint16_t, std::string)> func_t;
    class udpServer
    {
    public:
        udpServer(const func_t &callBack, const uint16_t &port, const std::string &ip = defaultIp)
            : _ip(defaultIp), _port(port), _callBack(callBack)
        {
        }
        ~udpServer()
        {
        }
        void initServer()
        {
            // 1.创建套接字
            // 返回一个文件描述符, AF_INET表示IPV4 Internet protocols
            // SOCK_DGRAM表示支持数据报（无连接的、不可靠的、固定最大长度的消息）
            _socketfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_socketfd == -1)
            {
                perror("socket error:");
                exit(1);
            }
            std::cout << "socket success: " << _socketfd << std::endl;

            // 2.绑定ip和端口号
            struct sockaddr_in local;
            bzero(&local, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(_port);
            local.sin_addr.s_addr = inet_addr(_ip.c_str());
            int n = bind(_socketfd, (struct sockaddr *)&local, sizeof(local));
            if (n == -1)
            {
                perror("bind error:");
                exit(2);
            }
        }
        void startServer()
        {
            char buf[128];
            while (true)
            {
                struct sockaddr_in receive;
                socklen_t len = sizeof(receive);
                ssize_t n = recvfrom(_socketfd, buf, sizeof(buf), 0, (struct sockaddr *)&receive, &len);
                if (n >= 0)
                {
                    buf[n] = 0;
                    std::string clientIp = inet_ntoa(receive.sin_addr);
                    uint16_t clientPort = ntohs(receive.sin_port);
                    std::string msg = buf;
                    _callBack(clientIp, clientPort, msg);
                }
            }
        }

    private:
        std::string _ip;
        uint16_t _port;
        int _socketfd;
        func_t _callBack;
    };
}