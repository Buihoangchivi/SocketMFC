#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "ClientControl.h"

using namespace std;

const int PART_SIZE = 970;

struct FilePart
{

	int size;
	char filename[200];
	char content[PART_SIZE];

};

string getFileName(string path)
{

	string ans = "";
	for (int i = (int)path.size() - 1; i >= 0; --i)
	{

		if (path[i] == '/' || path[i] == '\\')
		{

			break;

		}
		ans = path[i] + ans;

	}
	return ans;

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

bool CClientControl::SendFile(SOCKET socket, const char* path, char* uploadPath)
{

	sendTo(socket, message("upload-file", username));
	char sAdd[] = "127.0.0.1";
	unsigned int port = 5678; //Cung port voi server
	CSocket client;
	AfxSocketInit(NULL);
	client.Create();
	client.Connect(CA2W(sAdd), port);
	string filename = (string)path;
	string uploadname(getFileName((string)uploadPath));
	int nameLength = uploadname.size();
	char* upName;
	upName = new char[nameLength];
	for (int i = 0; i < nameLength; i++)
	{

		upName[i] = uploadname[i];

	}
	upName[nameLength] = '\0';
	client.Send(&nameLength, sizeof(int), 0);
	client.Send(upName, nameLength, 0);
	int end = 0;
	ifstream f;
	f.open(filename, ios::in | ios::binary | ios::ate);
	f.seekg(0, SEEK_SET);
	if (!f)
	{

		return false;

	}
	while (!f.eof())
	{

		int length = 0;
		int byte = 0;
		char* buff;
		buff = new char[4096];
		f.read(buff, 4096);
		client.Send(&end, sizeof(int), 0);
		length = 4096;
		if (f.eof())
		{

			for (int i = length - 1; i >= 0; i--)
				if (buff[i] != -51)
				{

					length = i + 1;
					break;

				}

		}
		client.Send(&length, sizeof(int), 0);
		byte = client.Send(buff, length, 0);
		ZeroMemory(buff, 4096);

	}
	end = 1;
	client.Send(&end, sizeof(int), 0);
	client.Close();
	return true;

}

bool CClientControl::ReceiveFile(SOCKET socket, const char* path, char* downloadPath)
{

	sendTo(socket, message("download-file", username));
	char sAdd[] = "127.0.0.1";
	unsigned int port = 5678; //Cung port voi server
	CSocket client;
	AfxSocketInit(NULL);
	client.Create();
	client.Connect(CA2W(sAdd), port);
	string fileLink = (string)path;
	string downloadname(getFileName(fileLink));
	int nameLength = downloadname.size();
	char* downName;
	downName = new char[nameLength];
	for (int i = 0; i < nameLength; i++)
	{

		downName[i] = downloadname[i];

	}
	downName[nameLength] = '\0';
	client.Send(&nameLength, sizeof(int), 0);
	client.Send(downName, nameLength, 0);
	ofstream f;
	f.open(downloadPath, ios::out | ios::binary);
	int end = 0;
	while (true)
	{

		client.Receive((char*)&end, sizeof(end), 0);
		if (end == 1)
		{

			break;

		}
		int length = 0;
		client.Receive((char*)&length, sizeof(length), 0);
		char* buff;
		buff = new char[length];
		client.Receive((char*)buff, length, 0);
		f.write(buff, length);
		ZeroMemory(buff, length);

	}
	f.close();
	fileLink = (string)downloadPath;
	string downloadname1(getFileName(fileLink));
	nameLength = downloadname1.size();
	char* downName1 = new char[nameLength];
	for (int i = 0; i < nameLength; i++)
	{

		downName1[i] = downloadname1[i];

	}
	downName1[nameLength] = '\0';
	client.Send(&nameLength, sizeof(int), 0);
	client.Send(downName1, nameLength, 0);
	return true;

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
