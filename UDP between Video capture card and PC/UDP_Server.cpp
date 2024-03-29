// UDP_Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#pragma comment(lib,"WS2_32.lib")
#define BUF_SIZE 64


int main()
{
	//the version of winsock
	int version_a = 1;
	int version_b = 1;

	//initiate winsocket
	WORD versionRequest = MAKEWORD(version_a, version_b);
	WSADATA data;
	int err;


	//初始化套接字动态库
	err = WSAStartup(versionRequest, &data);

	if (err != 0) {
		printf("ERROR!");
		getchar();
		return 0;
	}

	if (LOBYTE(data.wVersion) != 1 || HIBYTE(data.wVersion) != 1)
	{
		printf("WRONG WINSOCK VERSION!");
		WSACleanup();
		getchar();
		return 0;
	}

	/*AF_INET for IP internet,SOCK_DGRAM is for Data Gram(UDP),
	and SOCK_Stream is for TCP, the last one is communicate protocol, generally is zero*/
	SOCKET socServer = socket(AF_INET, SOCK_DGRAM, 0);


	//information of address, always NOT being operated directly
	SOCKADDR_IN srv_addr;     //for server
	SOCKADDR_IN cli_addr;     //for client
	int len = sizeof(SOCKADDR);

	////data recv
	char revBuff[BUF_SIZE] = { 0 };         

	//Struct sin_addr is  used to defind IP address,  it's a property of addr_in.  
	srv_addr.sin_addr.S_un.S_addr = inet_addr("192.168.9.10");
	//srv_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	//set protocol family  
	srv_addr.sin_family = AF_INET;
	//set host port  
	srv_addr.sin_port = htons(55797);

	//Struct cli_addr is  used to defind IP address,  it's a property of addr_in.  
	cli_addr.sin_addr.S_un.S_addr = inet_addr("224.0.0.252");
	//set protocol family  
	cli_addr.sin_family = AF_INET;
	//set host port  
	cli_addr.sin_port = htons(15000);

	bind(socServer, (sockaddr*)&srv_addr, sizeof(srv_addr));

    printf("UDP服务器已经启动\r\n");

	while (1)
	{
		//recvfrom(socServer, revBuff, BUF_SIZE, 0, (sockaddr*)&srv_addr, &len);
		printf("\n%s\n", revBuff);
		printf("The server ip address:%s port:%d\n", inet_ntoa(srv_addr.sin_addr), ntohs(srv_addr.sin_port));        //print ip address of server
		printf("The client ip address:%s port:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));        //print ip address of client
		sendto(socServer, "UDP Hello World from server", sizeof("UDP Hello World from server"), 0, (sockaddr*)&cli_addr, len);
		Sleep(2000);

	}
	
	closesocket(socServer);
	WSACleanup();
    return 0;
}

