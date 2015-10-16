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

    int  getNumByStringAndRadix (string c_changeNum,     int radix )
{
    int result = 0 ;
    
    for (int i=0;i< c_changeNum.length();i++)
    {
        int base =(pow(radix,c_changeNum.length()-1-i)) ;
        result += formatChar2int(c_changeNum[i])* base;
    }
    return result ;
}





string binarySearch (unsigned long long l_baseNum ,string c_changeNum ,    int low,    int high)

{
        int  mid = (low + high ) /2 ;
        int  l_changeNum = getNumByStringAndRadix(c_changeNum, mid) ;
   // cout<<mid <<"-----"<<l_baseNum<<"---"<<l_changeNum<<endl;
    if (l_changeNum == l_baseNum)
    {
        char t[255] ;
        sprintf(t, "%d", mid);
        return string(t);
    }else{
        if(low == high)
            return "Impossible" ;
        else{
            if (l_changeNum > l_baseNum)
            {
                return binarySearch(l_baseNum, c_changeNum, low, mid-1);
            }
            else
            {
                return binarySearch(l_baseNum, c_changeNum, mid+1, high);
            }
        }
    }
    
}

string getRadix(string s_baseNum ,string s_changeNum ,int baseRadix)
{
        int  l_baseNum = getNumByStringAndRadix(s_baseNum,baseRadix);
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
        int   high_Bound = 0 ;
    bool breakFlag = true ;
   for (int i = minRadix ; breakFlag ;i*=2)
    {
            int l_temp = getNumByStringAndRadix(s_changeNum, i) ;
        if (l_temp == l_baseNum)
        {
            ss<<i ;
            return ss.str();
        }else
        {
            if ( l_temp > l_baseNum)
            {
                high_Bound = i ;
                breakFlag = false ;
            }
        }
    }
    
    return binarySearch(l_baseNum, s_changeNum, high_Bound/2, high_Bound) ;
  
    /*
    unsigned long long l_changeNum  = 0 ;
    
    while (l_changeNum < l_baseNum)
    {
        l_changeNum = getNumByStringAndRadix(s_changeNum, minRadix) ;
        if (l_changeNum == l_baseNum)
        {
            stringstream ss ;
            ss << minRadix ;
            return ss.str();
        }else{
            minRadix ++ ;
        }
        
    }
    return "Impossible";
     */
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    string N1 ,N2 ,tag ;
    int radix ;
    cin>>N1 >> N2 >> tag >> radix ;
    
        if (formatChar2int(tag[0]) == 1)
        {
            cout << getRadix(N1, N2, radix) ;
        }
        else{
            cout << getRadix(N2, N1, radix) ;
        }
        
    
    return 0;
}
