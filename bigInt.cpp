#include"xuLiStringBigNumber.h"
#include<bitset>
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



//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
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
	
	string _128bit = binArr;
	int n = binArr.length();
	if (n < 128)
	{
		_128bit.insert(0, 128 - n, '0');
	}

	QInt number;
	initQInt(number);
	for (int i = 0; i < 128; i++)
	{
		if (_128bit[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}







//ham chuyen tu thap phan sang nhi phan
string DecToBin(string userInputStr)
{
	string binary;

	int SoBitMinDeBieuDien = MAXBIT(userInputStr); // kiem tra xem userInputStr dung may bit la co the bieu dien dc r

	//Kiem tra xem userInputStr co phai la so am ko
	bool IsSigned = false;
	if (userInputStr[0] == '-')
	{
		IsSigned = true;
		userInputStr.erase(0, 1);//Neu la so am thi xoa dau -
	}

	// chia userInputStr cho 2 r lay so du bo vao binary
	for (unsigned short int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary.push_back('1');
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary.push_back('0');
		userInputStr = chia2(userInputStr);
	}

	int bitCanThem = SoBitMinDeBieuDien - binary.length();
	if (bitCanThem > 0) // Vd: neu userInputStr = -2, luc nay chuoi binary = "01", de bieu dien // so 2 thi so bit can nho nhat la 8 bit, can lap them 6 so 0 cho du 8 bit
	{
		while (bitCanThem > 0)
		{
			binary.push_back('0');
			bitCanThem--;
		}

		//Dao chuoi lai
		string res = reverse(binary);

		if (IsSigned) //Neu la so am, thi bieu dien so bu 2
		{
			res = bu2(res);
		}
		return res;

	}
}


//Ham nhap so QInt, con thieu cai doc File, ko biet cho 2 tham so co dc ko
void ScanQInt(QInt &number, string userInputStr)
{
	initQInt(number);
	int bit = MAXBIT(userInputStr);
	string binArr = DecToBin(userInputStr);

	number = Arr_To_QInt(binArr);

	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(number.data[i]);
	}
}


// Ham chuyen tu nhi phan sang thap phan
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
		decNum = decNum + tmp;
	}
	return decNum;
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

int main()
{
	QInt a, b, c;

	/*string x= "15";
	ScanQInt(a, x);
*/
	string v = "11111110";
	string m = BinToDec(v);//loi 
	cout << m;
	system("pause");
	return 0;
}
