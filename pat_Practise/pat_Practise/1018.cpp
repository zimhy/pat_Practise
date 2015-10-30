#include<stdio.h>
#include<string>
#include <algorithm>
#include <iostream>
#include<vector>
#include <limits>  
using namespace std;

const int MAX_STA = 500;
const int MAX_INT = numeric_limits<int>::max()-1;


int val_road[MAX_STA][MAX_STA];
bool reached_sta[MAX_STA];
int val_sta[MAX_STA];

vector <int> min_path;
int min_length = MAX_INT;
int min_cost = MAX_INT;
vector<int> cur_path;
int cur_length = MAX_INT;
int cur_cost = MAX_INT;
int C_max, N, S_p, M;
int take_out; 
int take_in ;

void    cal_min_take( int &take_out ,int &min_cost )
{
	

	
	for (int i = 0; i < cur_path.size(); i++)
	{
		int this_st = cur_path[i];
		min_cost += C_max / 2 - val_sta[cur_path[i]];
		if (min_cost > take_out)
			take_out = min_cost;
	}
	

	
}
void dfs(int i  )
{
	if (cur_length > min_length)
		return;
	if (val_sta[i] == C_max || val_sta[i] == 0 )
	{
		cur_cost += C_max / 2 - val_sta[i];
		int min_take = 0;
		int  cost = 0 ;
		cal_min_take(min_take ,cost);
		if (cur_length < min_length || (cur_length == min_length &&min_take < take_out)|| (cur_length == min_length &&min_take == take_out&&take_in >= (min_take-cost)))
		{
			min_path.clear();
			for (int j = 0; j < cur_path.size(); j++)
			{
				min_path.push_back(cur_path[j]);
			}
			
			min_length = cur_length;
			take_out = min_take;
			take_in = min_take - cost;

		}
	}
	
	for (int j = 0; j <= N;j++)
	{
		if (!reached_sta[j] && val_road[i][j] != MAX_INT)
		{
			reached_sta[j] = true;
			cur_length = cur_length == MAX_INT ? val_road[i][j] : cur_length + val_road[i][j];
			cur_cost = cur_cost == MAX_INT ? C_max / 2 + val_sta[j] : cur_cost +( C_max / 2 - val_sta[j]);
			cur_path.push_back(j);
			dfs(j);
			reached_sta[j] = false;
			cur_length = cur_length == MAX_INT ? val_road[i][j] : cur_length - val_road[i][j];
			cur_cost = cur_cost == MAX_INT ? C_max / 2 - val_sta[j] : cur_cost - ( C_max / 2 - val_sta[j]);
			cur_path.pop_back();
		}
	}
	

}


int main(int argc, const char * argv[])
{
	for (int i = 0; i < MAX_STA; i++)
	{
		for (int j = 0; j < MAX_STA; j++)
		{
			val_road[i][j]  = MAX_INT;
			//used_road[i][j] = false;
		}
		reached_sta[i] = false;
		val_sta [i]= MAX_INT;
	}
	
	cin >> C_max >> N >> S_p >> M; 
	for (int i = 0; i < N;i++ )
	{
		cin >> val_sta[i+1];
	}
	for (int i =  0; i < M; i++)
	{
		int row, col, val;
		cin >> row >> col >> val;
		val_road[row][col] = val;
		val_road[col][row] = val; 
	}

	reached_sta[0] = true; 
	dfs(0);
	cout << take_out ;
	cout << " 0";
	for (int i = 0; i < min_path.size(); i++)
	{
		cout <<"->"<< min_path[i];
	}
	
	cout << ' '<<take_in;
	
	
}