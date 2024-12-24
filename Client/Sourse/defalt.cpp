#include<winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <tchar.h>
#include<string>
#include<thread>
#include<fstream>
#include <ctime>

std::fstream my_log;
int PORT = 0;
std::string IP;
#pragma comment(lib,"ws2_32.lib") //Winsock Library

std::string time() {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	char time[80];
	strftime(time, sizeof(time), "%d.%m.%Y %H:%M:%S", &localTime);
	return "["+std::string(time) + "] ";
}
void clean(char* ch, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		ch[i] = '\0';
	}
}

void wRecv(SOCKET me){
	while (true) {
		char buffer[1024];
		clean(buffer, 1024);
		if (recv(me, buffer, 1024, 0) == SOCKET_ERROR) { my_log << time() << "error in wRecv()\n"; return; };
		std::cout << buffer<<'\n';
	}
}
void wSend(SOCKET me) {
	while (true) {
		std::string str;
		getline(std::cin,str);
		if (send(me, str.c_str(), str.size(), 0) == SOCKET_ERROR) { my_log << time() << "error in wSend()\n"; return; }
	}
}

void handleError(bool err, const char* msg)
{
	if (!err)
		return;
	my_log << time() << msg << WSAGetLastError();
	exit(EXIT_FAILURE);
}

int main(int argc, char const* argv[])
{
	if(argc!=2){// в аргументе должно быть записан путь до конфиг файла
		std::cout<<"You write less argument than need. We want two argument." << std::endl;
		return 2;
	}

	std::ifstream konfig(argv[1], std::ios::in);//попытка открыть конфиг файл
	if (!konfig.is_open()) {
		std::cout <<"File \"" << argv[1] << "\" not found" << std::endl;
		return 1;
	}

	//проверка на наличие имени лог файла
	std::string log_name="";
	if(!(getline(konfig, log_name, '\n'))){//проверка на чтение вместе со чтением(если можно)
		std::cout<< "This config don't have log's name in file" << std::endl;
		return 3;
	}
	//запуск лог файла
	my_log.open(log_name, std::ios::out | std::ios::trunc);
	my_log << time() << "log file is open\n";
	if (!my_log.is_open()) {
		std::cout << "fatal\n";
		return 1;
	}
	//Проверка на наличие IP
	if(!(getline(konfig,IP,'\n'))){//проверка на чтение вместе со чтением(если можно)
		std::cout<< "This config don't have IP in file" << std::endl;
		return 3;
	}
	//Проверка на наличие порта
	std::string sPORT;
	if(!(getline(konfig, sPORT, '\n'))){//проверка на чтение вместе со чтением(если можно)
		std::cout<< "This config don't have Port in file" << std::endl;
		return 3;
	}
	for (size_t i = 0; i<sPORT.size();++i) {
		PORT *= 10;
		PORT += sPORT[i]-'0';
	}
	my_log << time() << ("Server socket is " + std::to_string(PORT) + '\n');

	//Initialize winsock
	my_log << time() << "Initialising Winsock...\n";
	WSADATA wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	handleError(res != 0, "Failed. Error Code : ");

	char buffer[1024] = { 0 };
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	handleError(client_sock == SOCKET_ERROR, "Could not create socket : ");


	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	//servaddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET,IP.c_str(), &servaddr.sin_addr.s_addr);
	int status = connect(
		client_sock,
		(struct sockaddr*)&servaddr,
		sizeof(servaddr)
	);
	handleError(status == SOCKET_ERROR, "Could not create socket : ");

	std::thread rec(wRecv, client_sock);
	std::thread sen(wSend, client_sock);
	rec.join();
	sen.join();
	my_log.close();
	// closing the connected socket
	closesocket(client_sock);
	WSACleanup();
	return 0;
}