#pragma once

#include <io.h>
#include <fstream> //输入头文件
#include <iostream>//输出头文件
#include <string>
#include <vector>

using namespace std;

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
	
	//读取文件名
	void GetName(string path, string filetype, string* FullPathName,int& filenumbers);

	//读取文件内容
	//void ReadFile();

	//读取最大加速度值
	void MaxAcc(string FullPathName[], int size);

	//保存文件
	void SaveData(string FullPathName[], int size);

};