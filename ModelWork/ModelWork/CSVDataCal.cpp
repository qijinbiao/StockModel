#include "CSVDataCal.h"
enum enCols
{
	clName = 1,
	clCode,
	clDate,
	clOpen,
	clClose,
	clHigh,
	clLow,
	clVol,
	clUpLow = 11
};
double CSVDataCal::GetAt(int pos, int cl)
{
	return StrToDouble(m_vctFile[pos][cl]);
}
int CSVDataCal::UpLowStop(int sp)
{
	int iUpLow = 0;
	double dbUp = GetAt(sp, clUpLow);
	if (abs(dbUp - 5) < 0.1 || abs(dbUp - 10) < 0.1 || abs(dbUp - 20) < 0.1)
	{
		double dHigh = GetAt(sp, clHigh);
		if (dHigh == GetAt(sp, clOpen))
		{
			iUpLow |= iOpenUpStop;
		}
		if (dHigh == GetAt(sp, clClose))
		{
			iUpLow |= iCloseUpStop;
		}
		if (iUpLow != 0 && iUpLow != (iOpenUpStop | iCloseUpStop))
		{
			for (int i = -30; i < 30; ++i)
			{
				if (sp + i < m_vctFile.size() && sp + i > 10)
				{
					if (GetAt(sp + i, clUpLow) > dbUp + 0.1)
					{
						iUpLow = 0;
					}
				}
			}
		}
	}
	else if (abs(dbUp + 5) < 0.1 || abs(dbUp + 10) < 0.1 || abs(dbUp + 20) < 0.1)
	{
		double dLow = GetAt(sp, clLow);
		if (dLow == GetAt(sp, clOpen))
		{
			iUpLow |= iOpenLowStop;
		}
		if (dLow == GetAt(sp, clClose))
		{
			iUpLow |= iCloseLowStop;
		}
		if (iUpLow != 0 && iUpLow != (iOpenLowStop | iCloseLowStop))
		{
			for (int i = -30; i < 30; ++i)
			{
				if (sp + i < m_vctFile.size() && sp + i > 10)
				{
					if (GetAt(sp + i, clUpLow) + 0.1 < dbUp)
					{
						iUpLow = 0;
					}
				}
			}
		}
	}
	return iUpLow;
}

void CSVDataCal::AddUpLowStop()
{
	vector<string> vctPath;
	vector<string> vctOutFile;
	FindFilePath("../../Data0/*.csv", vctPath);
	for (unsigned int ki = 0; ki < vctPath.size(); ++ki)
	{
		string &strPath = vctPath[ki];
		cout << ki << "/" << vctPath.size() << strPath << endl;
		ReadFile(strPath, m_vctFile);
		for (unsigned int k = 1; k < m_vctFile.size(); ++k)
		{
			string strSql = "UPDATE daytable SET CL11=" + m_vctFile[k][14]
				+ " WHERE DATA='" + m_vctFile[k][3]
				+ "' AND CodeID='" + m_vctFile[k][2] + "';";
			if (m_vctFile[k].size() == 14)
			{
				m_vctFile[k].push_back(IntToStr(UpLowStop(k)));
			}
			else
			{
				vctOutFile.push_back(strSql);
			}
		}
		//WriteFile(strPath, m_vctFile);
	}
	WriteFile("../Data/upSql.txt", vctOutFile);
}
void CSVDataCal::CheckYearData()
{
	char buff[256];
	int iNum = 0;
	map<string, pair<int,string>> mapKeyData;
	for (int i = 7;i < 22; ++i)
	{
		vector<string> vctFile;
		sprintf_s(buff, "../Data/key20%02d.txt", i + 1);
		ReadFile(buff, vctFile);
		++iNum;
		for (unsigned int ki = 0; ki < vctFile.size(); ++ki)
		{
			vector<string> vctInfo;
			Split(vctFile[ki], vctInfo, '\t');
			if (vctInfo.size() == 9)
			{
				string strKey = vctInfo[0] + '\t' + vctInfo[1] + '\t' + vctInfo[2]
					+ '\t' + vctInfo[3] + '\t' + vctInfo[4];
				int iUp = StrToInt(vctInfo[5]);
				int iLow = StrToInt(vctInfo[6]);
				double dbPer = iUp * 1.0 / (iUp + iLow);
				if (mapKeyData.find(strKey)==mapKeyData.end())
				{
					mapKeyData[strKey].first = 0;
				}
				while (mapKeyData[strKey].first < iNum)
				{
					mapKeyData[strKey].second += '\t'; 
					++mapKeyData[strKey].first;
				}
				mapKeyData[strKey].second += DoubleToStr(dbPer);
			}
		}
	}
	vector<string> vctOutFile;
	for (auto &it : mapKeyData)
	{
		vctOutFile.push_back(it.first + it.second.second);
	}
	WriteFile("../Data/KeyOut.txt", vctOutFile);
}
void CSVDataCal::Main()
{
	//CheckYearData();
	//AddUpLowStop();
}
