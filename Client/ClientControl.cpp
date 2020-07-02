#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "ClientControl.h"

using namespace std;

const int PART_SIZE = 970;
struct FilePart {
    int size;
    char filename[200];
    char content[PART_SIZE];
};

string getFileName(string path) {
    string ans = "";
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        if (path[i] == '/' || path[i] == '\\') {
            break;
        }
        ans = path[i] + ans;
    }
    return ans;
}

void CClientControl::fetchUserList() {
    int pos = -1;
    userBox->ResetContent();
    for (int i = 0; i < (int)userList.size(); ++i) {
        char str[1000];
        if (userList[i].first == currentRoom) {
            pos = i;
        }
        if (userList[i].second > 0) {
            sprintf(str, "%s (%d)", convertCStringToChar(userList[i].first), userList[i].second);
        }
        else {
            sprintf(str, "%s", convertCStringToChar(userList[i].first));
        }
        userBox->AddString(CString(str));
    }
    if (pos >= 0) {
        userBox->SetCurSel(pos);
    }
}






bool CClientControl::Connect(HWND m_hWnd)
{

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {

        return false;

    }

    sk = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    int err = connect(sk, (SOCKADDR*)&serverAddress, sizeof serverAddress);
    if (err == SOCKET_ERROR)
    {

        return false;

    }
    WSAAsyncSelect(sk, m_hWnd, WM_USER + 1, FD_READ | FD_CLOSE);
    sendTo(sk, message("re-login", this->username));
    return true;

}

void CClientControl::Disconnect()
{

    closesocket(sk);

}

void CClientControl::Initialize(const char* username, CListBox* messBox, CListBox* userBox) {
    strcpy(this->username, username);
    this->currentRoom = CString("General");
    this->messBox = messBox;
    this->userBox = userBox;
}

void CClientControl::InsertUser(CString username) {
    bool exists = false;
    for (int i = 0; i < (int)userList.size(); ++i) {
        if (userList[i].first == username) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        int countGeneral = userList.size() > 0 ? userList[0].second : 0;
        if (userList.size() >= 2) {
            userList.erase(userList.begin(), userList.begin() + 2);
        }
        userList.push_back(make_pair(username, 0));
        sort(userList.begin(), userList.end());

        userList.insert(userList.begin(), make_pair(CString("---------------"), -1));
        userList.insert(userList.begin(), make_pair(CString("General"), countGeneral));
    }
    fetchUserList();
    sendTo(sk, message("request-one", convertCStringToChar(username)));
}

void CClientControl::userLogin(CString username)
{

    /* bool exists = false;
     for (int i = 0; i < (int)userList.size(); ++i) {
         if (userList[i].first == username) {
             exists = true;
             break;
         }
     }
     if (!exists) {
         int countGeneral = userList.size() > 0 ? userList[0].second : 0;
         if (userList.size() >= 2) {
             userList.erase(userList.begin(), userList.begin() + 2);
         }
         userList.push_back(make_pair(username, 0));
         sort(userList.begin(), userList.end());

         userList.insert(userList.begin(), make_pair(CString("---------------"), -1));
         userList.insert(userList.begin(), make_pair(CString("General"), countGeneral));
     }
     fetchUserList();
     sendTo(sk, client, message("request-one", convertCStringToChar(username)));*/
}


void CClientControl::Send(CString message) {
    /*  if (currentRoom == CString("General")) {
          sendTo(sk, client, message("message-all", convertCStringToChar(message)));
      }
      else {
          static PrivateMessage pvt;
          strcpy(pvt.receiver, convertCStringToChar(currentRoom));
          strcpy(pvt.message, convertCStringToChar(message));
          sendTo(sk, client, message("message-one", (char*)&pvt, sizeof pvt));
      }*/
}

void CClientControl::ReceiveAll(CString message, bool unread) {
    /* messageList[CString("General")].push_back(message);
     if (currentRoom != CString("General")) {
         userList[0].second += unread ? 1 : 0;
         fetchUserList();
     }
     else {
         fetchMessList();
     }*/
}

