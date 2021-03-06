
// AutoChangeBlackMapDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "AutoChangeBlackMap.h"
#include "AutoChangeBlackMapDlg.h"
#include "afxdialogex.h"
//#include "string"

//using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoChangeBlackMapDlg 对话框



CAutoChangeBlackMapDlg::CAutoChangeBlackMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOCHANGEBLACKMAP_DIALOG, pParent)
	, m_pass(_T(""))
	, m_pass1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoChangeBlackMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA, m_text);
	DDX_Text(pDX, IDC_EDIT1, m_pass);
	DDX_Text(pDX, IDC_EDIT2, m_pass1);
}

BEGIN_MESSAGE_MAP(CAutoChangeBlackMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoChangeBlackMapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoChangeBlackMapDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CAutoChangeBlackMapDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAutoChangeBlackMapDlg 消息处理程序

BOOL CAutoChangeBlackMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	//初始化欢迎界面
	m_Font.CreatePointFont(200, _T("Arial"), NULL);
	m_text.SetFont(&m_Font, true);
	m_text.SetWindowTextW(_T("欢迎使用自动换黑图小工具\n请使用压缩包内自带的黑图文件\n或自行下载"));

	/*//初始化读入黑图文件路径文本框
	m_Font1.CreatePointFont(100, _T("Arial"), NULL);
	m_text1.SetFont(&m_Font1, true);
	m_text1.SetWindowTextW(_T("请选择黑图路径"));

	//初始化读入游戏路径文本框
	m_Font2.CreatePointFont(100, _T("Arial"), NULL);
	m_text2.SetFont(&m_Font2, true);
	m_text2.SetWindowTextW(_T("请选择游戏路径"));*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoChangeBlackMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAutoChangeBlackMapDlg::OnPaint()
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
HCURSOR CAutoChangeBlackMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoChangeBlackMapDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CFileDialog BMOpenFile(1,0,0,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("文件类型(*.pak)|*.pak||"));//生成一个对话框
	if (BMOpenFile.DoModal() == IDOK)//假如点击对话框确定按钮
	{
		m_pass = BMOpenFile.GetPathName();  //得到打开文件的路径
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(m_pass);     //在窗口标题上显示路径
	}
	delete BMOpenFile;    //释放分配的对话框
}


void CAutoChangeBlackMapDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("请选择到最底层的“QQ音速”文件夹，不需要向下继续选择其他文件夹"));
	BROWSEINFO GameOpenFile; //创建一个可以指定文件夹的结构体
	
	GameOpenFile.hwndOwner = NULL;
	GameOpenFile.pidlRoot = CSIDL_DESKTOP;//文件夹的根目录，此处为桌面
	GameOpenFile.pszDisplayName = NULL;
	GameOpenFile.lpszTitle = NULL;//显示位于对话框左上部的提示信息
	GameOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//有新建文件夹按钮
	GameOpenFile.lpfn = NULL;
	GameOpenFile.iImage = 0;
	LPITEMIDLIST pidl = SHBrowseForFolder(&GameOpenFile);//调用选择对话框
	if (pidl == NULL)
	{
		MessageBox(_T("请重新选择游戏路径！"));
		return;
	}
	TCHAR strFolder[1024];
	SHGetPathFromIDList(pidl, strFolder);
	m_pass1 = strFolder;
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(m_pass1);     //在窗口标题上显示路径
	if (GameOpenFile.pidlRoot != CSIDL_DESKTOP)
		delete pidl;    //释放分配的对话框
}


void CAutoChangeBlackMapDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	if (m_pass.IsEmpty())
	{
		MessageBox(_T("请选择黑图文件！"));
		return;
	}
	
	if (m_pass1.IsEmpty())
	{
		MessageBox(_T("请选择游戏路径！"));
		return;
	}

	//替换路径中的\为\\.....
	m_pass.Replace(_T("\\"),_T("\\\\"));
	m_pass1.Replace(_T("\\"), _T("\\\\"));

	//得到字符串长度
	//int l = m_pass.GetLength();  
	//int l1 = m_pass1.GetLength();

	//查找最后一个“//”的位置
	//int p = m_pass.ReverseFind('\\');
	//int p1 = m_pass1.ReverseFind('\\');
	CString pass = m_pass1+ _T("\\rnr_bg\\back11.pak");

	//将CString转换为LPCWSTR
	LPCWSTR M_PASS = m_pass.AllocSysString(); 
	LPCWSTR M_PASS1 = pass.AllocSysString();
	//LPCWSTR M_PASS = A2CW((LPCSTR)m_pass);
	//LPCWSTR M_PASS1 = A2CW((LPCSTR)pass);
	CopyFile(M_PASS, M_PASS1, FALSE);  //替换文件
	MessageBox(_T("成功！"));
}
