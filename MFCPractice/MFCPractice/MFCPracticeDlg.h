
// MFCPracticeDlg.h : ͷ�ļ�


#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "MFCPractice.h"
#include "MFCPracticeDlg.h"
#include "afxdialogex.h"
#include <tchar.h>
#include <io.h>
#include <fstream> //����ͷ�ļ�
#include <iostream>//���ͷ�ļ�
#include <string>
#include <vector>
#include <direct.h> 
#include <numeric>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

// CMFCPracticeDlg �Ի���
class CMFCPracticeDlg : public CDialogEx
{
// ����
public:
	CMFCPracticeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPRACTICE_DIALOG };
#endif

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
	afx_msg void OnBnClickedButtonGetname();
	CListCtrl m_list;
private:
	CString m_direction;
	float m_Tg;
	float m_Ta;
	float m_maxacc;
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonGetcontent();
};
