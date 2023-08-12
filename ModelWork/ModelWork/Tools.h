#pragma once
#include <io.h>
#include <direct.h>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <ctime>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
enum enUpLowStop
{
	iOpenUpStop = 1,
	iOpenLowStop = 2,
	iCloseUpStop = 4,
	iCloseLowStop = 8
};
int DoubleToInt(double db);
double StrToDouble(string str);
string IntToStr(int ix);
int StrToInt(string str, int iradix = 10);
string DoubleToStr(double dbValue);
void StrReplace(string &str, string src, string des);
void Split(const string &strInfo, vector<string> &vctInfo, char ch);
bool ReadFile(const string strFile, string &strInfo);
bool ReadFile(const string strFile, vector<string> &vctFile);
bool ReadFile(const string strFile, vector<vector<string>> &vctFile);
bool WriteFile(const string &strFile, vector<string> &vctFile);
bool WriteFile(const string &strFile, vector<vector<string>> &vctFile);
bool FindFilePath(string strPath, vector<string> &vctPath, bool bRecursion = false);
