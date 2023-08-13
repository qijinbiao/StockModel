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
enum enCols
{
	clName = 1,		//股票名称
	clCode,			//股票代码
	clDate,			//日期
	clOpen,			//开盘
	clClose,		//收盘
	clHigh,			//最高
	clLow,			//最低
	clVolume,		//成交量
	clTraVol,		//成交额
	clAmplitude,	//振幅
	clFluctuation,	//涨跌幅
	clPriceFluc,	//涨跌额
	clTurnoverRate	//换手率
};
enum enUpLowStop
{
	iOpenUpStop = 1,
	iOpenLowStop = 2,
	iCloseUpStop = 4,
	iCloseLowStop = 8
};
string IntToStr(int ix);
int StrToInt(string str, int iradix = 10);
int DoubleToInt(double db);
double StrToDouble(string str);
string DoubleToStr(double dbValue);
void StrReplace(string &str, string src, string des);
void Split(const string &strInfo, vector<string> &vctInfo, char ch);
bool ReadFile(const string strFile, string &strInfo);
bool ReadFile(const string strFile, vector<string> &vctFile);
bool ReadFile(const string strFile, vector<vector<string>> &vctFile);
bool WriteFile(const string &strFile, vector<string> &vctFile);
bool WriteFile(const string &strFile, vector<vector<string>> &vctFile);
bool FindFilePath(string strPath, vector<string> &vctPath, bool bRecursion = false);
