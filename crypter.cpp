#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;
tuple<string, string> double_ctrl(string);
string hex_crypt(string);

int main() {
	system("echo off");
	system("title xSnickerX ENCRYPTOR");
	system("color 0c");

	string stin, stin_copy;

	cout << "Enter string to be encrypted [100]: ";
	getline(cin, stin);

	stin_copy = stin;

	char day[10];
	char hour[10];
	
	system("cls");
	cout << "ENCRYPTING ... " << endl;

	time_t currentTime;
	time(&currentTime);
	tm* localTime = localtime(&currentTime);
	strftime(day, 10, "%d", localTime);
	strftime(hour, 10, "%I", localTime);

	int hour0 = int(hour[0]);
	int hour1 = int(hour[1]);
	int day0 = int(day[0]);
	int day1 = int(day[1]);
	int ku = day1 - (hour0 / 2) + stin.length();
	int kd = day0 - (hour1 / 2) + stin.length();

	tuple<string, string> sas = double_ctrl(stin);
	stin = get<0>(sas);
	string addon = get<1>(sas);

	char crt[150] = "";
	int x = 0;

	string _hour0c, _hour1c, _day0c, _day1c;
	_hour0c = char(hour0);
	_hour1c = char(hour1);
	_day0c = char(day0);
	_day1c = char(day1);

	for (int i = 0; i < stin.length() / 2; i++) {
		int cnum = int(stin[i]) - ku;
		char out_st = char(cnum);
		crt[x] = char(out_st);
		x = x + 1;
	}
	for (int i = stin.length() / 2; i < stin.length(); i++) {
		int cnum = int(stin[i]) - kd;
		char out_st = char(cnum);
		crt[x] = char(out_st);
		x = x + 1;
	}

	string sumString = _hour0c + _day0c + crt + _day1c + _hour1c + addon;

	stringstream ss;
	string in_stg = sumString;
	string hex_stg;

	ss.str("");
	for (unsigned int i = 0; i < in_stg.length(); i++) {
		ss << hex << (int)in_stg[i];
	}
	hex_stg = ss.str();

	cout << "Entered string: " << stin_copy << endl;
	cout << "Encrypted string CHR: " << sumString << endl;
	cout << "Encrypted string HEX: " << hex_stg << endl;

	system("pause");

	return 0;
}

tuple<string, string> double_ctrl(string str) {

	string strCopy1 = str;
	string strCopy2 = str;
	string addon = "";

	for (char _c : strCopy2) {
		if (_c != '\0') {
			bool first = true;
			int count = 0;
			size_t nPos = strCopy2.find(_c, 0);
			while (nPos != string::npos) {
				count++;

				if (!first) {
					addon += to_string(nPos) + strCopy2[nPos];
					strCopy1[nPos] = _c + count - 1;
					strCopy2[nPos] = '\0';
				}
				else {
					first = false;
				}

				nPos = strCopy2.find(_c, nPos + 1);
			}
		}
	}

	return make_tuple(strCopy1, addon);
}