#pragma once

#include <io.h>
#include <fstream> //����ͷ�ļ�
#include <iostream>//���ͷ�ļ�
#include <string>
#include <vector>

using namespace std;


//��ȡ�ļ���
void GetName(string path, string filetype, string* FullPathName,int& filenumbers);


//��ȡ�����ٶ�ֵ
void MaxAcc(string FullPathName);

//�����ļ�
void SaveData(string FullPathName);
