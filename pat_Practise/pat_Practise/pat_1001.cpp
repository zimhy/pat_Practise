//
//  pat_1001.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/16.
//  Copyright © 2015年 menghaizhang. All rights reserved.
//

#include <iostream>
#include <string>
#include<algorithm>
using namespace std ;

string standardFormat (long input)
{
    bool isNegative = input < 0 ;
    input = abs(input) ;
    string result =  string ("") ;
    int demical_Count = 0 ;
    if (input == 0 )
        return result + '0' ;
    for (; input > 0 ; input/= 10) {
        char temp  = '0' + input % 10 ;
        result = result + temp;
        demical_Count ++ ;
        
        if (demical_Count % 3 == 0&&input > 10 )
        {
            result += ',' ;
        }
        
    }
    reverse(result.begin(), result.end());
    if (isNegative)
    {
        result = '-' + result;
    }
    return result ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    long a , b ;
    while(cin>>a>>b)
    {
    long reslut = a+ b ;
    cout << standardFormat(reslut) ;
        cout <<endl ;
    }
    return 0;
}

