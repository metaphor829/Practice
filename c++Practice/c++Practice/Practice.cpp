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
			// �����ļ���ȫ·��
			vFiles.push_back(p.assign(sPath).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		
		_findclose(hFile);
	}

		iFileNumbers = vFiles.size();//�����ļ�����
		for(int i = 0; i < vFiles.size(); i++)
		{
			//��ȡ�ļ�����
			sFullPathName[i]=accumulate(vFiles[i].begin(), vFiles[i].end(), sFullPathName[i]);
			int a = sFullPathName[i].find_last_of("\\");
			int b = sFullPathName[i].find_first_of(",");

			std::string sFileName = sFullPathName[i].substr(a + 1, b - a - 1);
			std::cout << sFileName << std::endl;

			//��ȡ�ļ����е�Tg
			int c = sFullPathName[i].find_first_of("Tg");
			std::string sTg = sFullPathName[i].substr(c + 3, 4);
			std::cout << "Tg=" << sTg << std::endl;

			//��ȡ�ļ����еķ���
			int d = sFullPathName[i].find_last_of("(");
			int e = sFullPathName[i].find_last_of(")");
			std::string sDirection = sFullPathName[i].substr(d + 1, e - d - 4);
			std::cout << "����=" << sDirection << std::endl;

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
		while (getline(ifs, Line))//��ȡÿһ�е�����
		{

			stringstream temp(Line);
			float fAcc;
			temp >> fAcc;
			vAccs.push_back(fAcc);//��ÿһ�е����ݼ��뵽float������

		}
		int a = sFullPathName.find_last_of("\\");
		int b = sFullPathName.find_first_of(",");
		std::string sFileName = sFullPathName.substr(a + 1, b - a - 1);
		auto MaxAcc = max_element(vAccs.begin(), vAccs.end());//���������е����ֵ
		std::cout<< sFileName << "�����ٶ�Ϊ" << *MaxAcc << std::endl;
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

		
		while (getline(ifs, Line))//��ȡǰ�������������ں�ʱ�����������ֺ����ݷֱ𱣴�����������
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
		
		float fTg = vTga[0];//��������
		float fTa = vTga[1];//ʱ����
		int a = sFullPathName.find_last_of("\\");
		int b = sFullPathName.find_first_of(",");
		std::string sFileName = sFullPathName.substr(a + 1, b - a - 1);
		ofstream ofs(sFileName + ".dat"); //�������ļ�����.dat�ļ�
		ofs << fTg << "," << fTa << endl;//д���������ں�ʱ����
		for (int i = 0; i < vAccs.size(); i++)//д����ٶȵ�ֵ
		{
			ofs << vAccs[i] << endl;
		}
	
}


int main()
{
	char cPathBuffer[128] = { 0 };
	int iFileNumbers=0;
	_getcwd(cPathBuffer, sizeof(cPathBuffer));//��ȡ��ǰ����Ŀ¼
	string sPathName[128];//�����ļ�������
	GetName(cPathBuffer,".txt", sPathName, iFileNumbers);
	for (int i = 0; i < iFileNumbers; i++)
	{
		GetMaxAcc(sPathName[i]);
		SaveData(sPathName[i]);
	}
	std::cin.get();
}