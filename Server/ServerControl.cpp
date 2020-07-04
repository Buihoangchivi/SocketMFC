#include "pch.h"
#include "ServerControl.h"

void CServerControl::sendMessageToAllClient(message ms)
{

	for (int i = 0; i < clientArray.size(); i++)
		if (clientArray[i].socket)
		{

			sendTo(clientArray[i].socket, ms);

		}

}

bool CServerControl::listenConnection(HWND h)
{

	WSADATA wsaData;
	bool ok = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (!ok)
	{

		socdes = socket(AF_INET, SOCK_STREAM, 0);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(1234);
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(socdes, (SOCKADDR*)&sin, sizeof(sin));
		listen(socdes, 5);
		int err = WSAAsyncSelect(socdes, h, WM_USER + 1, FD_READ | FD_ACCEPT | FD_CLOSE);
		if (!err)
		{

			return true;

		}

	}
	return false;

}

void CServerControl::initLog(CListBox* serverLog)
{

	this->log = serverLog;

}

bool CServerControl::collectDataFromDatabase()
{

	//Mo file DataBase.txt
	ifstream infile;
	infile.open("DataBase.txt");
	dataArray.clear();
	if (infile.is_open())
	{

		while (!infile.eof())
		{

			account dt;
			infile >> dt.username >> dt.password;
			if (strcmp(dt.username, "") != 0)
				dataArray.push_back(dt);

		}
		infile.close();
		return true;

	}
	else
	{

		ofstream outfile;
		outfile.open("DataBase.txt");
		outfile.close();
		return false;

	}

}

string CServerControl::authenticate(SOCKET sk, message ms, CListBox& userLog)
{

	account a;
	memcpy(&a, (char*)&ms.content, sizeof a);
	try
	{

		if (strcmp(ms.action, "login") == 0)
		{

			bool check = false;
			for (int i = 0; i < clientArray.size(); i++)
				if (strcmp(clientArray[i].acc.username, a.username) == 0)
				{

					throw "User already logged in";

				}
			for (int i = 0; i < dataArray.size(); i++)
				if (strcmp(dataArray[i].username, a.username) == 0)
				{

					if (strcmp(dataArray[i].password, a.password) == 0)
					{

						check = true;
						break;

					}
					else
					{

						throw "Wrong password";

					}

				}
			if (!check)
				throw "No such user";
			else
			{

				CLIENT cl;
				strcpy(cl.acc.username, a.username);
				strcpy(cl.acc.password, a.password);
				cl.socket = sk;
				clientArray.push_back(cl);

			}

		}
		else
		{

			for (int i = 0; i < dataArray.size(); i++)
				if (strcmp(dataArray[i].username, a.username) == 0)
				{

					throw "Username already used";

				}
			dataArray.push_back(a);
			ofstream os;
			if (dataArray.size() == 1)
				os.open("DataBase.txt");
			else
				os.open("DataBase.txt", ios::app);
			os << a.username << " " << a.password << endl;
			os.close();
			CLIENT cl;
			strcpy(cl.acc.username, a.username);
			strcpy(cl.acc.password, a.password);
			cl.socket = sk;
			clientArray.push_back(cl);

		}

	}
	catch (const char* err)
	{

		sendTo(sk, message("login-response", err));
		throw 0;

	}

	while (userLog.GetCount() > 0)
	{

		userLog.DeleteString(0);

	}
	for (int i = 0; i < clientArray.size(); i++)
	{

		char* str = clientArray[i].acc.username;
		userLog.AddString(convertCharToCString(((string)"User: " + (string)str).c_str()));

	}

	char s[500];
	sprintf(s, "Username %s %s.", a.username, strcmp(ms.action, "login") == 0 ? "logged in" : "registered");
	sendTo(sk, message("login-response", "OK"));
	if (strcmp(ms.action, "register") == 0)
	{

		sendMessageToAllClient(message("new-user", a.username));

	}
	sendMessageToAllClient(message("new-login", a.username));
	return string(s);

}

