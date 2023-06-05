
// MFCPracticeDlg.cpp : ʵ���ļ�
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
}*///��ʾ���ýӿں��� ÿ��ʹ��ʱ����ע�� the app ��InitInstance�еĴ���dlg



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCPracticeDlg �Ի���



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


// CMFCPracticeDlg ��Ϣ�������

BOOL CMFCPracticeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T("�ļ���"), LVCFMT_CENTER, 200);
	m_list.InsertColumn(1, _T("�ļ�����"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("���·��"), LVCFMT_LEFT, 500);
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCPracticeDlg::OnPaint()
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
HCURSOR CMFCPracticeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCPracticeDlg::OnBnClickedButtonGetname()//��ȡ.txt�ļ���ť
{
	
	CFileDialog dlg(TRUE);//�������ļ��Ի���
	CString cFilePath;
	CString cFileName;
	if (dlg.DoModal() == IDOK)
		cFileName = dlg.GetPathName();
	else
		cFileName.Empty();
	int iEndPos = 0;
	iEndPos = cFileName.ReverseFind('\\');
	cFilePath = cFileName.Left(iEndPos);//��ȡ�ļ���·��

	m_list.DeleteAllItems();
	CFileFind finder;
	CString cFileType = _T(".txt");
	CString cFullPath= cFilePath + _T("\\*")+ cFileType;//��ȡ�ļ�ȫ·����ַ

	BOOL bworking = finder.FindFile(cFullPath);
	if (bworking == 0)
	{
		MessageBox(TEXT("δ�ɹ���ȡ��ǰ�ļ���"));
	}
	int index = 0;//�����б�����

	CString cFullName;
	while (bworking)//��ȡ�ļ�������������ַ����ʽ���ص�list�ؼ�
	{
		bworking = finder.FindNextFile();
		cFullName = finder.GetFileName();
		
		if (cFullName != _T(".")&& cFullName != _T(".."))
		{
					int iEndPos = 0;
					iEndPos = cFullName.ReverseFind('.');
					cFileName = cFullName.Left(iEndPos);//��ȡ�ļ���
					m_list.InsertItem(index, cFileName);//��ѡ��InsertItem��SetItem
					m_list.SetItemText(index, 1, cFileType);
					m_list.SetItemText(index, 2, cFilePath);
		}
		index++;
	}
			
}



void CMFCPracticeDlg::OnBnClickedButtonSave()//���Ϊ.dat��ť
{
	int nIndex = m_list.GetSelectionMark();//��ȡlist�ؼ��и���ѡ�е��ļ�����
	if (nIndex != -1)
	{

		CString cFileName = m_list.GetItemText(nIndex, 0);
		CString cFileType = m_list.GetItemText(nIndex, 1);
		CString cFilePath = m_list.GetItemText(nIndex, 2);
		CString cFullPath = cFilePath + _T("\\") + cFileName + cFileType;//��ȡlist�ؼ��и���ѡ�е��ļ�ȫ·����ַ
		CStdioFile file;//CStdio�������ж�ȡ
		BOOL ret = file.Open(cFullPath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("���ļ�ʧ��"));
			return;
		}
		file.SeekToBegin();// ���ļ�ָ��ָ���ļ���ʼ��
		CString cStrLine;
		vector <CString> vTga;//�����洢����ֵ��ʱ����
		vector<CString> vWord;//�����洢����
		
		//��ȡǰ���е�����
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cStrLine);
			CString left = cStrLine.Left(cStrLine.Find('\t'));
			CString right = cStrLine.Mid((cStrLine.Find('\t')+1));
			vWord.push_back(left);
			vTga.push_back(right);
		}
		//��ȡǰ���к�ļ��ٶ�����
		vector <CString> vAcc;
		
		for(int i=0;file.ReadString(cStrLine)!=0;i++)
		{
			vAcc.push_back(cStrLine);
		}
		
		file.Close();	// �ر��ļ� 
		
		CStdioFile filedat;
		CString cNewFileType = _T(".dat");
		CString cNewPath = cFilePath + _T("\\") + cFileName + cNewFileType;//�µ�.dat�ļ�ȫ·����ַ
		BOOL ret1=filedat.Open(cNewPath, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);//�����µ�.dat�ļ�д��
		if (!ret1)
		{
			MessageBox(TEXT("�����ļ�ʧ��"));
			return;
		}
		filedat.SeekToEnd();
		CString string1 = vTga[0] + _T (",") + vTga[1] + _T("\n");
		filedat.WriteString(string1);
		for (int i = 0; i<vAcc.size(); i++)
		{
			filedat.WriteString(vAcc[i]+ _T("\n"));
		}
		MessageBox(TEXT("�ɹ����Ϊ.dat�ļ�"));
	}
	else
	{
		MessageBox(TEXT("�������б�ѡ�������Ϊ.dat���ļ�"));
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCPracticeDlg::OnBnClickedButtonGetcontent()//��ȡ���ݰ�ť
{
	int nIndex = m_list.GetSelectionMark();//��ȡlist�ؼ��и���ѡ�е��ļ�����
	if (nIndex != -1)
	{

		CString cFileName = m_list.GetItemText(nIndex, 0);
		CString cDirection = cFileName.Mid(cFileName.ReverseFind('(')+1, 1);//��ȡ����
		CString cFileType = m_list.GetItemText(nIndex, 1);
		CString cFilePath = m_list.GetItemText(nIndex, 2);
		CString cFullPath = cFilePath + _T("\\") + cFileName + cFileType;//��ȡlist�ؼ��и���ѡ�е��ļ�ȫ·����ַ
		CStdioFile file;
		BOOL ret = file.Open(cFullPath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("���ļ�ʧ��"));
			return;
		}
		file.SeekToBegin();// ���ļ�ָ��ָ���ļ���ʼ��
		CString cStrLine;
		vector <CString> vTga;//�����洢����ֵ��ʱ����
		vector <CString> vWord;//�����洢����

		//��ȡǰ���е�����
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cStrLine);
			CString left = cStrLine.Left(cStrLine.Find('\t'));
			CString right = cStrLine.Mid((cStrLine.Find('\t') + 1));
			vWord.push_back(left);
			vTga.push_back(right);
		}
		float fTg = _ttof(vTga[0]);//��ȡ��������
		float fTa = _ttof(vTga[1]);//��ȡʱ����

		//��ȡǰ���к�ļ��ٶ�����
		vector<float>vAcc;
		for (int i = 0; file.ReadString(cStrLine) != 0; i++)
		{
			vAcc.push_back(_ttof(cStrLine));
		}
		float fMaxacc = *max_element(vAcc.begin(), vAcc.end());//vector�����ֵ
		m_direction = cDirection;//��ֵ�ؼ�����
		m_Tg = fTg;
		m_Ta = fTa;
		m_maxacc = fMaxacc;
		UpdateData(FALSE);//���µ���Ӧ�Ŀؼ�
	}
	else
	{
		MessageBox(TEXT("�������Ҳ��б�ѡ���ļ�"));
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
