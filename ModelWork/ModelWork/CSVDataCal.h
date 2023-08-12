#pragma once
#include "Tools.h"
class CSVDataCal
{
private:
	vector<vector<string>> m_vctFile;
	map<string, map<string, vector<int>>> m_mapKeyCont;
public:
	double GetAt(int pos, int cl);
	int UpLowStop(int sp);
	void AddUpLowStop();
	void CheckYearData();
	void Main();
};

