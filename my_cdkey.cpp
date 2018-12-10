#include "typedef.h"
#include <time.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef map<string, string>	MAP_STR;
typedef map<int, int>		MAP_INT;

int RandGet(int nMax, bool bReset/* = false*/);
int RandGet(int nMax, bool bReset = false)
{
	static __int64 RandSeed = ::time(NULL);
	if (bReset)
		RandSeed = ::time(NULL);

	__int64 x ;
	double i ;
	unsigned long final ;
	x = 0xffffffff;
	x += 1 ;

	RandSeed *= ((__int64)134775813);
	RandSeed += 1 ;
	RandSeed = RandSeed % x ;
	i = ((double)RandSeed) / (double)x ;
	final = (long) (nMax * i) ;

	return (int)final;
}

int main()
{
	cout<<"cdkey功能有两种。第一种：一个cdkey只可以被玩家使用一次，使用之后这个cdkey就无效。第二种：一个cdkey可以重复被玩家使用，但是每个玩家只能参与一次该活动。"<<endl;
	int nCDKeyMode = 0;
	do 
	{
		cout<<"请输入生成cdkey第几种模式(第一种:1,第二种:2)："<<endl;
		cin>>nCDKeyMode;
		if (1 != nCDKeyMode || 2 != nCDKeyMode)
		{
			break;
		}
	} while (true);

	int nRealStrLen = 0;
	do 
	{
		cout<<"请输入要生成cdkey长度(大于等于"<<STR_MIN_LEN<<"位小于"<<STR_MAX_LEN<<"位)："<<endl;
		cin>>nRealStrLen;
		if (nRealStrLen >= STR_MIN_LEN && nRealStrLen < STR_MAX_LEN)
		{
			break;
		}
		
	} while (true);

	int nStrLen = nRealStrLen - PREFIX_LEN;
	string strRepeat;
	
	if (2 == nCDKeyMode)
	{
		do 
		{
			cout<<"请输入第2种cdkey 3个前缀小写英文字母(长度3位,字符a-z)："<<endl;
			cin>>strRepeat;
			if (PREFIX_LEN != strRepeat.size())
			{
				cout<<"输入长度无效,必须是3位"<<endl;
				continue;
			}

			if (::islower(strRepeat.at(0)) && ::islower(strRepeat.at(1)) && ::islower(strRepeat.at(2)))
			{
				break;
			}
			else
			{
				cout<<"输入字符无效,3个前缀必须是小写英文字母"<<endl;
			}

		} while (true);
	}
	
	// 生成唯一key前缀
	string strOnly;
	if (1 == nCDKeyMode)
	{
		strOnly = LETTER_ONLYPREFIX[RandGet(sizeof(LETTER_ONLYPREFIX) / (PREFIX_LEN+1))];
		if (PREFIX_LEN != strOnly.size())
		{
			cout<<"系统生成第2种cdkey有误,请重新操作"<<endl;
			return 0;
		}
	}

	// cdkey 前缀
	string strPrefix((1 == nCDKeyMode) ? strOnly : strRepeat);

	time_t tCurrTime = ::time(NULL);
	struct tm* pTime;
	pTime = ::localtime(&tCurrTime);
	time_t tTime = (pTime->tm_year % 100) * 1000000 + (pTime->tm_mon + 1) * 10000 + pTime->tm_mday * 100 + pTime->tm_hour;

	char strDigit[DIGIT_LEN + 1] = "";
	::sprintf(strDigit, "%d", tTime);
	
	int nNum = 0;
	do 
	{
		cout<<"请输入要生成cdkey数目(大于0)："<<endl;
		cin>>nNum;

		if (nNum > 0)
		{
			break;
		}

	} while (true);

	cout<<"cdkey生成中......"<<endl;

	int nLetterLen = ::strlen(LETTER);
	MAP_STR	mapStrLetter;
	mapStrLetter.clear();
	
	int nBreak = 0;
	while (true)
	{
		if (++nBreak > 10000000)
		{
			break;
		}

		if (mapStrLetter.size() >= nNum)
		{
			break;
		}

		string strTemp;
		while (true)
		{
			if (strTemp.size() >= nStrLen - DIGIT_LEN)
			{
				break;
			}

			int nRand = RandGet(nLetterLen);
			if (nRand >= 0 && nRand < nLetterLen)
			{
				strTemp += LETTER[nRand];
			}
		}

		if (mapStrLetter.find(strTemp) == mapStrLetter.end())
		{
			mapStrLetter[strTemp] = strTemp;
		}
	}
	
	MAP_STR mapStrGet;
	mapStrGet.clear();
	MAP_STR::iterator iter_str = mapStrLetter.begin();
	for (; iter_str != mapStrLetter.end(); ++iter_str)
	{
		string strTemp = iter_str->first;
		if (strTemp.size() != nStrLen - DIGIT_LEN)
		{
			continue;
		}

		MAP_INT mapIntSpace;
		while (true)
		{
			if (mapIntSpace.size() >= DIGIT_LEN)
			{
				break;
			}

			int nRand = RandGet(nStrLen);
			if (nRand >= 0 && nRand < nStrLen)
			{
				mapIntSpace[nRand] = nRand;
			}
		}
		
		if (mapIntSpace.size() != DIGIT_LEN)
		{
			continue;
		}

		int nPlugDigitIdx = 0;
		int nPlugLetterIdx = 0;
		char strTempGet[128] = "";
		for (int nIndex = 0; nIndex < nStrLen; nIndex++)
		{
			if (mapIntSpace.find(nIndex) != mapIntSpace.end())
			{
				strTempGet[nIndex] = strDigit[nPlugDigitIdx];
				nPlugDigitIdx++;
			}
			else
			{
				strTempGet[nIndex] = strTemp[nPlugLetterIdx];
				nPlugLetterIdx++;
			}
		}

		string strGet(strTempGet);
		if (strGet.size() != nStrLen)
		{
			continue;
		}

		if (mapStrGet.find(strGet) == mapStrGet.end())
		{
			mapStrGet[strGet] = strGet;
		}
	}

// 	int nBegin = 0;
// 	MAP_STR::iterator iter = mapStrGet.begin();
// 	for (; iter != mapStrGet.end(); ++iter)
// 	{
// 		nBegin++;
// 		cout<<"cdkey"<<nBegin<<" : "<<iter->first.c_str()<<endl;
// 	}

	::remove(SAVE_FILE);
	::remove(SQL_SAVE_FILE);

	char strCreateTime[1024] = "";
	//::sprintf(strCreateTime, "*****CDKEY创建时间：%d年%2d月%2d日 %2d:%2d:%2d*****", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);

	FILE* fp1 = ::fopen(SAVE_FILE, "wt");
	if (NULL != fp1)
	{
		//::fputs(strCreateTime, fp1);
		//::fputs("\n", fp1);
		//::fputs("===================CDKEY=================", fp1);
		MAP_STR::iterator iter = mapStrGet.begin();
		for (; iter != mapStrGet.end(); ++iter)
		{
			::fputs("\n", fp1);
			::fputs(strPrefix.c_str(), fp1);
			::fputs(iter->first.c_str(), fp1);
		}
		::fputs("\n", fp1);
		::fclose(fp1);
	}
	fp1 = NULL;

	cout<<"cdkey生成完毕!!!实际生成:"<<mapStrGet.size()<<"条"<<endl;
	cout<<"是否生成对应的SQL语句?(Y/N 或 y/n)"<<endl;

	char ch;
	cin>>ch;
	if ('Y' != ch && 'y' != ch)
	{
		return 0;
	}

	string strSQL;
	FILE* fp3 = ::fopen(SQL_READ_FILE, "rt");
	if (NULL == fp3)
	{
		fp3 = ::fopen(SQL_READ_FILE, "wt");
		if (NULL != fp3)
		{
			::fputs("#请在下面一行输入对应生成SQL语句\n", fp3);
			::fputs("SQL=INSERT INTO cdkey_exchange(activity_id,cdkey) VALUES ('AAXXAA', 'BBXXBB');\n", fp3);
			::fputs("#注:“AAXXAA”表示活动ID,输出sql会提示是否输入,程序代码将“BBXXBB”自动替换为生成好的cdkey,\n", fp3);
			::fclose(fp3);
		}

		return 0;
	}
	else
	{
		while(!feof(fp3))
		{
			char buf[1024] = "";
			fgets(buf,1024,fp3);

			strSQL = buf;
			if (string::npos != strSQL.find("#"))
			{
				continue;
			}

			if (string::npos != strSQL.find("SQL=") && string::npos != strSQL.find("BBXXBB") && string::npos != strSQL.find("AAXXAA"))
			{
				break;
			}
		}

		::fclose(fp3);
		fp3 = NULL;
	}

	if (string::npos == strSQL.find("SQL=") || string::npos == strSQL.find("BBXXBB") || string::npos == strSQL.find("AAXXAA")
		|| (string::npos == strSQL.find_first_of("VALUES") && string::npos == strSQL.find_first_of("values")))
	{
		cout<<"文件cdkey_insql.txt的SQL有误!";
		return 0;
	}

	string strActId;
	do
	{
		cout<<"是否输入cdkey活动ID?(Y/N 或 y/n)"<<endl;
		cin>>ch;
		if ('Y' != ch && 'y' != ch)
		{
			strActId = "";
			break;
		}

		cout<<"请输入cdkey活动ID(大于0且不超过10位)"<<endl;
		cin>>strActId;
		if (strActId.size() <= 0 || strActId.size() > 10)
		{
			cout<<"cdkey活动ID必须是大于0且不超过10位"<<endl;
			continue;
		}

		bool bDigit = true;
		for (int nIndex = 0; nIndex < strActId.size(); nIndex++)
		{
			if (!::isdigit(strActId.at(nIndex)))
			{
				bDigit = false;
				break;
			}
		}

		if (bDigit)
		{
			break;
		}

		cout<<"cdkey活动ID必须都是数字"<<endl;
	}
	while(true);

	string strRealSQL = strSQL.substr(strSQL.find_first_of("=") + 1, strSQL.size());
	FILE* fp2 = ::fopen(SQL_SAVE_FILE, "wt");
	if (NULL != fp2)
	{
		::fputs(strCreateTime, fp2);
		::fputs("\n", fp2);
		::fputs("===================CDKEY--SQL==================\n", fp2);
		if (1 == nCDKeyMode)
		{
			int nPosVal = string::npos;
			if (string::npos != strRealSQL.find("VALUES"))
			{
				nPosVal = strRealSQL.find("VALUES");
			}
			else if (string::npos != strRealSQL.find("values"))
			{
				nPosVal = strRealSQL.find("values");
			}

			if (string::npos == nPosVal)
			{
				cout<<"文件cdkey_insql.txt的SQL有误!";
				::fclose(fp2);
				fp2 = NULL;
				return 0;
			}

			string strSQLPre = strRealSQL.substr(0, nPosVal + 6);
			::fputs(strSQLPre.c_str(), fp2);
			::fputs("\n", fp2);
			
			string strSQLAft = strRealSQL.substr(nPosVal);
			strSQLAft = strSQLAft.substr(strSQLAft.find("("));
			strSQLAft = strSQLAft.substr(0, strSQLAft.find(")") + 1);
			if (strActId.size() > 0)
			{
				strSQLAft.replace(strSQLAft.find("AAXXAA"), 6, strActId.c_str());
			}

			int nBegin = 1;
			int nMapStrGetSize = mapStrGet.size();
			MAP_STR::iterator iter = mapStrGet.begin();
			for (; iter != mapStrGet.end(); ++iter, ++nBegin)
			{
				string strCDKey = strPrefix + iter->first.c_str();
				string strTempSQL = strSQLAft;
				unsigned int nOff = strTempSQL.find("BBXXBB");
				strTempSQL.replace(nOff, 6, strCDKey);
				if (nBegin != nMapStrGetSize)
				{
					strTempSQL += ",\n";
				}
				else
				{
					strTempSQL += ";\n";
				}

				//::fputs("\n", fp2);
				::fputs(strTempSQL.c_str(), fp2);
			}
		}
		else if (2 == nCDKeyMode)
		{
			string strTempSQL = strRealSQL;
			unsigned int nOff = strTempSQL.find("BBXXBB");
			strTempSQL.replace(nOff, 6, strPrefix);
			if (strActId.size() > 0)
			{
				strTempSQL.replace(strTempSQL.find("AAXXAA"), 6, strActId.c_str());
			}

			::fputs(strTempSQL.c_str(), fp2);
		}
 		
		//::fputs("\n", fp2);
		::fputs("===================CDKEY--SQL==================", fp2);
		::fclose(fp2);
	}
	fp2 = NULL;

	cout<<"生成SQL完成"<<endl;

	return 0;
}