string CServerControl::logoutAccount(const char* user, CListBox& userLog)
{

	char str[1000];
	for (int i = 0; i < clientArray.size(); ++i) {
		if (strcmp(clientArray[i].acc.username, user) == 0)
		{

			sprintf(str, "Username %s logged out.", user);
			sendMessageToAllClient(message("logout", user));
			clientArray.erase(clientArray.begin() + i);
			break;

		}
	}
	while (userLog.GetCount() > 0)
	{

		userLog.DeleteString(0);

	}
	for (int i = 0; i < clientArray.size(); i++)
	{

		char* str = clientArray[i].acc.username;
		userLog.AddString(convertCharToCString(((string)"User: " + (string)str).c_str()));

	}
	return (string)str;

}

string CServerControl::cancelAccount(const char* user, CListBox& userLog)
{

	char str[1000];
	for (int i = 0; i < clientArray.size(); ++i) {
		if (strcmp(clientArray[i].acc.username, user) == 0)
		{

			sprintf(str, "Username %s canceled.", user);
			sendMessageToAllClient(message("cancel", user));
			clientArray.erase(clientArray.begin() + i);
			break;

		}
	}
	while (userLog.GetCount() > 0)
	{

		userLog.DeleteString(0);

	}
	for (int i = 0; i < clientArray.size(); i++)
	{

		char* str = clientArray[i].acc.username;
		userLog.AddString(convertCharToCString(((string)"User: " + (string)str).c_str()));

	}
	return (string)str;

}

void CServerControl::closeServer()
{

	char a[] = "ahihi";
	sendMessageToAllClient(message("close-server", a));
	for (int i = 0; i < clientArray.size(); i++)
		if (clientArray[i].socket)
		{

			closesocket(clientArray[i].socket);

		}

}

//void CServerControl::CreateForWriting(SOCKET socket, const char* rawname)
string CServerControl::UpFile(char* username)
{

	//AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	CSocket server;
	unsigned int port = 5678;
	AfxSocketInit(NULL);

	server.Create(port);
	server.Listen(5);


	CSocket sk;

	server.Accept(sk);

	//memcpy((char*)&sk, r, sizeof CSocket);
	int nameLength = 0;
	sk.Receive((char*)&nameLength, sizeof(nameLength), 0);
	char* filename1;
	filename1 = new char[nameLength];
	sk.Receive((char*)filename1, nameLength, 0);
	filename1[nameLength] = '\0';
	string s = "File\\";
	char filename[200];
	strcpy(filename, (char*)(s + (string)filename1).c_str());
	ofstream f;
	f.open(filename, ios::out | ios::binary);
	int end = 0;
	while (true)
	{

		sk.Receive((char*)&end, sizeof(end), 0);
		if (end == 1)
		{

			break;

		}
		int length = 0;
		sk.Receive((char*)&length, sizeof(length), 0);
		char* buff;
		buff = new char[length];
		sk.Receive((char*)buff, length, 0);

		f.write(buff, length);
		ZeroMemory(buff, length);

	}
	f.close();
	sk.ShutDown(2); //Ngat ca chieu Gui va Nhan
	sk.Close();
	server.Close();

	char str[200];
	sprintf(str, "Username %s uploaded file %s.", username, filename1);
	sendMessageToAllClient(message("client-upload", str));
	return (string)str;
	//return true;

	/*string filename(rawname);
	FILE* f = _wfopen(convertCharToCString(rawname), convertCharToCString("wb"));
	fileWriter[filename] = f;
	sendTo(socket, message("upload-file-response", rawname));*/

}

