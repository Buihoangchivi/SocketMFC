
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isConnected = false;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDSIGNIN, signInButton);
	DDX_Control(pDX, DOWNLOAD, downLoadButton);
	DDX_Control(pDX, UPLOAD, upLoadButton);
	DDX_Control(pDX, LOGOUT, logOutButton);
	DDX_Control(pDX, IDREGISTER, registerButton);
	DDX_Control(pDX, IDCANCEL, cancelButton1);
	DDX_Control(pDX, IDCANCEL2, cancelButton2);
	DDX_Control(pDX, IDC_EDIT1, userText);
	DDX_Control(pDX, IDC_EDIT2, passwordText);
	DDX_Control(pDX, IDC_LIST1, clientLog);
	DDX_Control(pDX, IDC_LIST2, userListLog);
	DDX_Control(pDX, IDC_LIST3, fileListLog);
	DDX_Control(pDX, IDC_EDIT3, textBox);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER + 1, eventsControl)
	ON_BN_CLICKED(IDSIGNIN, &CClientDlg::OnBnClickedSignin)
	ON_BN_CLICKED(IDREGISTER, &CClientDlg::OnBnClickedRegister)
	ON_BN_CLICKED(DOWNLOAD, &CClientDlg::OnBnClickedDownload)
	ON_BN_CLICKED(UPLOAD, &CClientDlg::OnBnClickedUpload)
	ON_BN_CLICKED(LOGOUT, &CClientDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDCANCEL2, &CClientDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::connectToServer() {
	if (isConnected == false) {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
			return;
		}

		UpdateData();
		sk = socket(AF_INET, SOCK_STREAM, 0);
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(1234);
		serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

		int err = connect(sk, (SOCKADDR*)&serverAddress, sizeof serverAddress);
		if (err == SOCKET_ERROR) {
			return;
		}
		isConnected = true;
		WSAAsyncSelect(sk, m_hWnd, WM_USER + 1, FD_READ | FD_CLOSE);
	}
}

account CClientDlg::getAccountInfo()
{

	CString username;
	CString password;
	GetDlgItemText(IDC_EDIT1, username);
	GetDlgItemText(IDC_EDIT2, password);

	account auth;
	strcpy(auth.username, convertCStringToChar(username));
	strcpy(auth.password, convertCStringToChar(password));
	strcpy(this->username, convertCStringToChar(username));
	return auth;

}

void CClientDlg::OnBnClickedSignin()
{
	// TODO: Add your control notification handler code here
	connectToServer();
	account auth = getAccountInfo();
	message msg;
	strcpy(msg.action, "login");
	memcpy(msg.content, (char*)&auth, sizeof auth);
	sendTo(sk, msg);

}


void CClientDlg::OnBnClickedRegister()
{

	connectToServer();
	account auth = getAccountInfo();
	message msg;
	strcpy(msg.action, "register");
	memcpy(msg.content, (char*)&auth, sizeof auth);
	sendTo(sk, msg);

}


void CClientDlg::OnBnClickedDownload()
{

	CString uploadname;
	GetDlgItemText(IDC_EDIT3, uploadname);
	string filename;
	//cin >> filename;
	/*filename = "C:\\Users\\buiva\\Desktop";
	char* upName = convertCStringToChar(uploadname);
	upName[strlen(upName)] = '\0';
	sendTo(sk, message("download", upName));
	f.open(filename, ios::out | ios::binary);*/

}


void CClientDlg::OnBnClickedUpload()
{
	
	CString uploadname;
	GetDlgItemText(IDC_EDIT3, uploadname);
	sprintf(str_msg, "Uploading %s", convertCStringToChar(uploadname));
	string s = (string)str_msg;
	clientLog.AddString(convertCharToCString(s.c_str()));

	ctr.SendFile(sk, convertCStringToChar(uploadname));

	sprintf(str_msg, "Finished uploading %s", convertCStringToChar(uploadname));
	s = (string)str_msg;
	clientLog.AddString(convertCharToCString(s.c_str()));

}


