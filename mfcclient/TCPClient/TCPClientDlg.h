
// TCPClientDlg.h : ͷ�ļ�
//

#pragma once


// CTCPClientDlg �Ի���
class CTCPClientDlg : public CDialogEx
{
// ����
public:
	CTCPClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

