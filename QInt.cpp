#include"xuLiStringBigNumber.h"
#include<bitset>

using namespace std;
#define MAX 128

// do ko chac unsigned int luon la 4 bytes, nen dung unit32_t
typedef struct
{
	uint32_t data[4];
}QInt;


//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
}

void them_du_n_bit(string& num, int n_bit=MAX)
{
	int len = num.length();
	if (len < n_bit)
		num.insert(0, n_bit-len, '0');
}

// Ham lay bu 1
string bu1(string a)
{
	string tmp;
	them_du_n_bit(a);
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
template<typename T>
T Arr_To_QInt(const string& binArr)
{
	
	string _128bit = binArr;
	int n = binArr.length();
	if (n < 128)
	{
		_128bit.insert(0, 128 - n, '0');
	}

	T number;
	
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
	string binary;
	char c;
	
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
			c='1';
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else c='0';
		binary.push_back(c);
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

	number = Arr_To_QInt<QInt>(binArr);

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


//=============================  CAC TOAN TU <, >, >=, <= , ==, =
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

bool operator == (const QInt& N1, const QInt& N2)
{
	return IsEqual(N1, N2);
}


//==================================================================================



// ===================TOAN TU &, |, ^, ~ , << , >>
QInt operator & (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] & b.data[i];
	}
	return res;
}




QInt operator | (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] | b.data[i];
	}
	return res;
}



QInt operator ^ (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] ^ b.data[i];
	}
	return res;
}



QInt operator ~ (const QInt& a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = ~a.data[i];
	}
	return res;
}


string dichPhai(const string& a, int bit)
{
	string res;
	if (bit > a.length()) return res;//neu dich so luong bit nhieu hon 128, thi toan bi mang se = 0
	if (bit < 0)
	{
		cout << "\nSo luong bit dich khong hop le." << endl;
		res = a;
	}
	else
	{
		char tmp = (IsNegative(a)) ? '1' : '0';
		for (int i = a.length() - 1; i >= 0; i--)
		{
			char c = (i - bit) < 0 ? tmp : a[i - bit];
			res.push_back(c);
		}
	}
	
	return res;
}

string dichTrai(const string& b, int bit)
{
	string res;
	if (bit > b.length()) return res;
	if (bit < 0)
	{
		cout << "\nSo luong bit dich khong hop le" << endl;
		res = b;
	}
	else
	{
		for (int i = 0; i < b.length(); i++)
		{
			char c = (i + bit) > (b.length() - 1) ? '0' : b[i + bit];
			res.push_back(c);
		}
	}
	return res;
}

// Neu so luong bit dixh < 0 thi xu li nhu the nao, cho i kien???????
QInt operator >> (const QInt& a, unsigned int bit)
{
	string res;
	string A = QInt_To_Arr(a);
	res = dichPhai(A, bit);
	return  Arr_To_QInt<QInt>(res);
}

// thieu truong hop bit < 0
QInt operator << (const QInt& a, int bit)
{

	string A = QInt_To_Arr(a);
	string res = dichTrai(A,bit);	
	return  Arr_To_QInt<QInt>(res);
}



QInt rol(const QInt& a)
{
	string A = QInt_To_Arr(a);

	int MSB = A[0];// giu bit trai nhat 
	for (int i = 0; i < MAX - 1; i++)
	{
		A[i] = A[i + 1];
	}
	A[MAX - 1] = MSB;// bit trai nhat thanh bit phai nhat	
	return  Arr_To_QInt<QInt>(A);
}



QInt ror(const QInt& a)
{
	string A = QInt_To_Arr(a);

	int LSB = A[MAX - 1];
	for (int i = MAX - 1; i > 0; i--)
	{
		A[i] = A[i - 1];
	}
	A[0] = LSB;	
	return Arr_To_QInt<QInt>(A);
}

//===================================================================================================


//================================ TOAN TU + - * /
string CongBit(const string& n1, const string& n2)
{
	string res;
	char c;
	int tmp = 0;
	for (int i = n1.length() - 1; i >= 0; i--)
	{
		tmp = stringToNum(n1[i]) + stringToNum(n2[i]) + tmp;
		if (tmp == 2)
		{	
			c = '0';
			tmp = 1;
		}
		else if (tmp > 2)
		{
			c = '1';
			tmp = 1;
		}
		else
		{
			c = numToString(tmp);
			tmp = 0;			
		}
		res.insert(0, 1, c);
	}
	if (tmp == 1)
		res.insert(0, 1, '1');
	return res;
}




/*Phep tru 2 QInt a va b
   a-b=a+(-b)
   a + soBu2(b)*/
string TruBit(const string& n1, const string& n2)
{
	string bu2_n2 = bu2(n2);
	return  CongBit(n1, bu2_n2);	
}

QInt operator + (const QInt& n1, const QInt& n2)
{
	string res(MAX, '0');
	string num1 = QInt_To_Arr(n1);
	string num2 = QInt_To_Arr(n2);
	res= CongBit(num1, num2);
	return Arr_To_QInt<QInt>(res);
}



QInt operator - (const QInt& n1, const QInt& n2)
{
	string res;
	string num1 = QInt_To_Arr(n1);
	string num2 = QInt_To_Arr(n2);
	res=TruBit(num1, num2);
	return Arr_To_QInt<QInt>(res);
}


