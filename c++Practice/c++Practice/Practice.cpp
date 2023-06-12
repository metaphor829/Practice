#include "Parctice.h"
#include <direct.h> 
#include <numeric>
#include <sstream>
#include <stdio.h> 
#include <algorithm>


CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

void CInfoFile::GetName(string sPath, string sFiletype, string sFullPathName[],int& iFileNumbers)
{
	vector<string> vFiles;
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(sPath).append("\\*" + sFiletype).c_str(), &fileinfo)) != -1) {
		do {
			// 保存文件的全路径
			vFiles.push_back(p.assign(sPath).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		
		_findclose(hFile);
	}

		iFileNumbers = vFiles.size();//传回文件个数
		for(int i = 0; i < vFiles.size(); i++)
		{
			//读取文件名
			sFullPathName[i]=accumulate(vFiles[i].begin(), vFiles[i].end(), sFullPathName[i]);
			int a = sFullPathName[i].find_last_of("\\");
			int b = sFullPathName[i].find_first_of(",");

			std::string sFileName = sFullPathName[i].substr(a + 1, b - a - 1);
			std::cout << sFileName << std::endl;

			//读取文件名中的Tg
			int c = sFullPathName[i].find_first_of("Tg");
			std::string sTg = sFullPathName[i].substr(c + 3, 4);
			std::cout << "Tg=" << sTg << std::endl;

			//读取文件名中的方向
			int d = sFullPathName[i].find_last_of("(");
			int e = sFullPathName[i].find_last_of(")");
			std::string sDirection = sFullPathName[i].substr(d + 1, e - d - 4);
			std::cout << "方向=" << sDirection << std::endl;

		}
}



void CInfoFile::MaxAcc(string sFullPathName[],int iFileNumbers)
{

	for (int i = 0; i < iFileNumbers; i++)
	{
		ifstream ifs;
		ifs.open(sFullPathName[i]);
		if (!ifs.is_open())
		{
			cerr << "cannot open the file" << endl;
		}
		string Line;
		vector<float> vAccs;
		while (getline(ifs, Line))//读取每一行的数据
		{

			stringstream temp(Line);
			float fAcc;
			temp >> fAcc;
			vAccs.push_back(fAcc);//将每一行的数据加入到float容器中

		}
		int a = sFullPathName[i].find_last_of("\\");
		int b = sFullPathName[i].find_first_of(",");
		std::string sFileName = sFullPathName[i].substr(a + 1, b - a - 1);
		auto MaxAcc = max_element(vAccs.begin(), vAccs.end());//遍历容器中的最大值
		std::cout<< sFileName << "最大加速度为" << *MaxAcc << std::endl;
	}

	
}


void CInfoFile::SaveData(string sFullPathName[],int iFileNumbers)
{	
	for (int i = 0; i < iFileNumbers; i++)
	{
		ifstream ifs;
		ifs.open(sFullPathName[i]);
		if (!ifs.is_open())
		{
			cerr << "cannot open the file" << endl;
		}
		string Line;
		vector<float> vTga;
		vector<float> vAccs;
		vector<string> vWords;

		for (int i = 0; i < 3; i++)//读取前三行中特征周期和时间间隔，将文字和数据分别保存在两个容器
		{
			getline(ifs, Line);
			stringstream temp(Line);
			float fTga;
			string sWord;
			temp >> sWord >> fTga;
			vTga.push_back(fTga);
			vWords.push_back(sWord);
		}
		int iNumber = 1;
		while (getline(ifs, Line))//读取加速度每一行的数据保存在容器中
		{

			stringstream temp(Line);
			float fAcc;
			temp >> fAcc;
			vAccs.push_back(fAcc);//将每一行的数据加入到float容器中
			iNumber++;
			
		}
		float fTg = vTga[0];//特征周期
		float fTa = vTga[1];//时间间隔
		int a = sFullPathName[i].find_last_of("\\");
		int b = sFullPathName[i].find_first_of(",");
		std::string sFileName = sFullPathName[i].substr(a + 1, b - a - 1);
		ofstream ofs(sFileName + ".dat"); //创建本文件名的.dat文件
		ofs << iNumber << "," << fTa << endl;//写入行数和时间间隔
		for (int i = 0; i < vAccs.size(); i++)//写入加速度的值
		{
			ofs << vAccs[i] << endl;
		}
	}
}


int main()
{
	CInfoFile file;
	char cPathBuffer[128] = { 0 };
	int iFileNumbers=0;
	_getcwd(cPathBuffer, sizeof(cPathBuffer));//获取当前工程目录
	std::string* sPathName=new string[128] ;//创建文件名数组
	file.GetName(cPathBuffer,".txt", sPathName, iFileNumbers);
	file.MaxAcc(sPathName, iFileNumbers);
	file.SaveData(sPathName, iFileNumbers);

	delete[]sPathName;
		
	std::cin.get();
}