#include <WinSock2.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
void WriteLogSent(string s)
{
	char time[20], date[10];
	ofstream of("Client.txt", ios_base::app);
	of << "Отправлена команда " << s << ", дата " << _strdate(date) << ", время " << _strtime(time) << endl;
	of.close();
}
void WriteLogGot(string s)
{
	char time[20], date[10];
	ofstream of("Client.txt", ios_base::app);
	of << "Получен ответ " << s << ", дата " << _strdate(date) << ", время " << _strtime(time) << endl;
	of.close();
}
int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSADATA wsadata;
	if (WSAStartup(0x0202, &wsadata) != 0)
	{
		cout << "Error";
		exit(1);
	}
	SOCKADDR_IN sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(1111);
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	if (connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) != 0) cout << "Not connected";
	else cout << "Connected\n";
	char message[100];
	recv(sock, message, 99, NULL);
	cout << message;
	while (1)
	{
		char word[256];
		cin.getline(word, 255);
		send(sock,word, 256, NULL);
		WriteLogSent(word);
		char answer[100];
		recv(sock, answer, 100, NULL);
		WriteLogGot(answer);
		cout << answer << endl;
	}
	system("pause");

}
