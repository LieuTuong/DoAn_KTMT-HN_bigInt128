#include"xuLiStringBigNumber.h"

int stringToNum(char c)     // chuyen char sang so
{
	return c - '0';
}

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}

//Kiem tra dau cua num
bool IsSign(string num)
{
	return (num[0] == '-') ? true : false;
}

//Cai dat dau cho num
void setSign(string& num, bool s)
{
	if (s == true && !IsSign(num))
		num.insert(0, 1, '-');
	else if (s == false && IsSign(num))
		num.erase(0, 1);
}


// Ham lay tri tuyet doi cua num
string absolute(string num)
{
	string res = num;
	if (IsSign(num))//Neu la so am thi bo dau -
		res.erase(0, 1);
	return res;
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

string operator * (string bigNumber, int x)
{
	string res = "";
	bool sign = false;

	if (IsSign(bigNumber) && x > 0 || !IsSign(bigNumber) && x < 0) sign = true;//Xet dau cua bigNumber va x de suy ra dau cua res

	//chuyen tat ca ve so duong de tinh
	bigNumber = absolute(bigNumber);
	if (x < 0) x *= -1;

	//Neu nhan vs 0 thi kq =0
	if (x == 0) return "0";


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
			tmp += stringToNum(bigNumber[i]) * x;
			res.insert(0, 1, numToString(tmp % 10));//lay phan don vi cho vao string
			tmp /= 10;// lay phan chuc de tinh tiep
		}
	}

	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}

	if (sign)// Neu la so am thi them dau -
		setSign(res, true);
	return res;
}

string _x_mu_n(int coSo, int soMu)
{
	bool soAm = false;
	if (coSo < 0)
	{
		soAm = (soMu % 2 == 0) ? false : true;
		coSo *= -1;
	}


	string res = "1";
	for (int i = 1; i <= soMu; i++)
	{
		res = res * coSo;
	}
	if (soAm)
		res.insert(0, 1, '-');

	return res;

}

bool operator>(string a, string b)
{
	return false;
}

bool operator<(string a, string b)
{
	return false;
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


string subtract(string soTru, string soBiTru)
{
	string res;

	//Lay tri tuyet doi 2 so
	soTru = absolute(soTru);
	soBiTru = absolute(soBiTru);
	//
	canBang2Chuoi(soTru, soBiTru);

	int len = soTru.length();
	int hieu, tmp;
	for (int i = len - 1; i >= 0; --i)
	{

		if (soTru[i] < soBiTru[i]) //Neu tai vi tri dg xet, (soBiTru < soTru ), phan tu tiep theo -1 do muon 1
		{
			hieu = stringToNum(soTru[i]) + 10 - stringToNum(soBiTru[i]);
			tmp = stringToNum(soTru[i - 1]) - 1;
			soTru[i - 1] = numToString(tmp);
		}
		else
		{
			hieu = stringToNum(soTru[i]) - stringToNum(soBiTru[i]);
		}
		res.insert(0, 1, numToString(hieu));// bo ket qua tinh dc theo hang vao chuoi res
	}
	while (res[0] == '0' && res.length() != 1)// bo so 0 du
		res.erase(0, 1);
	return res;
}



string add(string a, string b)
{
	string res = "";
	//Lay tri tuyet doi 2 so
	a = absolute(a);
	b = absolute(b);

	//
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


//Ham cong 2 chuoi bigInt
string operator + (string a, string b)
{
	string res;
	if (IsSign(a) == IsSign(b))//Neu 2 so cung dau
	{
		res = add(a, b);
		setSign(res, IsSign(a));// Xet dau cho res theo dau cua a
	}
	else//Neu 2 so khac dau
	{
		if ( Greater(absolute(a) , absolute(b)) )//Neu |a| > |b|
		{
			res = subtract(a, b);
			setSign(res, IsSign(a));//Xet dau cua res theo dau cua so lon hon			
		}
		else
		{
			res = subtract(b, a);
			setSign(res, IsSign(b));
		}
	}

	if (res == "0")// Tranh truong hop (-0), neu = 0 thi bo dau -
		setSign(res, false);
	return res;
}



//Ham tru 2 chuoi BigInt
string operator - (string a, string b)
{
	setSign(b, !IsSign(b)); // a - b = a + (-y)
	return a + b;
}


bool equals(string a, string b)
{
	return (a == b && IsSign(a) == IsSign(b));
}



bool Less(string n1, string n2)
{
	int len1 = n1.length();
	int len2 = n2.length();

	bool s1 = IsSign(n1);
	bool s2 = IsSign(n2);

	if (s1 && !s2)// n1 so am, n2 so duong
		return true;
	else if (!s1 && s2)//n1 duong, n2 am
		return false;

	else if (!s1) // deu duong
	{

		if (len1 < len2) return true;
		if (len1 > len2) return false;
		return n1 < n2;
	}
	else// deu am
	{
		if (len1 > len2)return true;
		if (len1 < len2)return false;
		return n1.compare(n2) > 0;
	}
	
}


bool Greater(string a, string b)
{
	return !Less(a, b) && !equals(a, b);
}


