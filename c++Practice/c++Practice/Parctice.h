#pragma once

#include <io.h>
#include <fstream> //输入头文件
#include <iostream>//输出头文件
#include <string>
#include <vector>

using namespace std;


//读取文件名
void GetName(string path, string filetype, string* FullPathName,int& filenumbers);


//读取最大加速度值
void MaxAcc(string FullPathName);

//保存文件
void SaveData(string FullPathName);
