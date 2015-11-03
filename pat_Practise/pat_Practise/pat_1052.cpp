
//  main.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/16.
//  Copyright ? 2015Äê menghaizhang. All rights reserved.
//

#include <iostream>
using namespace std;
const int MAX = 200001;
int value_message[MAX][3]; //Í°ÅÅÐò [value ][0.this 1.next 2.exist  ]
int nodes[MAX][2];


int main(int argc, const char * argv[]) {
	// insert code here...
	//std::cout << "Hello, World!\n";
	for (int i = 0; i < MAX; i++)
	{
		value_message[i][2] = 0;
	}
	int N, firstaddr;
	cin >> N >> firstaddr;
	for (int i = 0; i < N; i++)
	{
		int self, value, next;
		cin >> self >> value >> next;
		/*if (value >= -100000 && value <= 100000&&self!=-1)
		{
			value_message[value + 100000][2] = 1;
			value_message[value + 100000][0] = self;
			value_message[value + 100000][1] = next;
		}*/
		nodes[self][0] = value;
		nodes[self][1] = next;
	}
	N = 0;
	int node_add = firstaddr;
	while (node_add != -1)
	{
		int value = nodes[node_add][0];
		int self = node_add;
		int next = nodes[node_add][1];
		value_message[value + 100000][2] = 1;
		value_message[value + 100000][0] = self;
		value_message[value + 100000][1] = next;
		node_add = next;
		N++;
	}




	int pre_val = -1;
	int last = 0;
	for (int i = 0;i < MAX; i++)
	{
		if (value_message[i][2] ==1 )
		{
			last = i;
			if (pre_val != -1)
			{
				value_message[pre_val][1] = value_message[i][0];
			}
			else
			{
				firstaddr = value_message[i][0];
			}
			pre_val = i;
			//value_message[i][1] = -1;
			
		}
	}
	value_message[last][1] = -1;

	cout << N <<" "<< firstaddr<<endl ;
	for (int i = 0; i < MAX; i++)
	{
		if (value_message[i][2] == 1 )
		{
			if (value_message[i][1] != -1)
			{
			//	cout << value_message[i][0] << " " << i - 100000 << " " << value_message[i][1] << endl;
				printf("%05d %d %05d\n", value_message[i][0], i - 100000, value_message[i][1]);
			}
			else
			{
				printf("%05d %d %d\n", value_message[i][0], i - 100000, value_message[i][1]);
			}

		}
	}

	return 0;
}


