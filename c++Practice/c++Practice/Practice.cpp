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
			// �����ļ���ȫ·��
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		
		_findclose(hFile);
	}

		FilenNumbers = files.size();//�����ļ�����
		for(int i = 0; i < files.size(); i++)
		{
			//��ȡ�ļ���
		    FullPathName[i]=accumulate(files[i].begin(), files[i].end(), FullPathName[i]);
			int a = FullPathName[i].find_last_of("\\");
			int b = FullPathName[i].find_first_of(",");

			std::string filename = FullPathName[i].substr(a + 1, b - a - 1);
			std::cout << filename << std::endl;

			//��ȡ�ļ����е�Tg
			int c = FullPathName[i].find_first_of("Tg");
			std::string Tg = FullPathName[i].substr(c + 3, 4);
			std::cout << "Tg=" << Tg << std::endl;

			//��ȡ�ļ����еķ���
			int d = FullPathName[i].find_last_of("(");
			int e = FullPathName[i].find_last_of(")");
			std::string direction = FullPathName[i].substr(d + 1, e - d - 4);
			std::cout << "����=" << direction << std::endl;

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
		while (getline(ifs, Line))//��ȡÿһ�е�����
		{

			stringstream temp(Line);
			float acc;
			temp >> acc;
			Accs.push_back(acc);//��ÿһ�е����ݼ��뵽float������

		}
		int a = FullPathName[i].find_last_of("\\");
		int b = FullPathName[i].find_first_of(",");
		std::string filename = FullPathName[i].substr(a + 1, b - a - 1);
		auto maxAcc = max_element(Accs.begin(), Accs.end());//���������е����ֵ
		std::cout<< filename << "�����ٶ�Ϊ" << *maxAcc << std::endl;
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

		for (int i = 0; i < 3; i++)//��ȡǰ�������������ں�ʱ�����������ֺ����ݷֱ𱣴�����������
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
		while (getline(ifs, Line))//��ȡ���ٶ�ÿһ�е����ݱ�����������
		{

			stringstream temp(Line);
			float acc;
			temp >> acc;
			Accs.push_back(acc);//��ÿһ�е����ݼ��뵽float������
			linenumber++;
			
		}
		float Tg = Tga[0];//��������
		float Ta = Tga[1];//ʱ����
		int a = FullPathName[i].find_last_of("\\");
		int b = FullPathName[i].find_first_of(",");
		std::string Filename = FullPathName[i].substr(a + 1, b - a - 1);
		ofstream ofs(Filename + ".dat"); //�������ļ�����.dat�ļ�
		ofs << linenumber << "," << Ta << endl;//д��������ʱ����
		for (int i = 0; i < Accs.size(); i++)//д����ٶȵ�ֵ
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
	_getcwd(Pathbuffer, sizeof(Pathbuffer));//��ȡ��ǰ����Ŀ¼
	std::string* PathName=new string[128] ;//�����ļ�������
	file.GetName(Pathbuffer,".txt", PathName, FileNumbers);
	file.MaxAcc(PathName, FileNumbers);
	file.SaveData(PathName, FileNumbers);

	delete[]PathName;
		
	std::cin.get();
}