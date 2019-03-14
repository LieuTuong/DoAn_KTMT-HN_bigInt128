#include <iostream>
#include<string>
#include<bitset>
#include<array>
#include<memory>
using namespace std;
#define MAX 128

// do ko chac unsigned int luon la 4 bytes, nen dung unit32_t
typedef struct
{
	uint32_t data[4];

}QInt;

int MAXBIT(string userInputStr)
{
	if (userInputStr[0] == '-')
	{
		userInputStr.erase(0, 1);
	}
	int len = userInputStr.length();
	if (len <= 3)return 8;
	else if (len > 3 && len <= 5) return 16;
	else if (len > 5 && len <= 10) return 32;
	else if (len > 10 && len <= 19) return 64;
	else if (len > 19 && len <= 39)return 128;
	else return 0;
}


void xuat(array<int, MAX>a)
{
	for (auto& x : a)
	{
		cout << x;
	}
	cout << endl;
}
//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
}

int stringToNum(char c)     // chuyen char sang so
{
	return c - '0';
}

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}

string remove0(const string& number)
{
	string res = number;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] != '0')//Vi tri khac 0 dau tien
		{
			res.erase(0, i);
			break;
		}
	}
	return res;
}


//ten ham da bieu thi tat ca:))
string chia2(string bigInt)
{

	string tmp;
	string soChia = remove0(bigInt);

	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(bigInt.length());
	if (stringToNum(soChia[0]) < 2)
	{
		i = 1;
		j = 10;
	}
	for (; i < soChia.length(); i++)
	{
		tmp[k++] = ((soChia[i] - '0' + j) / 2 + '0');
		j = ((soChia[i] - 48 + j) % 2) * 10;
	}
	tmp.resize(k);
	return tmp;
}



// Ham lay bu 1
string bu1(string a)
{
	string tmp="";
	for (int i = 0; i < a.length(); i++)
	{
		char x= (a[i] == '1') ? '0' : '1';
		tmp.push_back(x);		
	}
	return tmp;
}



//Ham lay bu 2
string bu2(string a)
{
	string dayBu1 = bu1(a);
	int soDu = 1;
	string bu2;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		char x;
		if (dayBu1[i] == '0' && soDu == 1)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '0'&& soDu == 0)
		{
			x = '0';
			soDu = 0;
		}
		else if (dayBu1[i] == '1' && soDu == 0)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '1'&& soDu == 1)
		{
			x = '0';
			soDu = 1;
		}
		bu2.insert(0, 1, x);
	}
	return bu2;
}



//Ham chuyen tu QInt sang mang int a[MAX]
string QInt_To_Arr(const QInt& number)
{
	string a ;
	for (int i = 0; i < a.length(); i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a.push_back('1');
		}
		else
		{
			a.push_back('0');
		}
	}
	return a;
}



