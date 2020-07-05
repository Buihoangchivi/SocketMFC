#pragma once
//#include <afxsock.h>
#include "afxsock.h"
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <cstdio>
#include <fstream>
using namespace std;

struct account
{

    char username[50];
    char password[50];

};

struct message
{

    char action[50];
    char content[4100];
    message();
    message(const char* action, const char* content);
    message(const char* action, const char* content, int size);

};

class CClientControl {
private:

    SOCKADDR_IN serverAddress;

public:
    SOCKET sk;
    char username[50];
    bool Connect(HWND);
    void Disconnect();
    bool SendFile(SOCKET, const char*, bool, char*);
    bool ReceiveFile(SOCKET, const char*, bool, char*);
 
};

void sendTo(SOCKET socket, message& ms);
void receiveFrom(SOCKET socket, message& ms);
char* convertCStringToChar(const CString& s);
CString convertCharToCString(const char* s);
int convertstringToInt(string s);

