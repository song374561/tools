/*
* Name:			8comic cracker
* Ver:			1.00
* Authour:		wetprogrammer
* Namespace:	http://blog.wetprogrammer.net
* Description:	Find the picture real url.
*/
#include <iostream>
#include <cctype>
#include <cstdio>
#include <string>
#include <sstream>
#include <string.h>
#define f 50
using namespace std;

string subkeyCreater(string comicKey, int ch);
string urlCreater(string subKey, int itemid, int page);
//si();
string strSplit(string str, int start, int count);
//ss(), d = null;
string strSplit(string str, int start, int count, int test);
//ss(), d != null;
string intToStr(int n);
string addZero(int n);
//nn();
int getHash(int n);
//mm();
int pageCounter(string subKey);

int main(int argc, char *argv[])
{
	string comicKey;
	int itemid, ch;

	string subKey,picUrl;
	int chs, totalPage;
	int page;

	cout << "漫畫金鑰：" << endl;
	cin >> comicKey;
	cout << "漫畫id：" << endl;
	cin >> itemid;
	cout << "漫畫話數：" << endl;
	cin >> ch;


	chs = comicKey.length() / f;
	subKey = subkeyCreater(comicKey, ch);
	
	totalPage = pageCounter(subKey);

	for (page = 1; page <= totalPage; page++)
	{
		cout << urlCreater(subKey, itemid, page) << endl;
	}
}
string strSplit(string str, int start, int count)
{
	string temp1;
	string temp2;

	temp1 = str.substr(start, count);

	for (int i = 0; i < temp1.length(); i++)
	{
		if (isdigit(temp1[i]))
			temp2.push_back(temp1[i]);
	}
	return temp2;
}
string strSplit(string str, int start, int count, int test)
{
	return str.substr(start, count);
}
string intToStr(int n)
{
	string s;
	stringstream ss(s);
	ss << n;
	return ss.str();
}

string subkeyCreater(string comicKey, int ch)
{
	string subKey="";
	int keyLength = comicKey.length();
	for (int i = 0; i < keyLength / f; i++)
	{
		if (strSplit(comicKey, i*f, 4).compare(intToStr(ch)) == 0)
		{
			subKey = strSplit(comicKey, i*f, f, f);
			break;
		}
	}
	if (subKey == "")
	{
		subKey = strSplit(comicKey, keyLength - f, f);
	}
	return subKey;
}
string addZero(int n)
{
	if (n < 10)
		return "00" + intToStr(n);
	else if (n < 100)
		return "0" + intToStr(n);
	else
		return intToStr(n);
}
int getHash(int n)
{
	return (((n - 1) / 10) % 10)+(((n-1)%10)*3);
}
int pageCounter(string subKey)
{
	return stoi(strSplit(subKey, 7, 3));
}
string urlCreater(string subKey, int itemid, int page)
{
	string serverNum = strSplit(subKey, 4, 2);
	string serialNum = strSplit(subKey, 6, 1);
	string sitemid = intToStr(itemid);
	string serialNum2 = strSplit(subKey, 0, 4);
	string pageNum = addZero(page);
	string hash = strSplit(subKey, getHash(page) + 10, 3, f);

	return "http://img" + serverNum + ".8comic.com/" + serialNum + "/" + sitemid + "/" + serialNum2 + "/" + pageNum + "_" + hash + ".jpg";
}