void CClientControl::SendFile(SOCKET socket, const char* path) {
    sk = socket;
    FILE* f = _wfopen(convertCharToCString(path), convertCharToCString("rb"));
    string filename(getFileName(string(path)));
    fileReader[filename] = f;
    sendTo(sk, message("upload-file", filename.c_str()));
    
 /*   CString mess = convertCharToCString(("Uploading " + filename).c_str());
    this->messBox->AddString(mess);
    messageList[currentRoom].push_back(mess);*/
}

void CClientControl::SendFilePart(const char* rawname) {
    string filename(rawname);
    FILE* f = fileReader[filename];
    FilePart part;
    strcpy(part.filename, rawname);
    part.size = fread(part.content, 1, PART_SIZE, f);
    sendTo(sk, message("upload-file-part", (char*)&part, sizeof part));
    fclose(f);
    fileReader.erase(filename);

    //if (part.size < PART_SIZE) {
    //    fclose(f);
    //    fileReader.erase(filename);

    //    /*CString mess = convertCharToCString(("Finished uploading " + filename).c_str());
    //    this->messBox->AddString(mess);
    //    messageList[currentRoom].push_back(mess);*/
    //}
}

void CClientControl::RequestFile(const char* rawname) {

    FILE* f = _wfopen(convertCharToCString(rawname), convertCharToCString("rb"));
    string filename(getFileName(string(rawname)));
    fileReader[filename] = f;

    sendTo(sk, message("request-file", rawname));

    CString mess = convertCharToCString(("Downloading " + string(rawname)).c_str());
    this->messBox->AddString(mess);
    messageList[currentRoom].push_back(mess);

    /*sendTo(sk, client, message("request-file", rawname));

    CString mess = convertCharToCString(("Downloading " + string(rawname)).c_str());
    this->messBox->AddString(mess);
    messageList[currentRoom].push_back(mess);*/

}

void CClientControl::ReceiveFilePart(const char* raw) {
    string filename(getFileName(string(raw)));
    FILE* f = fileReader[filename];
    FilePart part;
    strcpy(part.filename, filename.c_str());
    part.size = fread(part.content, 1, PART_SIZE, f);
    sendTo(sk, message("request-file-part", (char*)&part, sizeof part));

    if (part.size < PART_SIZE) {
        fclose(f);
        fileReader.erase(filename);

        CString mess = convertCharToCString(("Finished downloading " + filename).c_str());
        this->messBox->AddString(mess);
        messageList[currentRoom].push_back(mess);
    }


    /* FilePart part;
     memcpy((char*)&part, raw, sizeof FilePart);

     string filename(part.filename);
     if (part.size == -1) {
         FILE* f = _wfopen(convertCharToCString(part.filename), convertCharToCString("wb"));
         fileWriter[filename] = f;
     }
     else {
         FILE* f = fileWriter[filename];
         fwrite(part.content, 1, part.size, f);
         if (part.size < PART_SIZE) {
             fclose(f);
             fileWriter.erase(filename);
             CString mess = convertCharToCString(("Finished downloading " + string(filename)).c_str());
             messageList[currentRoom].push_back(mess);
             this->messBox->AddString(mess);
             return;
         }
     }
     sendTo(sk, client, message("request-file-part", part.filename));*/
}

message::message()
{
}

message::message(const char* action, const char* content)
{

    strcpy(this->action, action);
    strcpy(this->content, content);

}

message::message(const char* action, const char* content, int size)
{

    strcpy(this->action, action);
    memcpy(this->content, content, size);

}

//void CClientControl::sendTo(sk, message& ms)
//{
//
//    send(socketDes, (char*)&ms, sizeof ms, 0);
//
//}
//
//void CClientControl::receiveFrom(message& ms)
//{
//
//    recv(socketDes, (char*)&ms, sizeof ms, 0);
//
//}

void sendTo(SOCKET socket, message& ms)
{

    send(socket, (char*)&ms, sizeof ms, 0);

}

void receiveFrom(SOCKET socket, message& ms)
{

    recv(socket, (char*)&ms, sizeof ms, 0);

}

char* convertCStringToChar(const CString& s)
{

    CStringA cs = CW2A(s, CP_UTF8);
    return _strdup(cs);

}

CString convertCharToCString(const char* s)
{
    return (LPCTSTR)CA2W(s, CP_UTF8);
}

int convertstringToInt(string s)
{

    if (s == "")
        return 0;
    stringstream ipstr;
    ipstr << s;
    int n;
    ipstr >> n;
    return n;

}
