
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



void CMFCPracticeDlg::OnBnClickedButtonGetname()
{
	
	CFileDialog dlg(TRUE);//�������ļ��Ի���
	CString filepath;
	CString m_csFileName;
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();
	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	filepath = m_csFileName.Left(iEndPos);//��ȡ�ļ���·��

	m_list.DeleteAllItems();
	CFileFind finder;
	CString filetype = _T(".txt");
	CString strwildcard= filepath + _T("\\*")+ filetype;//��ȡ�ļ�ȫ·����ַ

	BOOL bworking = finder.FindFile(strwildcard);
	if (bworking == 0)
	{
		MessageBox(TEXT("δ�ɹ���ȡ��ǰ�ļ���"));
	}
	int index = 0;//�����б�����

	CString filename, fullname;
	while (bworking)
	{
		bworking = finder.FindNextFile();
		fullname = finder.GetFileName();
		
		if (fullname != _T(".")&& fullname != _T(".."))
		{
					int iEndPos = 0;
					iEndPos = fullname.ReverseFind('.');
					filename = fullname.Left(iEndPos);//��ȡ�ļ���
					m_list.InsertItem(index, filename);
					m_list.SetItemText(index, 1, filetype);
					m_list.SetItemText(index, 2, filepath);
		}
		index++;
	}
			
}



void CMFCPracticeDlg::OnBnClickedButtonSave()
{
	int nIndex = m_list.GetSelectionMark();//��ȡlist�ؼ��и���ѡ�е��ļ�����
	if (nIndex != -1)
	{

		CString filename = m_list.GetItemText(nIndex, 0);
		CString filetype = m_list.GetItemText(nIndex, 1);
		CString filepath = m_list.GetItemText(nIndex, 2);
		CString fullpath = filepath + _T("\\") + filename + filetype;//��ȡlist�ؼ��и���ѡ�е��ļ�ȫ·����ַ
		CStdioFile file;//CStdio�������ж�ȡ
		BOOL ret = file.Open(fullpath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("���ļ�ʧ��"));
			return;
		}
		file.SeekToBegin();// ���ļ�ָ��ָ���ļ���ʼ��
		CString cstrLine;
		CArray <CString, CString>Tga;//���������������ں�ʱ���� 
		CArray <CString, CString>Word;//��������
		Tga.SetSize(10);
		Word.SetSize(10);
		//��ȡǰ���е�����
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cstrLine);
			CString left = cstrLine.Left(cstrLine.Find('\t'));
			CString right = cstrLine.Mid((cstrLine.Find('\t')+1));
			Word.SetAt(i, left);
			Tga.SetAt(i, right);
		}
		//��ȡǰ���к�ļ��ٶ�����
		CArray <CString, CString>Acc;
		Acc.SetSize(50);
		for(int i=0;file.ReadString(cstrLine)!=0;i++)
		{
			Acc.SetAt(i,cstrLine);
		}
		
		file.Close();	// �ر��ļ� 
		
		CStdioFile filedat;
		CString newfiletype = _T(".dat");
		CString newpath = filepath + _T("\\") + filename + newfiletype;//�µ�.dat�ļ�ȫ·����ַ
		BOOL ret1=filedat.Open(newpath, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);//�����µ�.dat�ļ�д��
		if (!ret1)
		{
			MessageBox(TEXT("�����ļ�ʧ��"));
			return;
		}
		filedat.SeekToEnd();
		CString string1 = Tga[0] + _T (",") + Tga[1] + _T("\n");
		filedat.WriteString(string1);
		for (int i = 0; i<Acc.GetSize(); i++)
		{
			filedat.WriteString(Acc[i]+ _T("\n"));
		}
		MessageBox(TEXT("�ɹ����Ϊ.dat�ļ�"));
	}
	else
	{
		MessageBox(TEXT("�������б�ѡ�������Ϊ.dat���ļ�"));
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCPracticeDlg::OnBnClickedButtonGetcontent()
{
	int nIndex = m_list.GetSelectionMark();//��ȡlist�ؼ��и���ѡ�е��ļ�����
	if (nIndex != -1)
	{

		CString filename = m_list.GetItemText(nIndex, 0);
		CString direction = filename.Mid(filename.ReverseFind('(')+1, 1);//��ȡ����
		CString filetype = m_list.GetItemText(nIndex, 1);
		CString filepath = m_list.GetItemText(nIndex, 2);
		CString fullpath = filepath + _T("\\") + filename + filetype;//��ȡlist�ؼ��и���ѡ�е��ļ�ȫ·����ַ
		CStdioFile file;
		BOOL ret = file.Open(fullpath, CFile::modeRead | CFile::shareDenyNone);
		if (!ret)
		{
			MessageBox(TEXT("���ļ�ʧ��"));
			return;
		}
		file.SeekToBegin();// ���ļ�ָ��ָ���ļ���ʼ��
		CString cstrLine;
		CArray <CString, CString>Tga;//���������������ں�ʱ���� 
		CArray <CString, CString>Word;//��������
		Tga.SetSize(10);
		Word.SetSize(10);
		//��ȡǰ���е�����
		for (int i = 0; i < 3; i++)
		{
			file.ReadString(cstrLine);

			CString left = cstrLine.Left(cstrLine.Find('\t'));
			CString right = cstrLine.Mid((cstrLine.Find('\t') + 1));
			Word.SetAt(i, left);
			Tga.SetAt(i, right);
		}
		float Tg = _ttof(Tga[0]);//��ȡ��������
		float Ta = _ttof(Tga[1]);//��ȡʱ����

		//��ȡǰ���к�ļ��ٶ�����
		CArray <FLOAT, FLOAT>Acc;
		Acc.SetSize(50);
		for (int i = 0; file.ReadString(cstrLine) != 0; i++)
		{
			Acc.SetAt(i, _ttof(cstrLine));
		}
		float maxacc = Acc[0];
		for (int i = 1; i < Acc.GetSize(); i++) 
		{
			if (Acc[i] > maxacc) 
			{ maxacc = Acc[i]; }
		}
		m_direction = direction;//��ֵ�ؼ�����
		m_Tg = Tg;
		m_Ta = Ta;
		m_maxacc = maxacc;
		UpdateData(FALSE);//���µ���Ӧ�Ŀؼ�
	}
	else
	{
		MessageBox(TEXT("�������Ҳ��б�ѡ���ļ�"));
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