void CClientDlg::OnBnClickedLogout()
{

	sendTo(sk, message("logout", username));
	closesocket(sk);
	CClientDlg dlg;
	EndDialog(0);
	dlg.DoModal();

}


void CClientDlg::OnBnClickedCancel2()
{

	sendTo(sk, message("cancel", username));
	closesocket(sk);
	CDialogEx::OnCancel();

}

LRESULT CClientDlg::eventsControl(WPARAM wParam, LPARAM lParam)
{

	if (WSAGETSELECTERROR(lParam))
	{

		closesocket(wParam);
		return 0;

	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{

		message* msg = new message;
		receiveFrom(wParam, *msg);
		if (strcmp(msg->action, "login-response") == 0)
		{

			if (strcmp(msg->content, "OK") == 0)
			{

				this->signInButton.ShowWindow(SW_HIDE);
				this->registerButton.ShowWindow(SW_HIDE);
				this->cancelButton1.ShowWindow(SW_HIDE);
				this->userText.ShowWindow(SW_HIDE);
				this->passwordText.ShowWindow(SW_HIDE);
				this->clientLog.ShowWindow(SW_SHOW);
				this->userListLog.ShowWindow(SW_SHOW);
				this->fileListLog.ShowWindow(SW_SHOW);
				this->textBox.ShowWindow(SW_SHOW);
				this->downLoadButton.ShowWindow(SW_SHOW);
				this->upLoadButton.ShowWindow(SW_SHOW);
				this->logOutButton.ShowWindow(SW_SHOW);
				this->cancelButton2.ShowWindow(SW_SHOW);
				sprintf(str_msg, "Login successfully.");
				string s = (string)str_msg;
				clientLog.AddString(convertCharToCString(s.c_str()));

			}
			else
			{

				sprintf(str_msg, "Fail to login.");
				string s = (string)str_msg;
				clientLog.AddString(convertCharToCString(s.c_str()));
				MessageBox(CString(msg->content));

			}

		}
		if (strcmp(msg->action, "new-user") == 0)
		{

			sprintf(str_msg, "New user %s registered.", msg->content);
			string s = (string)str_msg;
			clientLog.AddString(convertCharToCString(s.c_str()));

		}
		if (strcmp(msg->action, "new-login") == 0)
		{

			sprintf(str_msg, "User %s logged in.", msg->content);
			string s = (string)str_msg;
			clientLog.AddString(convertCharToCString(s.c_str()));

		}
		if (strcmp(msg->action, "logout") == 0)
		{

			sprintf(str_msg, "User %s logged out.", msg->content);
			string s = (string)str_msg;
			clientLog.AddString(convertCharToCString(s.c_str()));

		}
		if (strcmp(msg->action, "cancel") == 0)
		{

			sprintf(str_msg, "User %s canceled.", msg->content);
			string s = (string)str_msg;
			clientLog.AddString(convertCharToCString(s.c_str()));

		}
		if (strcmp(msg->action, "close-server") == 0)
		{

			//Dong socket
			closesocket(sk);
			CClientDlg dlg;
			EndDialog(0);
			dlg.DoModal();

		}
		if (strcmp(msg->action, "upload-file-response") == 0) {
			ctr.SendFilePart(msg->content);
		}
		if (strcmp(msg->action, "request-file-response") == 0) {
			//ctr.ReceiveFilePart(msg->content);
		}
		if (strcmp(msg->action, "download-response") == 0)
		{

			/*char* buff = new char[524];
			strcpy(buff, msg->content);
			f.write(buff, strlen(buff));
			ZeroMemory(buff, strlen(buff));*/
			/*f.write(msg->content, strlen(msg->content));
			ZeroMemory(msg->content, strlen(msg->content));*/

		}
		if (strcmp(msg->action, "stop-download") == 0)
		{

			if (strcmp(msg->content, "1") == 0)
				clientLog.AddString(L"Download successfully.");
			else
				clientLog.AddString(L"Fail to download file.");
			f.close();

		}
		delete msg;
		break;

	}
	}
	return 0;

}