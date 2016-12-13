
// TCPClientDlg.h : 头文件
//

#pragma once


// CTCPClientDlg 对话框
class CTCPClientDlg : public CDialogEx
{
// 构造
public:
	CTCPClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();

private:
	SOCKET st;
	sockaddr_in client;
	int length;
	CEdit *m_EditIP;
	CEdit *m_EditPort;
	CEdit *m_EditRecv;
	CEdit *m_EditSend;
public:
	afx_msg void OnBnClickedButtonSend();
};

