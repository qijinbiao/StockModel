#include "Tools.h"

int DoubleToInt(double db)
{
	return (int)((db > 0.0) ? (db + 0.5) : (db - 0.5));
}
double StrToDouble(string str)
{
	return strtod(str.c_str(), NULL);
}
string IntToStr(int ix)
{
	char buff[20];
	sprintf_s(buff, "%d", ix);
	return buff;
}
int StrToInt(string str, int iradix)
{
	char *buff = NULL;
	return strtol(str.c_str(), &buff, iradix);
}
string DoubleToStr(double dbValue)
{
	char buff[64];
	sprintf_s(buff, "%.3f", dbValue);
	return buff;
}
void StrReplace(string &str, string src, string des)
{
	size_t sp = str.find(src);
	while (string::npos != sp)
	{
		str.replace(sp, src.length(), des);
		sp = str.find(src);
	}
}
void Split(const string &strInfo, vector<string> &vctInfo, char ch)
{
	size_t sp = 0;
	size_t ep = 0;
	vctInfo.clear();
	while (string::npos != (ep = strInfo.find(ch, sp)))
	{
		vctInfo.push_back(strInfo.substr(sp, ep - sp));
		sp = ep + 1;
	}
	if (sp < strInfo.length())
	{
		vctInfo.push_back(strInfo.substr(sp, strInfo.length() - sp));
	}
}
unsigned char *ReadFileToBuff(const string &strFile, int &iLen)
{
	FILE *fin = NULL;
	unsigned char *ucBuff = NULL;
	iLen = 0;
	int iError = fopen_s(&fin, strFile.c_str(), "rb");
	if (iError == 0)
	{
		fseek(fin, 0, SEEK_END);
		iLen = ftell(fin);
		fseek(fin, 0, SEEK_SET);
		ucBuff = new unsigned char[iLen + 1];
		fread(ucBuff, iLen, 1, fin);
		ucBuff[iLen] = 0;
		fclose(fin);
	}
	return ucBuff;
}
bool ReadFile(const string strFile, string &strInfo)
{
	int iLen = 0;
	unsigned char *ucBuff = ReadFileToBuff(strFile, iLen);
	if (ucBuff == NULL)
	{
		return false;
	}
	strInfo = (char *)ucBuff;
	delete[] ucBuff;
	return true;
}
bool ReadFile(const string strFile, vector<string> &vctFile)
{
	vctFile.clear();
	string strInfo;
	if (ReadFile(strFile, strInfo))
	{
		size_t sp = 0;
		string strEnd = "\r\n";
		size_t ep = strInfo.find(strEnd);
		if (string::npos == ep)	strEnd = "\n";
		while (string::npos != ep)
		{
			vctFile.push_back(strInfo.substr(sp, ep - sp));
			sp = ep + strEnd.length();
			ep = strInfo.find(strEnd, sp);
		}
		if (sp < strInfo.length())
		{
			vctFile.push_back(strInfo.substr(sp, strInfo.length() - sp));
		}
		return true;
	}
	return false;
}

bool ReadFile(const string strFile, vector<vector<string>> &vctFile)
{
	vctFile.clear();
	string strInfo;
	if (ReadFile(strFile, strInfo))
	{
		size_t sp = 0;
		string strEnd = "\r\n";
		size_t ep = strInfo.find(strEnd);
		if (string::npos == ep)	strEnd = "\n";
		while (string::npos != ep)
		{
			vector<string> vctInfo;
			Split(strInfo.substr(sp, ep - sp), vctInfo, ',');
			vctFile.push_back(vctInfo);
			sp = ep + strEnd.length();
			ep = strInfo.find(strEnd, sp);
		}
		if (sp < strInfo.length())
		{
			vector<string> vctInfo;
			Split(strInfo.substr(sp, strInfo.length() - sp), vctInfo, ',');
			vctFile.push_back(vctInfo);
		}
		return true;
	}
	return false;
}

bool WriteFile(const string &strFile, vector<string> &vctFile)
{
	FILE *fout = NULL;
	int iError = fopen_s(&fout, strFile.c_str(), "wb");
	if (iError == 0)
	{
		for (auto &strLine : vctFile)
		{
			fprintf(fout, "%s\r\n", strLine.c_str());
		}
		fclose(fout);
		return true;
	}
	return false;
}
bool WriteFile(const string &strFile, vector<vector<string>> &vctFile)
{
	FILE *fout = NULL;
	int iError = fopen_s(&fout, strFile.c_str(), "wb");
	if (iError == 0)
	{
		for (auto &vctInfo : vctFile)
		{
			string strLine = "";
			for (auto &strInfo : vctInfo)
			{
				strLine += strInfo + ',';
			}
			strLine[strLine.length() - 1] = '\r';
			fprintf(fout, "%s\n", strLine.c_str());
		}
		fclose(fout);
		return true;
	}
	return false;
}
void GetNextFolders(string strPath, vector<string> &vctFolder)
{
	_finddata_t flData;
	size_t sp = strPath.find('/');
	string strPathHead = strPath.substr(0, ++sp);
	string strRear = strPath.substr(sp);
	intptr_t lFileDir = _findfirst((strPathHead + '*').c_str(), &flData);
	if (lFileDir != -1)
	{
		do 
		{
			if ((flData.attrib & 16) && flData.name != string(".") && flData.name != string(".."))
			{
				vctFolder.push_back(strPathHead + flData.name);
			}
		} while (_findnext(lFileDir, &flData) == 0);
		_findclose(lFileDir);
	}
}
bool FindFilePath(string strPath, vector<string> &vctPath, bool bRecursion)
{
	StrReplace(strPath, "\\", "/");
	size_t sp = strPath.rfind('/');
	string strRear = strPath.substr(sp);
	if (bRecursion)
	{
		vector<string> vctFolder;
		GetNextFolders(strPath, vctFolder);
		for (auto &strFolder : vctFolder)
		{
			FindFilePath(strFolder + strRear, vctPath, bRecursion);
		}
	}
	string strPathHead = strPath.substr(0, ++sp);
	_finddata_t flData;
	intptr_t lFileDir = _findfirst(strPath.c_str(), &flData);
	if (lFileDir != -1)
	{
		do
		{
			if (flData.name != string(".") && flData.name != string(".."))
			{
				vctPath.push_back(strPathHead + flData.name);
			}
		} while (_findnext(lFileDir, &flData) == 0);
		_findclose(lFileDir);
	}
	return true;
}