#pragma once
#include <afxsock.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <map>
using namespace std;

struct account
{

	char username[50];
	char password[50];

};

struct CLIENT
{

	SOCKET socket;
	account acc;
	CLIENT();
	CLIENT(SOCKET);

};

struct FilePart
{

	int size;
	char filename[50];
	char content[970];

};

struct message
{

	char action[50];
	char content[970];
	message();
	message(const char* action, const char* content);
	message(const char* action, const char* content, int size);

};

class CServerControl
{
private:
	SOCKADDR_IN sin;
	SOCKET socdes;
	CListBox* log;
	vector<account> dataArray;
	void sendMessageToAllClient(message);

public:
	vector<CLIENT> clientArray;
	bool listenConnection(HWND);
	void initLog(CListBox* serverLog);
	bool collectDataFromDatabase();
	string authenticate(SOCKET sk, message ms, CListBox& userLog);
	string logoutAccount(const char* user, CListBox& userLog);
	string cancelAccount(const char* user, CListBox& userLog);
	void closeServer();
	string UpFile(char*);
	string DownFile(char*);

};

void sendTo(SOCKET sk, message& ms);
void receiveFrom(SOCKET sk, message& ms);
char* convertCStringToChar(const CString& s);
CString convertCharToCString(const char* s);
int convertstringToInt(string s);

