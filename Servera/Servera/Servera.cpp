#include <WinSock2.h>
#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
void WriteLogSent(string s)
{
	char time[20], date[10];
	ofstream of("Server.txt", ios_base::app);
	of << "Отправлен ответ " << s << ", дата " << _strdate(date) << ", время " << _strtime(time) << endl;
	of.close();
}
void WriteLogGot(string s)
{
	char time[20], date[10];
	ofstream of("Server.txt", ios_base::app);
	of << "Получена команда " << s << ", дата " << _strdate(date) << ", время " << _strtime(time) << endl;
	of.close();
}
int main()
{
	SetConsoleCP(1251);// установк кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	SOCKET sock;
	WSADATA wsadata;
	if (WSAStartup(0x0202, &wsadata) != 0)
	{
		cout << "open WSAStartup is invalid!\n";
		exit(1);
	}
	SOCKADDR_IN sockaddr;
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(1111);
	sockaddr.sin_family = AF_INET;
	int size = sizeof(sockaddr);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
	listen(sock, 1);
	SOCKET connection;
	connection = accept(sock, NULL, NULL);
	if (connection == 0) cout << "Not connected";
	else
	{
		cout << "Client connected\n";
	}
	map<string, string> slovar;
	slovar["Книга"] = "book\0";
	slovar["Идти"] = "go, walk, run, move, follow\0";
	slovar["Кот"] = "cat, tomcat, he-cat\0";
	slovar["Блокнот"] = "notebook, notepadd, pad, scratchpad, tablet\0";
	slovar["Футболка"] = "T-shirt, tee-shirt\0";
	slovar["Телефон"] = "phone, telephone\0";
	slovar["Автобус"] = "bus, coach, autobus, omnibus\0";
	slovar["Цветок"] = "flower, blossom, floret\0";
	slovar["Глаз"] = "eye, optic, orb\0";
	slovar["Банан"] = "banana\0";
	string s = "Доступный список слов:\nКнига\nИдти\nКот\nБлокнот\nФутболка\nТелефон\nАвтобус\nЦветок\nГлаз\nБанан\n\0";
	send(connection, s.c_str(), s.size() + 1, NULL);
	while (1)
	{
		char word[256];
		if (recv(connection, word, 255, NULL) == -1) { 
			continue; 
		}
		WriteLogGot(word);
		if (strcmp(word, "Who") == 0)
		{
			const char answer[] = "Бабенко Алина, К25, вариант - 8";
			send(connection, answer, sizeof(answer), NULL);
			WriteLogSent(answer);
		}
		else
			if (slovar.count(word) == 0)
			{
				WriteLogSent("Invalid word");
				send(connection, "Invalid word", 16, NULL);
			}
			else
			{
				send(connection, slovar.at(word).c_str(), slovar.at(word).size() + 1, NULL);
				WriteLogSent(slovar.at(word));
			}
	}
	system("pause");

}