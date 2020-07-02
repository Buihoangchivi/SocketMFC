
// ClientDlg.h : header file
//

#pragma once
#include <afxsock.h>
#include "ClientControl.h"
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
using namespace std;


// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	char str_msg[50];
	bool isConnected;
	SOCKET sk;
	SOCKADDR_IN serverAddress;
	char username[20];
	account getAccountInfo();
	void connectToServer();
	ofstream f;
	CClientControl ctr;

public:
	afx_msg void OnBnClickedSignin();
	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedDownload();
	afx_msg void OnBnClickedUpload();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedCancel2();
	CButton signInButton;
	CButton downLoadButton;
	CButton upLoadButton;
	CButton logOutButton;
	CButton registerButton;
	CButton cancelButton1;
	CButton cancelButton2;
	CEdit userText;
	CEdit passwordText;
	CListBox clientLog;
	CListBox userListLog;
	CListBox fileListLog;
	CEdit textBox;
	LRESULT eventsControl(WPARAM wParam, LPARAM lParam);

};