//QInt operator * (const QInt& m, const QInt& q)
//{
//	string A(MAX,'0');
//	string M = QInt_To_Arr(m);
//	string Q = QInt_To_Arr(q);
//	string res;
//	int Q0 = 0;
//	int k = MAX;
//	while (k>0)
//	{
//		if ( Q[MAX-1] == '1' && Q0 == 0)
//		{
//			A=TruBit(A,M);
//			Q0 = 1;
//		}
//		else if (Q[MAX-1] == '0' && Q0 == 1)
//		{
//			A = CongBit(A,M);
//			Q0 = 0;
//		}
//
//		//Gop A va Q lai de dich bit
//		string A_Q = A + Q;
//		A_Q = dichPhai(A_Q, 1);//dich phai 1 bit
//
//		//Sau khi gop thi tach A_Q ra lai, nua dau la A, nua sau la Q
//		A.assign(A_Q, 0, MAX);//tach tu 0 den vi tri MAX=128
//		Q.assign(A_Q, MAX, MAX);//tu vi tri 128
//		--k;
//	}
//	//res = A + Q;
//	
//	//Tinh neu ket qua bi tran
//	return Arr_To_QInt(Q);
//
//}


typedef struct
{
	uint32_t data[4];
}QFloat;


int SoPhanTuSauDauCham(string phanThapPhan)
{
	int dauCham = phanThapPhan.find_first_of('.');
	return phanThapPhan.length() - dauCham - 1;
}

//Tao so thuc 1 vs n so 0 ngoai sau
string Float_1(int n)
{
	string res = "1.";
	for (int i = 0; i < n; i++)
		res.push_back('0');
	return res;
}


//chuyen phan thap phan cua QFloat tu Dec -> Bin
string DecToBin_phanThapPhan(string phanThapPhan)
{
	string res;
	while (1)
	{
		phanThapPhan = phanThapPhan * 2;
		int len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		string so1 =Float_1(len_sauDauCham);

		if (phanThapPhan.compare(so1)==0)
		{
			res.push_back('1');
			break;
		}
		else if (phanThapPhan.compare(so1)==1)
		{
			res.push_back('1');
			int DauCham = phanThapPhan.find_first_of('.');
			for (int i = 0; i < DauCham; i++)
				phanThapPhan[i] = '0';
		}
		else
		{
			res.push_back('0');
		}
	}
	return res;
}


//Tach phan nguyen va phan thap phan cua QFloat
void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan)
{
	int len = bigFloat.length();
	int dauCham = bigFloat.find_first_of('.');

	phanNguyen.assign(bigFloat, 0, dauCham);

	phanThapPhan.assign(bigFloat, dauCham, len - phanNguyen.length());//dg co dang (.x)
	phanThapPhan.insert(0, 1, '0');//dua ve dang (0.x)
}


string DecToBin_QFloat(string bigFloat)
{
	string res, phanNguyen, phanThapPhan;
	tachQFloat(bigFloat, phanNguyen, phanThapPhan);

	res = DecToBin(phanNguyen);
	res.append(".");
	res.append(DecToBin_phanThapPhan(phanThapPhan));

	return res;	
}

//Chuan hoa ve dang ( 1.F * 2^E )
int chuanHoaQFloat(string& floatNum)
{
	int exponent;
	int dauCham = floatNum.find_first_of('.');
	int so1DauTien = floatNum.find_first_of('1');

	int viTri = (dauCham > so1DauTien) ? so1DauTien + 1 : so1DauTien;
	floatNum.erase(dauCham, 1);
	floatNum.insert(viTri, 1, '.');
	exponent = (dauCham > so1DauTien) ? dauCham - so1DauTien - 1 : dauCham - so1DauTien;
	return exponent;
}

void ScanQFloat(QFloat& x,string num)
{
	string res;
	char c;
	
	string binFloat = DecToBin_QFloat(num);
	int E = chuanHoaQFloat(binFloat);//Chuan hoa ve dang ( 1.F * 2^E ), tra ve E
	E += 16383;// E+ bias
	string expBin = DecToBin(toString(E));//chuyen so mu sang nhi phan

	binFloat.erase(0, 2);// bo 1.

	if (binFloat.length() < 112)//them so 0 cho du 112 fration
	{
		binFloat.insert(binFloat.length(), 112 - binFloat.length(), '0');
	}

	//Bieu dien bit dau
	c = IsSign(num) ? '1' : '0';
	res.push_back(c);
	cout << "\nDau" << endl;
	cout << res;
	// Bieu dien 15 bit exp
	res.append(expBin);
	cout << "\nPhan exp: " << endl;
	cout << res;
	//Bieu dien 112 fraction
	res.append(binFloat);
	cout << "\nChuoi nhi phan float"<<endl;
	cout << res;

	QFloat Qfloat = Arr_To_QInt<QFloat>(res);

	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(Qfloat.data[i]);
	}
}

int main()
{
	/*string x = "8.21875";
	string res=DecToBin_QFloat(x);
	cout << res<<endl;*/
	string x = "8.21875";
	QFloat a;
	ScanQFloat(a, x);
	
	system("pause");
	return 0;
}
