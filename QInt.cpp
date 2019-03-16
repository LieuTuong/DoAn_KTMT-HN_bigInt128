#include"xuLiStringBigNumber.h"
#include<bitset>

using namespace std;
#define MAX 128

// do ko chac unsigned int luon la 4 bytes, nen dung unit32_t
typedef struct
{
	uint32_t data[4];

}QInt;

//int MAXBIT(string userInputStr)
//{
//	if (userInputStr[0] == '-')
//	{
//		userInputStr.erase(0, 1);
//	}
//	int len = userInputStr.length();
//	if (len <= 3)return 8;
//	else if (len > 3 && len <= 5) return 16;
//	else if (len > 5 && len <= 10) return 32;
//	else if (len > 10 && len <= 19) return 64;
//	else if (len > 19 && len <= 39)return 128;
//	else return 0;
//}



//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
}


// Ham lay bu 1
string bu1(string a)
{
	string tmp;
	for (int i = 0; i < MAX; i++)
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
	for (int i = MAX - 1; i >= 0; i--)
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
	for (int i = 0; i < MAX; i++)
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
	
	string _128bit = binArr;
	int n = binArr.length();
	if (n < 128)
	{
		_128bit.insert(0, 128 - n, '0');
	}

	QInt number;
	initQInt(number);
	for (int i = 0; i < MAX; i++)
	{
		if (_128bit[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}



//he 10 -> he 2
string DecToBin(string userInputStr)
{
	string binary(MAX,'0');
	
	//Kiem tra xem userInputStr co phai la so am ko
	bool IsSigned = IsSign(userInputStr);
	if (IsSigned)
	{		
		userInputStr = absolute(userInputStr); //Lay tri tuyet doi cua chuoi
	}
	

	// chia userInputStr cho 2 r lay so du bo vao binary
	for ( int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary[i]='1';
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary[i]='0';
		userInputStr = chia2(userInputStr);
	}

		//Dao chuoi lai
		binary = reverse(binary);

		if (IsSigned) //Neu la so am, thi bieu dien so bu 2
		{
			binary = bu2(binary);
		}
	
		return binary;

	}


// he 2 -> he 10
string BinToDec(string bit)
{
	string decNum, tmp;
	
	
	for (int i = 0; i < bit.length(); i++)
	{
		if (bit[i] == '1')
		{
			tmp = _x_mu_n(2, bit.length() - i - 1);
			if (i == 0)// so la so am
			{
				tmp = tmp * -1;
			}
		}
		else
			tmp = "0";
		decNum = decNum + tmp;
	}
	return decNum;
}

//ham chuyen (bo 4 bit) Bin sang gia tri HEX tuong ung
char nibbles(string binVal)
{
	char c ;

	if      (binVal == "0000") c = '0';
	else if (binVal == "0001") c = '1';
	else if (binVal == "0010") c = '2';
	else if (binVal == "0011") c = '3';
	else if (binVal == "0100") c = '4';
	else if (binVal == "0101") c = '5';
	else if (binVal == "0110") c = '6';
	else if (binVal == "0111") c = '7';
	else if (binVal == "1000") c = '8';
	else if (binVal == "1001") c = '9';
	else if (binVal == "1010") c = 'A';
	else if (binVal == "1011") c = 'B';
	else if (binVal == "1100") c = 'C';
	else if (binVal == "1101") c = 'D';
	else if (binVal == "1110") c = 'E';
	else if (binVal == "1111") c = 'F';
	
	return c;
}

// he 2 -> he 16
string BinToHex(string bin)
{
	string res="0x";
	int Blen = bin.length();
	if (Blen % 4 == 1) //neu Blen ko chia het cho 4, thi them n so 0 sao cho (n + Blen) chia het cho 4
	{
		int newLen = 4 *  ((Blen / 4) + 1);
		bin.insert(0, newLen - Blen, '0');
	}

	//Tach chuoi thanh tung bo 4, r doi nhung bo 4 do sang Hex tuong ung
	for (int i=0;i<bin.length();i+=4)
	{
		string bo4Bit;
		int k = i;
		int j = 1;
		while (j <= 4)
		{
			bo4Bit.push_back(bin[k]);
			k++;
			j++;
		}
		res.push_back(nibbles(bo4Bit));
	}
	
	return res;
}


// he 10 -> he 16
string DecToHex(string dec)
{
	string res;
	res = DecToBin(dec);
	res = BinToHex(res);
	
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

//ham xuat so QInt, xuat ra so he thap phan
void PrintQInt(QInt number)
{
	//chuyen tu QInt sang mang a
	string bin = QInt_To_Arr(number);

	//Tu mang nhi phan a chuyen sang so thap phan	
	string decNum = BinToDec(bin);
	
	cout << "\nSo chuyen sang he thap phan: ";
	cout << decNum;
}

bool IsNegative(string num)
{
	return (num[0] == '1') ? true : false;
}

bool IsEqual(const QInt& N1, const QInt& N2)
{
	string n1 = QInt_To_Arr(N1);
	string n2 = QInt_To_Arr(N2);
	return n1 == n2;
}

bool IsLess(const QInt& N1, const QInt& N2)
{
	//chuyen QInt qua mang de so sanh
	string n1 = QInt_To_Arr(N1);
	string n2 = QInt_To_Arr(N2);

	//xet dau cua 2 QInt 
	bool sign1 = IsNegative(n1);
	bool sign2 = IsNegative(n2);

	if (sign1 && !sign2)// n1 am, n2 duong
	{
		return true;
	}
	else if (!sign1 && sign2)
	{
		return false;
	}

	else// n1, n2 cung dau 
	{
		int viTriBit1_n1 = n1.find_first_of('1');
		int viTriBit1_n2 = n2.find_first_of('1');
		
		while (1)
		{
			{
				if (viTriBit1_n1 > viTriBit1_n2)//vi tri bit 1 cua a > vi tri bit 1 dau tien cua b
					return true;
				else if (viTriBit1_n1 < viTriBit1_n2)
					return false;
				else  //viTriBit1_n1 == viTriBit1_n2
				{
					viTriBit1_n1 = n1.find_first_of('1', viTriBit1_n1+1); //Tim vi tri bit 1 tiep theo
					viTriBit1_n2 = n2.find_first_of('1', viTriBit1_n2+1);
				}
			}
		}
	}

}

bool IsGreater(const QInt& N1, const QInt& N2)
{
	return !IsLess(N1, N2) && !IsEqual(N1, N2);
}

bool operator < (const QInt& N1, const QInt& N2)
{
	return IsLess(N1, N2);
}

bool operator > (const QInt& N1, const QInt& N2)
{
	return IsGreater(N1, N2);
}

bool operator <= (const QInt& N1, const QInt& N2)
{
	return IsLess(N1, N2) || IsEqual(N1, N2);
}

bool operator >= (const QInt& N1, const QInt& N2)
{
	return IsGreater(N1, N2) || IsEqual(N1, N2);
}

int main()
{
	string x = "-15";
	string y = "-3";
	QInt a, b;
	ScanQInt(a, x);
	ScanQInt(b, y);

	if (a <= b)
		cout << "\nDung";
	else cout << "\nSai";

	system("pause");
	return 0;
}
