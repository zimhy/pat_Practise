
#include <string>
#include <stdio.h>
#include <vector> 
# include <iostream>
#include<algorithm>
using namespace std;

struct Big_Float
{
	int digit;
	string num_s;
};

bool is_less_than_one(string num)
{
	int dot_position = num.find('.');
	if (dot_position != num.npos)
	{
		for (int i = 0; i < dot_position; i++)
		{
			if (num[i] > '0')
				return false;
		}
		return true;
	}
	return false;
}
bool iszero(string num)
{
	for (int i = 0; i < num.length(); i++)
	{
		if (num[1] != '0' && num[i] != '.')
		{
			return false;
		}
	}
	return true;
}
Big_Float  conver_num(string &num)
{
	int dot_position = num.find('.');//小数点的位置
	bool is_less = is_less_than_one(num);//绝对值是否小于1
	//int result = 0;
	
	if (dot_position == -1) //字符串里面没有小数点
	{
		int useless_zero_count  = 0;
		for (int i = 0; i < num.size(); i++)
		{
			if (num[i] == '0')
				useless_zero_count++;
			else {
				Big_Float result_num = { num.length() - useless_zero_count ,num.substr(useless_zero_count , num.length()) };
				return result_num;
			}

		}
		Big_Float result_num = { 0 , "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" };
		return result_num;
	}else
	if (is_less)
	{
		int zero_cout = 0;
		bool end = false;
		if (iszero(num))
		{
			Big_Float result_num = { 0 , "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" };
			return result_num;
		}
		for (int i = dot_position+1; i < num.length()&&!end ; i++)
		{
			if (num[i] == '0')
			{
				zero_cout--;
			}
			else
			{
				Big_Float result_num = { zero_cout, num.substr(i, num.length()) };
				return result_num;
			}
		}
		
	}
	else
	{
		int j = 0;
		bool is_useless_zero = true;
		int count_useless_zero = 0; 
		
		string num_s ;
		
		for (int i = 0; i < num.length(); i++)
		{
			if (num[i] != '0')
			{
				is_useless_zero = false;
			}
			if (is_useless_zero&&num[i] == '0')
			{
				count_useless_zero++;
				//i--;
				//num.erase(i, i + 1);
			}
			

		if (num[i]!= '.'&&!(is_useless_zero&&num[i] == '0'))
			{
				char digit_c = num[i];
				num_s += digit_c;
				
				
			}
			
		}
		Big_Float result_num = { dot_position - count_useless_zero ,num_s };
		return result_num;
	}

}
void print(Big_Float num ,int num_sig )
{
	cout << "0.";
	for (int i = 0; i < num_sig; i++)
	{
		if(i<num.num_s.length())
		cout << num.num_s [i];
		else
		{
			cout << '0';
		}
		
	}
	cout << "*10^";
	cout << num.digit;
	
}

int main_1060(int argc ,const char * argv[])
{
	int num_sig;
	string num1, num2;
	cin >>num_sig >> num1 >> num2;
	char num1_c[100];
	if (num_sig > 100)
	{
		num_sig = 100;
	}
	//strcpy_s(num1_c,sizeof(num1_c), "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	char num2_c[100];
	//strcpy_s(num2_c, sizeof(num2_c), "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	Big_Float num1_bg = conver_num(num1);
	Big_Float num2_bg = conver_num(num2);
	bool is_match = true  ;
	if (num1_bg.digit == num2_bg.digit)
	{
		for (int i = 0; i < num_sig&&is_match; i++)
		{
			char c_num1 = '0';
			char  c_num2 = '0';
			if (i < num1_bg.num_s.length())
			{
				c_num1 = num1_bg.num_s[i];
			}
			if (i < num2_bg.num_s.length())
			{
				c_num2 = num2_bg.num_s[i];
			}
			if (c_num1 != c_num2)
			{
				is_match = false;
			}
		}
	}
	else { 
		is_match = false;
	}

	if (is_match)
	{
		cout << "YES ";
		print(num1_bg, num_sig);
	}
	else
	{
		cout << "NO ";

		
		print(num1_bg, num_sig);
		cout <<" ";
		print(num2_bg, num_sig);
	}
	
	//system("PAUSE");
	//system.
	return 0;


}