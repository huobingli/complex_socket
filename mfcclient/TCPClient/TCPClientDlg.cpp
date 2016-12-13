
// TCPClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPClient.h"
#include "TCPClientDlg.h"
#include "afxdialogex.h"

#include <algorithm>
#include <cmath>
#include <WinSock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTCPClientDlg �Ի���



CTCPClientDlg::CTCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCPClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CTCPClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTCPClientDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CTCPClientDlg ��Ϣ�������

BOOL CTCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
	{
		AfxMessageBox(_T("���ؿ�ʧ�ܣ�"));
		return 0;
	}

	st = 0;
	st = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	client.sin_family = AF_INET;
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTCPClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCPClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCPClientDlg::OnBnClickedButtonConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ip;
	CString port;
	m_EditIP = (CEdit*)GetDlgItem(IDC_EDIT_IP);
	m_EditIP->GetWindowText(ip);
	m_EditPort = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	m_EditPort->GetWindowText(port);

	if (ip.GetLength() == 0 || port.GetLength() == 0) {
		AfxMessageBox("��������ȫ");
		return;
	}
	CString bangding = "��";
	CString he = "��";
	AfxMessageBox(bangding + ip.GetBuffer(0) + he + port);
	const char *ipbuffer = (LPSTR)(LPCTSTR)ip;

	char ipbuf[20];
	memset(ipbuf, 0, sizeof(ipbuf));
	strcpy(ipbuf, ipbuffer);

	client.sin_addr.s_addr = inet_addr(ipbuf);

	char portbuf[6];
	const char *portbuffer = (LPSTR)(LPCTSTR)port;
	memset(portbuf, 0, sizeof(portbuf));
	strcpy(portbuf, portbuffer);

	int iPort = 0;
	int length = strlen(portbuf);
	for (int i = 0; i < length; i++) {
		iPort = iPort + (portbuf[i] - '0') * pow(10, (length - i - 1));
	}

	client.sin_port = htons(iPort);

	length = sizeof(client);
	int i = connect(st, (struct sockaddr*)& client, length);
	if (i == 0) {
		MessageBox("���ӳɹ�");
	}
	else if (i == -1) {
		MessageBox("����ʧ��");
	}
	else
	{
		MessageBox("����failed");
	}


}


void CTCPClientDlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sendBuffer;
	m_EditSend = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

	m_EditSend->GetWindowText(sendBuffer);
	
	const char *buffer = (LPSTR)(LPCTSTR)sendBuffer;

	int i = send(st, buffer, strlen(buffer), 0);

}
