
// ServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

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

		serverLog.AddString(L"Server connected to database.");

	}
	else
	{

		serverLog.AddString(L"Database file doesn't exist. Program has created a new empty database file.");

	}

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

				string response = control.authenticate(socket, *msg, userLog);
				serverLog.AddString(convertCharToCString(response.c_str()));
				//userLog.GetCount();

			}
			catch (int) {}

		}
		if (strcmp("download", msg->action) == 0)
		{

			char fileName[100];
			strcpy(fileName, msg->content);
			//filename[nameLength] = '\0';
			//
			//int end = 0;
			bool ok;
			f.open(fileName, ios::in | ios::binary | ios::ate);
			f.seekg(0, SEEK_SET);
			if (!f)
			{

				f.close();
				ok = false;
				goto return_result;

			}
			
			while (!f.eof())
			{

				//int length = 0;
				//int byte = 0;
				char* buff = new char[256];
				f.read(buff, 255);
				//cout << buff;
				//tempClient->sk.Send(&end, sizeof(int), 0);
				//length = 4096;
				//tempClient->sk.Send(&length, sizeof(int), 0);
				sendTo(socket, message("download-response", buff));
				/*byte = tempClient->sk.Send(buff, length, 0);
				if (byte <= 0)
				{

					ok = false;
					goto return_result;

				}*/
				ZeroMemory(buff, 256);

			}
			//end = 1;
			//tempClient->sk.Send(&end, sizeof(int), 0);
			ok = true;

		return_result:
			string response = control.sendResultDownloadFile(socket, ok);
			serverLog.AddString(convertCharToCString(response.c_str()));

		}
		if (strcmp("upload-file", msg->action) == 0)
		{

			//control.CreateForWriting(socket, msg->content);
			control.CreateForWriting();

		}
		if (strcmp("upload-file-part", msg->action) == 0)
		{

			control.SaveFile(socket, msg->content);

		}
		if (strcmp("request-file", msg->action) == 0)
		{

			control.CreateForReading(socket, msg->content);

		}
		if (strcmp("request-file-part", msg->action) == 0)
		{

			control.SendFile(socket, msg->content);

		}
		if (strcmp("logout", msg->action) == 0)
		{

			string response = control.logoutAccount(msg->content, userLog);
			serverLog.AddString(convertCharToCString(response.c_str()));

		}
		if (strcmp("cancel", msg->action) == 0)
		{

			string response = control.cancelAccount(msg->content, userLog);
			serverLog.AddString(convertCharToCString(response.c_str()));

		}
		delete msg;
		break;

	}
	/*case FD_CLOSE:
	{

		try
		{

			string response = control.logoutAccount(socket, userLog);
			serverLog.AddString(convertCharToCString(response.c_str()));

		}
		catch (int) {}
		break;

	}*/
	}
	return 0;

}

void CServerDlg::OnBnClickedListen()
{

	if (control.listenConnection(m_hWnd))
	{

		serverLog.AddString(L"Established connection successfully.");
		serverLog.AddString(L"Server is listening connection from client...");
		this->listenButton.EnableWindow(FALSE);

	}
	else
	{

		serverLog.AddString(L"Failed to establish connection.");

	}

}


void CServerDlg::OnBnClickedCancel()
{

	control.closeServer();
	CDialogEx::OnCancel();

}
