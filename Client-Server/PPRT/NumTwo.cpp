#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>

int main(int args, char* argv[]) 
{
    int client;
    
    struct sockaddr_in addr;
    socklen_t sizeOfAddr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1703);
    addr.sin_family = AF_INET;
    client = socket(AF_INET, SOCK_STREAM, NULL);
    bind(client, (sockaddr*)&addr, sizeof(addr));
    listen(client, 1);
 
    int newConnection;
    int cycle = 0;
    int stillConnected = 0;
    newConnection = accept(client, (struct sockaddr*)&addr, &sizeOfAddr);
    while (true) {
        if(cycle==0){sleep(2);}
        cycle++;
        char recievedData[3];
        int bytesReceived = recv(newConnection, recievedData, sizeof(recievedData), 0);
        if(stillConnected == 15)
        {
            stillConnected = 0;
            cycle=0;
            newConnection = accept(client, (struct sockaddr*)&addr, &sizeOfAddr);
            continue;
        }
        int intData = 0;
        for (int i = 0; i < 3; i++) 
        {
            intData *= 10;
            if (recievedData[i]<0&&i==0) 
            {
                intData = -1;
                break;
            }
            else if (recievedData[i] < 0) 
            {
                intData /= 10;
                break;
            }
            intData += static_cast<int>(recievedData[i] - '0');
        }
        if(intData>576)
        {
            recievedData[0]=-1;
        }
        else 
        if (intData>0 && intData%32==0)
        {
            std::cout << "\nData recieved.\n";
            recievedData[0] =-1;
        }
        else if(intData>=0)
        {
            std::cout << "\nData error.\n";
            recievedData[0]=-1;
        }
        else if (intData < 0) 
        {
            stillConnected++;
        }
    }
}
