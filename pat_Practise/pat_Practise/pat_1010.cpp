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

    unsigned long long   getNumByStringAndRadix (string c_changeNum,     unsigned long long radix )
{
    int result = 0 ;
    
    for (int i=0;i< c_changeNum.length();i++)
    {
        int base =(pow(radix,c_changeNum.length()-1-i)) ;
        result += formatChar2int(c_changeNum[i])* base;
    }
    return result ;
}





string binarySearch (unsigned long long l_baseNum ,string c_changeNum ,    unsigned long long  low,    unsigned long long  high)

{
    
    unsigned long long   l_changeNum = 0 ;
   // cout<<mid <<"-----"<<l_baseNum<<"---"<<l_changeNum<<endl;
    for(;low<=high;)//二分搜索
    {
        unsigned long long  mid=(high+low)/2;
        l_changeNum =  getNumByStringAndRadix(c_changeNum, mid) ;
        if (l_changeNum==l_baseNum)
        {
            char  c_result [255] ;
            sprintf(c_result, "%llu",mid) ;
            return string(c_result) ;
        }else
            if(low == high)
            {return "Impossible" ;}
        else
        {
            if(l_changeNum > l_baseNum){
                high = mid-1;
            }
            else{
                low = mid ;
            }
        }
    }
    
    return "Impossible" ;
}

string getRadix(string s_baseNum ,string s_changeNum ,unsigned long long baseRadix)
{
        unsigned long long   l_baseNum = getNumByStringAndRadix(s_baseNum,baseRadix);
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
    unsigned long long   high_Bound = 0 ;
    bool breakFlag = true ;
   for (unsigned long long  i = minRadix ; breakFlag ;i*=2)
    {
            unsigned long long  l_temp = getNumByStringAndRadix(s_changeNum, i) ;
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


int main_1010(int argc, const char * argv[]) {
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
