#pragma once

#include <io.h>
#include <fstream> //����ͷ�ļ�
#include <iostream>//���ͷ�ļ�
#include <string>
#include <vector>

using namespace std;

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
	
	//��ȡ�ļ���
	void GetName(string path, string filetype, string* FullPathName,int& filenumbers);

	//��ȡ�ļ�����
	//void ReadFile();

	//��ȡ�����ٶ�ֵ
	void MaxAcc(string FullPathName[], int size);

	//�����ļ�
	void SaveData(string FullPathName[], int size);

};