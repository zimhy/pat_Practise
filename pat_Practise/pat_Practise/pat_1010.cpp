//
//  pat_1010.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/16.
//  Copyright © 2015年 menghaizhang. All rights reserved.
//

#include <iostream>
#include <string>
#include<algorithm>
#include <math.h>
#include <sstream>
using namespace std ;

int formatChar2int (char c)
{
    if (c<='9'&&c>='0')
        return c-'0' ;
    else
        if (c<='z'&&c>='a')
            return c-'a'+10 ;
    else
        return 0 ;
}

long getNumByStringAndRadix (string c_changeNum, int radix )
{
    long result = 0 ;
    
    for (int i=0;i< c_changeNum.length();i++)
    {
        int base =(pow(radix,c_changeNum.length()-1-i)) ;
        result += formatChar2int(c_changeNum[i])* base;
    }
    return result ;
}
string getRadix(string s_baseNum ,string s_changeNum ,int baseRadix)
{
    long l_baseNum = getNumByStringAndRadix(s_baseNum,baseRadix);
    int minRadix = 2 ;
    for (int i = 0 ;i <s_changeNum.length() ;i++ )
    {
        int temp = formatChar2int(s_changeNum[i])+1;
       
        if (temp >= minRadix)
        {
            minRadix = temp ;
        }
    }
    stringstream ss;
    for (int i = minRadix ; i < 36 ;i++)
    {
        long l_temp = getNumByStringAndRadix(s_changeNum, i) ;
        if (l_temp == l_baseNum)
        {
            ss<<i ;
            return ss.str();
        }else
        {
            if ( l_temp > l_baseNum)
            {
                return string ("Impossible") ;
            }
        }
    }
    return  "Impossible" ;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string N1 ,N2 ,tag ;
    int radix ;
    while(cin>>N1 >> N2 >> tag >> radix )
    {
        if (formatChar2int(tag[0]) == 1)
        {
            cout << getRadix(N1, N2, radix) ;
        }
        else{
            cout << getRadix(N2, N1, radix) ;
        }
        
    }
    return 0;
}
