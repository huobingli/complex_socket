
// TCPClientDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTCPClientDlg 对话框



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


// CTCPClientDlg 消息处理程序

BOOL CTCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
	{
		AfxMessageBox(_T("加载库失败！"));
		return 0;
	}

	st = 0;
	st = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	client.sin_family = AF_INET;
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCPClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCPClientDlg::OnBnClickedButtonConnect()
{
	// TODO:  在此添加控件通知处理程序代码
	CString ip;
	CString port;
	m_EditIP = (CEdit*)GetDlgItem(IDC_EDIT_IP);
	m_EditIP->GetWindowText(ip);
	m_EditPort = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	m_EditPort->GetWindowText(port);

	if (ip.GetLength() == 0 || port.GetLength() == 0) {
		AfxMessageBox("请输入完全");
		return;
	}
	CString bangding = "绑定";
	CString he = "和";
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
		MessageBox("连接成功");
	}
	else if (i == -1) {
		MessageBox("连接失败");
	}
	else
	{
		MessageBox("连接failed");
	}


}


void CTCPClientDlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	CString sendBuffer;
	m_EditSend = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

	m_EditSend->GetWindowText(sendBuffer);
	
	const char *buffer = (LPSTR)(LPCTSTR)sendBuffer;

	int i = send(st, buffer, strlen(buffer), 0);

}
