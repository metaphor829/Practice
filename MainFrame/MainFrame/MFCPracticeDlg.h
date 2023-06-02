
// MFCPracticeDlg.h : 头文件


#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "MFCPractice.h"
#include "MFCPracticeDlg.h"
#include "afxdialogex.h"
#include <tchar.h>
#include <io.h>
#include <fstream> //输入头文件
#include <iostream>//输出头文件
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

// CMFCPracticeDlg 对话框
class CMFCPracticeDlg : public CDialogEx
{
// 构造
public:
	CMFCPracticeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPRACTICE_DIALOG };
#endif

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
