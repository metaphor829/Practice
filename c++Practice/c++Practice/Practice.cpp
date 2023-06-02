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

void CInfoFile::GetName(string path, string filetype, string FullPathName[],int& FilenNumbers)
{
	vector<string> files;
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + filetype).c_str(), &fileinfo)) != -1) {
		do {
			// 保存文件的全路径
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		
		_findclose(hFile);
	}

		FilenNumbers = files.size();//传回文件个数
		for(int i = 0; i < files.size(); i++)
		{
			//读取文件名
		    FullPathName[i]=accumulate(files[i].begin(), files[i].end(), FullPathName[i]);
			int a = FullPathName[i].find_last_of("\\");
			int b = FullPathName[i].find_first_of(",");

			std::string filename = FullPathName[i].substr(a + 1, b - a - 1);
			std::cout << filename << std::endl;

			//读取文件名中的Tg
			int c = FullPathName[i].find_first_of("Tg");
			std::string Tg = FullPathName[i].substr(c + 3, 4);
			std::cout << "Tg=" << Tg << std::endl;

			//读取文件名中的方向
			int d = FullPathName[i].find_last_of("(");
			int e = FullPathName[i].find_last_of(")");
			std::string direction = FullPathName[i].substr(d + 1, e - d - 4);
			std::cout << "方向=" << direction << std::endl;

		}
}



void CInfoFile::MaxAcc(string FullPathName[],int filenumbers)
{

	for (int i = 0; i <filenumbers; i++)
	{
		ifstream ifs;
		ifs.open(FullPathName[i]);
		if (!ifs.is_open())
		{
			cerr << "cannot open the file" << endl;
		}
		string Line;
		vector<float> Accs;
		while (getline(ifs, Line))//读取每一行的数据
		{

			stringstream temp(Line);
			float acc;
			temp >> acc;
			Accs.push_back(acc);//将每一行的数据加入到float容器中

		}
		int a = FullPathName[i].find_last_of("\\");
		int b = FullPathName[i].find_first_of(",");
		std::string filename = FullPathName[i].substr(a + 1, b - a - 1);
		auto maxAcc = max_element(Accs.begin(), Accs.end());//遍历容器中的最大值
		std::cout<< filename << "最大加速度为" << *maxAcc << std::endl;
	}

	
}


void CInfoFile::SaveData(string FullPathName[],int FileNumbers)
{	
	for (int i = 0; i < FileNumbers; i++)
	{
		ifstream ifs;
		ifs.open(FullPathName[i]);
		if (!ifs.is_open())
		{
			cerr << "cannot open the file" << endl;
		}
		string Line;
		vector<float> Tga;
		vector<float> Accs;
		vector<string> Words;

		for (int i = 0; i < 3; i++)//读取前三行中特征周期和时间间隔，将文字和数据分别保存在两个容器
		{
			getline(ifs, Line);
			stringstream temp(Line);
			float tga;
			string word;
			temp >> word >> tga;
			Tga.push_back(tga);
			Words.push_back(word);
		}
		int linenumber = 1;
		while (getline(ifs, Line))//读取加速度每一行的数据保存在容器中
		{

			stringstream temp(Line);
			float acc;
			temp >> acc;
			Accs.push_back(acc);//将每一行的数据加入到float容器中
			linenumber++;
			
		}
		float Tg = Tga[0];//特征周期
		float Ta = Tga[1];//时间间隔
		int a = FullPathName[i].find_last_of("\\");
		int b = FullPathName[i].find_first_of(",");
		std::string Filename = FullPathName[i].substr(a + 1, b - a - 1);
		ofstream ofs(Filename + ".dat"); //创建本文件名的.dat文件
		ofs << linenumber << "," << Ta << endl;//写入行数和时间间隔
		for (int i = 0; i < Accs.size(); i++)//写入加速度的值
		{
			ofs << Accs[i] << endl;
		}
	}
}


int main()
{
	CInfoFile file;
	char Pathbuffer[128] = { 0 };
	int FileNumbers=0;
	_getcwd(Pathbuffer, sizeof(Pathbuffer));//获取当前工程目录
	std::string* PathName=new string[128] ;//创建文件名数组
	file.GetName(Pathbuffer,".txt", PathName, FileNumbers);
	file.MaxAcc(PathName, FileNumbers);
	file.SaveData(PathName, FileNumbers);

	delete[]PathName;
		
	std::cin.get();
}