//Ham chuyen tu mang a sang Qint
QInt Arr_To_QInt(const string& binArr)
{
	QInt number;
	initQInt(number);
	for (int i = 0; i < binArr.length(); i++)
	{
		if (binArr[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}



//Ham dao nguoc mang (sau khi chia 2 thi he nhi phan la lay so du tu duoi len)
string reverse(string a)
{
	string rev_arr;
	for (int i = 0; i < a.length(); i++)
	{
		rev_arr.push_back(a[a.length() - i - 1]);
	}
	return rev_arr;
}



//ham chuyen tu thap phan sang nhi phan
string DecToBin(string userInputStr)
{
	string binary;

	bool IsSigned = false;
	if (userInputStr[0] == '-')
	{
		IsSigned = true;
		userInputStr.erase(0, 1);
	}

	for (unsigned short int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary.push_back('1');
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary.push_back('0');
		userInputStr = chia2(userInputStr);
	}
	string res = reverse(binary);

	if (IsSigned)
	{
		res = bu2(res);
	}
	return res;

}


//Ham nhap so QInt, con thieu cai doc File, ko biet cho 2 tham so co dc ko
void ScanQInt(QInt &number, string userInputStr)
{
	initQInt(number);

	string binArr = DecToBin(userInputStr);

	number = Arr_To_QInt(binArr);

	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(number.data[i]);
	}
}

string operator * (string bigNumber, int x)
{
	string res = "";
	int len = bigNumber.length();
	int tmp = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (bigNumber[i] == '.')
		{
			res.insert(0, 1, '.');
		}
		else
		{
			tmp = stringToNum(bigNumber[i]) * x + tmp;
			res.insert(0, 1, numToString(tmp % 10));//lay phan don vi cho vao string
			tmp = tmp / 10;// lay phan chuc de tinh tiep
		}

	}
	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}

string _x_mu_n(int coSo, int soMu)
{
	string res = "1";
	for (int i = 1; i <= soMu; i++)
	{
		res = res * coSo;
	}
	return res;

}

// cho do dai 2 chuoi bang nhau de cong 2 chuoi lai
void canBang2Chuoi(string& a, string& b)
{
	int a_len = a.length(), b_len = b.length();
	if (a_len > b_len)
	{
		b.insert(0, a_len - b_len, '0');
	}
	else
	{
		a.insert(0, b_len - a_len, '0');
	}
}


//Ham cong 2 chuoi bigInt
string operator + (string& a, string& b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();

	int tmp = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		tmp = stringToNum(a[i]) + stringToNum(b[i]) + tmp;
		res.insert(0, 1, numToString(tmp % 10));
		tmp /= 10;
	}
	if (tmp > 0)
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}
//================== OPERATOR - CHO 2 CHUOI SO NGUYEN LON ===================
string phepTru2Chuoi(string& soTru, string& soBiTru)
{
	string res; 
	canBang2Chuoi(soTru, soBiTru);
	int len = soTru.length();
	int tmp = 0;// soNho
	int hieu;
	for (int i = len - 1; i >= 0; --i)
	{

		if (soTru[i] < soBiTru[i]) //Neu tai vi tri dg xet, (soBiTru < soTru ) lay (soBiTru + 10 ) - soBiTru
		{
			hieu = (stringToNum(soTru[i]) + 10) - stringToNum(soBiTru[i]) - tmp;
			tmp = 1;
		}
		else// neu soBiTru lon hon thi lay (SoBiTru - soTru)
		{
			hieu = stringToNum(soTru[i]) - stringToNum(soBiTru[i]) - tmp;
		}
		res.insert(0, 1, numToString(hieu));// bo ket qua tinh dc theo hang vao chuoi res
	}
	return res;
}

//Ham tru 2 chuoi BigInt
string operator - (string& a, string& b)
{
	string res = "";
	canBang2Chuoi(a, b);

	int soTruCoLonHonSoBiTru = a.compare(b);//kiem tra xem so a co nho hon so b ko de ra ket qua am
	if (soTruCoLonHonSoBiTru >= 0)// Neu a >= b
	{
		res = phepTru2Chuoi(a, b);
	}
	else //Neu a<b
	{
		res = phepTru2Chuoi(b, a);
		res.insert(0, 1, '-');
	}
	
	
	return res;
}
//========================================================================================



// Ham chuyen tu nhi phan sang thap phan
string BinToDec(string bit)
{
	string decNum, tmp;
	for (int i = 0; i < bit.length(); i++)
	{
		if (bit[i] == '1')
		{
			tmp = _x_mu_n(2,bit.length() - 1 - i); //2^i, voi i thuoc [bit.length(),0]
			decNum = decNum + tmp;// Cong don tat ca cac 2^i
		}
	}
	return decNum;
}

int main()
{
	string a = "00001111";
	string b = "60";
	QInt aa;
	string bin = BinToDec(a);
	cout << bin;

	system("pause");
	return 0;
}
