
// MFCPracticeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCPractice.h"
#include "MFCPracticeDlg.h"
#include "afxdialogex.h"


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*extern "C" __declspec(dllexport)void ShowDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CMFCPracticeDlg dlg;
	dlg.DoModal();
}*///显示调用接口函数 每次使用时还需注释 the app 和InitInstance中的创建dlg



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


// CMFCPracticeDlg 对话框



CMFCPracticeDlg::CMFCPracticeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCPRACTICE_DIALOG, pParent)
	, m_direction(_T(""))
	, m_Tg(0)
	, m_Ta(0)
	, m_maxacc(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPracticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_direction);
	DDX_Text(pDX, IDC_EDIT3, m_Tg);
	DDX_Text(pDX, IDC_EDIT2, m_Ta);
	DDX_Text(pDX, IDC_EDIT4, m_maxacc);
}

BEGIN_MESSAGE_MAP(CMFCPracticeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETNAME, &CMFCPracticeDlg::OnBnClickedButtonGetname)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMFCPracticeDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_GETCONTENT, &CMFCPracticeDlg::OnBnClickedButtonGetcontent)
END_MESSAGE_MAP()


// CMFCPracticeDlg 消息处理程序

BOOL CMFCPracticeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T("文件名"), LVCFMT_CENTER, 200);
	m_list.InsertColumn(1, _T("文件类型"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("存放路径"), LVCFMT_LEFT, 500);
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCPracticeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCPracticeDlg::OnPaint()
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
HCURSOR CMFCPracticeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCPracticeDlg::OnBnClickedButtonGetname()//获取.txt文件按钮
{
	
	CFileDialog dlg(TRUE);//弹出打开文件对话框
	CString cFilePath;
	CString cFileName;
	if (dlg.DoModal() == IDOK)
		cFileName = dlg.GetPathName();
	else
		cFileName.Empty();
	int iEndPos = 0;
	iEndPos = cFileName.ReverseFind('\\');
	cFilePath = cFileName.Left(iEndPos);//获取文件夹路径

	m_list.DeleteAllItems();
	CFileFind finder;
	CString cFileType = _T(".txt");
	CString cFullPath= cFilePath + _T("\\*")+ cFileType;//获取文件全路径地址

	BOOL bworking = finder.FindFile(cFullPath);
	if (bworking == 0)
	{
		MessageBox(TEXT("未成功读取当前文件夹"));
	}
	int index = 0;//用于列表索引

	CString cFullName;
	while (bworking)//读取文件名并处理，将地址、格式挂载到list控件
	{
		bworking = finder.FindNextFile();
		cFullName = finder.GetFileName();
		
		if (cFullName != _T(".")&& cFullName != _T(".."))
		{
					int iEndPos = 0;
					iEndPos = cFullName.ReverseFind('.');
					cFileName = cFullName.Left(iEndPos);//读取文件名
					m_list.InsertItem(index, cFileName);//必选先InsertItem再SetItem
					m_list.SetItemText(index, 1, cFileType);
					m_list.SetItemText(index, 2, cFilePath);
		}
		index++;
	}
			
}



void CMFCPracticeDlg::OnBnClickedButtonSave()//另存为.dat按钮
{
	int nIndex = m_list.GetSelectionMark();//获取list控件中高亮选中的文件索引
	if (nIndex != -1)
	{

		CString cFileName = m_list.GetItemText(nIndex, 0);
		CString cFileType = m_list.GetItemText(nIndex, 1);
		CString cFilePath = m_list.GetItemText(nIndex, 2);
		CString cFullPath = cFilePath + _T("\\") + cFileName + cFileType;//获取list控件中高亮选中的文件全路径地址
		CStdioFile file;//CStdio可以逐行读取
		BOOL ret = file.Open(cFullPath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("打开文件失败"));
			return;
		}
		file.SeekToBegin();// 将文件指针指向文件开始处
		CString cStrLine;
		vector <CString> vTga;//用来存储特征值和时间间隔
		vector<CString> vWord;//用来存储文字
		
		//读取前三行的数据
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cStrLine);
			CString left = cStrLine.Left(cStrLine.Find('\t'));
			CString right = cStrLine.Mid((cStrLine.Find('\t')+1));
			vWord.push_back(left);
			vTga.push_back(right);
		}
		//读取前三行后的加速度数据
		vector <CString> vAcc;
		
		for(int i=0;file.ReadString(cStrLine)!=0;i++)
		{
			vAcc.push_back(cStrLine);
		}
		
		file.Close();	// 关闭文件 
		
		CStdioFile filedat;
		CString cNewFileType = _T(".dat");
		CString cNewPath = cFilePath + _T("\\") + cFileName + cNewFileType;//新的.dat文件全路径地址
		BOOL ret1=filedat.Open(cNewPath, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);//创建新的.dat文件写入
		if (!ret1)
		{
			MessageBox(TEXT("创建文件失败"));
			return;
		}
		filedat.SeekToEnd();
		CString string1 = vTga[0] + _T (",") + vTga[1] + _T("\n");
		filedat.WriteString(string1);
		for (int i = 0; i<vAcc.size(); i++)
		{
			filedat.WriteString(vAcc[i]+ _T("\n"));
		}
		MessageBox(TEXT("成功另存为.dat文件"));
	}
	else
	{
		MessageBox(TEXT("请先在列表选择需另存为.dat的文件"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCPracticeDlg::OnBnClickedButtonGetcontent()//读取内容按钮
{
	int nIndex = m_list.GetSelectionMark();//获取list控件中高亮选中的文件索引
	if (nIndex != -1)
	{

		CString cFileName = m_list.GetItemText(nIndex, 0);
		CString cDirection = cFileName.Mid(cFileName.ReverseFind('(')+1, 1);//获取方向
		CString cFileType = m_list.GetItemText(nIndex, 1);
		CString cFilePath = m_list.GetItemText(nIndex, 2);
		CString cFullPath = cFilePath + _T("\\") + cFileName + cFileType;//获取list控件中高亮选中的文件全路径地址
		CStdioFile file;
		BOOL ret = file.Open(cFullPath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("打开文件失败"));
			return;
		}
		file.SeekToBegin();// 将文件指针指向文件开始处
		CString cStrLine;
		vector <CString> vTga;//用来存储特征值和时间间隔
		vector <CString> vWord;//用来存储文字

		//读取前三行的数据
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cStrLine);
			CString left = cStrLine.Left(cStrLine.Find('\t'));
			CString right = cStrLine.Mid((cStrLine.Find('\t') + 1));
			vWord.push_back(left);
			vTga.push_back(right);
		}
		float fTg = _ttof(vTga[0]);//获取特征周期
		float fTa = _ttof(vTga[1]);//获取时间间隔

		//读取前三行后的加速度数据
		vector<float>vAcc;
		for (int i = 0; file.ReadString(cStrLine) != 0; i++)
		{
			vAcc.push_back(_ttof(cStrLine));
		}
		float fMaxacc = *max_element(vAcc.begin(), vAcc.end());//vector找最大值
		m_direction = cDirection;//赋值控件变量
		m_Tg = fTg;
		m_Ta = fTa;
		m_maxacc = fMaxacc;
		UpdateData(FALSE);//更新到对应的控件
	}
	else
	{
		MessageBox(TEXT("请先在右侧列表选择文件"));
	}

	// TODO: 在此添加控件通知处理程序代码
}
