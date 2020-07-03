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

typedef vector<CString> MessageList;

struct account
{

    char username[25];
    char password[25];

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

    map<CString, MessageList> messageList;
    map<CString, int> fileLength;

    map<string, FILE*> fileWriter;
    map<string, FILE*> fileReader;

    vector<pair<CString, int>> userList;
    CString currentRoom;
    CListBox* messBox;
    CListBox* userBox;

    void fetchUserList();

public:
    SOCKET sk;
    char username[20];
    void Initialize(const char*, CListBox*, CListBox*);
    bool Connect(HWND);
    void Disconnect();

    void InsertUser(CString);
    void userLogin(CString);
    void Send(CString);
    void ReceiveAll(CString, bool unread = false);

    //void SendFile(SOCKET, const char*);
    bool SendFile(SOCKET, const char*);
    bool ReceiveFile(SOCKET, const char*);
    void SendFilePart(const char*);

    void RequestFile(const char*);
    void ReceiveFilePart(const char*);
    /* void sendTo(message& ms);
     void receiveFrom(message& ms);*/
};


void sendTo(SOCKET socket, message& ms);
void receiveFrom(SOCKET socket, message& ms);
char* convertCStringToChar(const CString& s);
CString convertCharToCString(const char* s);
int convertstringToInt(string s);