string CServerControl::DownFile(char* username)
{

	//AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	CSocket server;
	unsigned int port = 5678;
	AfxSocketInit(NULL);

	server.Create(port);
	server.Listen(5);


	CSocket sk;

	server.Accept(sk);

	int nameLength = 0;
	sk.Receive((char*)&nameLength, sizeof(nameLength), 0);
	char* filename1;
	filename1 = new char[nameLength];
	sk.Receive((char*)filename1, nameLength, 0);
	filename1[nameLength] = '\0';
	string s = "File\\";
	char filename[200];
	strcpy(filename, (char*)(s + (string)filename1).c_str());
	//
	int end = 0;
	ifstream f;
	f.open(filename, ios::in | ios::binary | ios::ate);
	f.seekg(0, SEEK_SET);
	if (!f)
	{

		f.close();
		string s = "Can't open file " + (string)filename1;
		return s;

	}
	while (!f.eof())
	{
		int length = 0;
		int byte = 0;
		char* buff;
		buff = new char[4096];
		f.read(buff, 4096);
		//cout << buff;
		sk.Send(&end, sizeof(int), 0);
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
		sk.Send(&length, sizeof(int), 0);
		byte = sk.Send(buff, length, 0);
		/*if (byte <= 0)
		{
			cout << "Fails";
			return false;
		}*/
		ZeroMemory(buff, 4096);
	}
	end = 1;
	sk.Send(&end, sizeof(int), 0);
	

	sk.ShutDown(2); //Ngat ca chieu Gui va Nhan
	sk.Close();
	server.Close();

	char str[200];
	sprintf(str, "Username %s downloaded file %s.", username, filename1);
	sendMessageToAllClient(message("client-download", str));
	return (string)str;

	//return true;

	/*string filename(rawname);
	FILE* f = _wfopen(convertCharToCString(rawname), convertCharToCString("wb"));
	fileWriter[filename] = f;
	sendTo(socket, message("upload-file-response", rawname));*/

}

void CServerControl::SaveFile(SOCKET socket, const char* raw)
{

	FilePart part;
	memcpy((char*)&part, raw, sizeof FilePart);

	FILE* f = fileWriter[string(part.filename)];
	fwrite(part.content, 1, part.size, f);

	fclose(f);
	fileWriter.erase(string(part.filename));

	/*if (part.size < 1024)
	{

		fclose(f);
		fileWriter.erase(string(part.filename));
		sendMessageToAllClient(message("new-file", part.filename));

	}
	else
	{

		sendTo(socket, message("upload-file-response", part.filename));

	}*/

}

void CServerControl::CreateForReading(SOCKET socket, const char* rawname)
{

	string filename(rawname);
	FILE* f = _wfopen(convertCharToCString(rawname), convertCharToCString("rb"));
	fileReader[make_pair(filename, socket)] = f;

	FilePart part;
	strcpy(part.filename, rawname);
	part.size = -1;
	sendTo(socket, message("request-file-response", (char*)&part, sizeof part));

}

//string CServerControl::sendResultDownloadFile(SOCKET socket, const char* user, bool check)
string CServerControl::sendResultDownloadFile(SOCKET socket, bool check)
{

	char str[1000];
	if (check)
	{

		//sprintf(str, "Username %s downloaded successfully.", user);
		char temp[] = "1";
		sendTo(socket, message("stop-download", temp));
		sprintf(str, "Username downloaded successfully.");

	}
	else
	{

		//sprintf(str, "Username %s failed to downloadfile.", user);
		char temp[] = "0";
		sendTo(socket, message("stop-download", temp));
		sprintf(str, "Username failed to downloadfile.");

	}
	return (string)str;

}

void CServerControl::SendFile(SOCKET socket, const char* rawname)
{

	string filename(rawname);
	FILE* f = fileReader[make_pair(filename, socket)];

	FilePart part;
	strcpy(part.filename, rawname);
	part.size = fread(part.content, 1, 946, f);

	if (part.size < 946)
	{

		fclose(f);
		fileReader.erase(make_pair(filename, socket));

	}
	sendTo(socket, message("request-file-response", (char*)&part, sizeof part));

}

CLIENT::CLIENT() : socket(0)
{
}

CLIENT::CLIENT(SOCKET sk)
{

	this->socket = sk;

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

void sendTo(SOCKET sk, message& ms)
{

	send(sk, (char*)&ms, sizeof ms, 0);

}

void receiveFrom(SOCKET sk, message& ms)
{

	recv(sk, (char*)&ms, sizeof ms, 0);

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