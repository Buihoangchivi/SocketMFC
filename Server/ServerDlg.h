
// ServerDlg.h : header file
//

#pragma once

#include "ServerControl.h"

// CServerDlg dialog
class CServerDlg : public CDialogEx
{
// Construction
public:
	CServerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CServerControl control;
	ifstream f;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT eventsControl(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedListen();
	afx_msg void OnBnClickedCancel();
	CListBox serverLog;
	CListBox userLog;
	CButton listenButton;
};
