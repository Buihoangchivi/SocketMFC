
// ServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg dialog



CServerDlg::CServerDlg(CWnd* pParent) : CDialogEx(IDD_SERVER_DIALOG, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	control.initLog(&serverLog);

}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, serverLog);
	DDX_Control(pDX, IDC_LIST2, userLog);
	DDX_Control(pDX, IDLISTEN, listenButton);
	DDX_Control(pDX, IDC_LIST3, fileListLog);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER + 1, eventsControl)
	ON_BN_CLICKED(IDLISTEN, &CServerDlg::OnBnClickedListen)
	ON_BN_CLICKED(IDCANCEL, &CServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (control.collectDataFromDatabase())
	{

		serverLog.AddString(L">>");
		serverLog.AddString(L"Server connected to database.");
		//In 1 dong trong de co the de doc lich su thao tac giua client va server
		serverLog.AddString(L"");

	}
	else
	{

		serverLog.AddString(L">>");
		serverLog.AddString(L"Database file doesn't exist. Program has created a new empty database file.");
		//In 1 dong trong de co the de doc lich su thao tac giua client va server
		serverLog.AddString(L"");

	}
	//Tao folder ten File chua cac file de cac client upload, download
	_mkdir("File");
	PrintFileList();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CServerDlg::eventsControl(WPARAM socket, LPARAM lp)
{

	if (WSAGETSELECTERROR(lp))
	{

		closesocket(socket);
		return 0;

	}
	switch (WSAGETSELECTEVENT(lp))
	{
	case FD_ACCEPT:
	{

		/*SOCKET sk = accept(socket, NULL, NULL);
		CLIENT cl(sk);
		control.clientArray.push_back(cl);*/
		accept(socket, NULL, NULL);
		break;

	}
	case FD_READ:
	{

		message* msg = new message;
		receiveFrom(socket, *msg);
		if (strcmp(msg->action, "login") == 0 || strcmp(msg->action, "register") == 0)
		{

			try
			{

				serverLog.AddString(L">>");
				string response = control.authenticate(socket, *msg, userLog);
				serverLog.AddString(convertCharToCString(response.c_str()));
				//In 1 dong trong de co the de doc lich su thao tac giua client va server
				serverLog.AddString(L"");

			}
			catch (int) 
			{

				string response = "Fail to login or register!!!";
				serverLog.AddString(convertCharToCString(response.c_str()));
				//In 1 dong trong de co the de doc lich su thao tac giua client va server
				serverLog.AddString(L"");
			
			}

		}
		if (strcmp("download-file", msg->action) == 0)
		{

			serverLog.AddString(L">>");
			string response = control.DownFile(msg->content);
			serverLog.AddString(convertCharToCString(response.c_str()));
			//In 1 dong trong de co the de doc lich su thao tac giua client va server
			serverLog.AddString(L"");

		}
		if (strcmp("upload-file", msg->action) == 0)
		{

			serverLog.AddString(L">>");
			string response = control.UpFile(msg->content);
			serverLog.AddString(convertCharToCString(response.c_str()));
			//In 1 dong trong de co the de doc lich su thao tac giua client va server
			serverLog.AddString(L"");
			PrintFileList();

		}
		if (strcmp("logout", msg->action) == 0)
		{

			serverLog.AddString(L">>");
			string response = control.logoutAccount(msg->content, userLog);
			serverLog.AddString(convertCharToCString(response.c_str()));
			//In 1 dong trong de co the de doc lich su thao tac giua client va server
			serverLog.AddString(L"");

		}
		if (strcmp("cancel", msg->action) == 0)
		{

			serverLog.AddString(L">>");
			string response = control.cancelAccount(msg->content, userLog);
			serverLog.AddString(convertCharToCString(response.c_str()));
			//In 1 dong trong de co the de doc lich su thao tac giua client va server
			serverLog.AddString(L"");

		}
		if (strcmp("get-server-path", msg->action) == 0)
		{

			TCHAR defaultDir[200];
			GetCurrentDirectory(200, defaultDir);
			int i = 0;
			while (defaultDir[i] != '\0')
				i++;
			char* temp = "\\File";
			for (int j = 0; j <= strlen(temp); j++)
				defaultDir[i + j] = temp[j];
			sendTo(socket, message("get-server-path-response", (char*)defaultDir, sizeof defaultDir));

		}
		delete msg;
		break;

	}
	}
	return 0;

}

void CServerDlg::OnBnClickedListen()
{

	if (control.listenConnection(m_hWnd))
	{

		serverLog.AddString(L">>");
		serverLog.AddString(L"Established connection successfully.");
		serverLog.AddString(L"Server is listening connection from client...");
		//In 1 dong trong de co the de doc lich su thao tac giua client va server
		serverLog.AddString(L"");
		this->listenButton.EnableWindow(FALSE);

	}
	else
	{

		serverLog.AddString(L">>");
		serverLog.AddString(L"Failed to establish connection.");
		//In 1 dong trong de co the de doc lich su thao tac giua client va server
		serverLog.AddString(L"");

	}

}


void CServerDlg::OnBnClickedCancel()
{

	control.closeServer();
	CDialogEx::OnCancel();

}

void CServerDlg::PrintFileList()
{

	//Xoa man hinh cua fileListLog
	while (fileListLog.GetCount() > 0)
	{

		fileListLog.DeleteString(0);

	}
	vector<string> a;
	string path = ".\\File\\*";
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(convertCharToCString(path.c_str()), &data)) != INVALID_HANDLE_VALUE)
	{

		do
		{

			if (data.cFileName[0] != '.')
			{

				fileListLog.AddString(data.cFileName);

			}

		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);

	}

}
