#include "Parctice.h"
#include <direct.h> 
#include <numeric>
#include <sstream>
#include <stdio.h> 
#include <algorithm>




void GetName(string sPath, string sFiletype, string sFullPathName[],int& iFileNumbers)
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
			//读取文件名·
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



void GetMaxAcc(string sFullPathName)
{

		ifstream ifs;
		ifs.open(sFullPathName);
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
		int a = sFullPathName.find_last_of("\\");
		int b = sFullPathName.find_first_of(",");
		std::string sFileName = sFullPathName.substr(a + 1, b - a - 1);
		auto MaxAcc = max_element(vAccs.begin(), vAccs.end());//遍历容器中的最大值
		std::cout<< sFileName << "最大加速度为" << *MaxAcc << std::endl;
}

	



void SaveData(string sFullPathName)
{	
	
		ifstream ifs;
		ifs.open(sFullPathName);
		if (!ifs.is_open())
		{
			cerr << "cannot open the file" << endl;
		}
		string Line;
		vector<float> vTga;
		vector<float> vAccs;
		vector<string> vWords;

		
		while (getline(ifs, Line))//读取前三行中特征周期和时间间隔，将文字和数据分别保存在两个容器
		{
			
			stringstream temp(Line);
			if (Line[0] >= '0' && Line[0] <= '9')
			{
				float fAcc;
				temp >> fAcc;
				vAccs.push_back(fAcc);
			}
			else
			{
				string sWord;
				float fTga;
				temp >> sWord >> fTga;
				vTga.push_back(fTga);
				vWords.push_back(sWord);
			}
		}
		
		float fTg = vTga[0];//特征周期
		float fTa = vTga[1];//时间间隔
		int a = sFullPathName.find_last_of("\\");
		int b = sFullPathName.find_first_of(",");
		std::string sFileName = sFullPathName.substr(a + 1, b - a - 1);
		ofstream ofs(sFileName + ".dat"); //创建本文件名的.dat文件
		ofs << fTg << "," << fTa << endl;//写入特征周期和时间间隔
		for (int i = 0; i < vAccs.size(); i++)//写入加速度的值
		{
			ofs << vAccs[i] << endl;
		}
	
}


int main()
{
	char cPathBuffer[128] = { 0 };
	int iFileNumbers=0;
	_getcwd(cPathBuffer, sizeof(cPathBuffer));//获取当前工程目录
	string sPathName[128];//创建文件名数组
	GetName(cPathBuffer,".txt", sPathName, iFileNumbers);
	for (int i = 0; i < iFileNumbers; i++)
	{
		GetMaxAcc(sPathName[i]);
		SaveData(sPathName[i]);
	}
	std::cin.get();
}