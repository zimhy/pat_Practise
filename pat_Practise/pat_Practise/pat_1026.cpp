//
//  pat_1026.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/17.
//  Copyright © 2015年 menghaizhang. All rights reserved.
//


#include <iostream>
#include <string>
#include <sstream>
#include<algorithm>
#include <time.h>
#include <vector>
#include <queue>
using namespace std;

const int player_come = 1;
const int table_free = 2;

struct Player {
	string time;
	int playTime;
	bool isvip;

};


struct Event {
	int event_type;
	Player *player;
	int table_num;
	string event_time;

};

vector<Player> players;
bool table_isValid[100];
bool table_isVip[100];
int table_count[100];
int tables_num = 0;
int players_num = 0;

struct cmp_event {
	bool operator()(Event a, Event b) {
		return a.event_time > b.event_time;
	}
};


struct cmp_player {
	bool operator()(Player a, Player b) {
		return a.time > b.time;
	}
};

priority_queue<Event, vector<Event>, cmp_event> q_events;
priority_queue<Player, vector<Player>, cmp_player> w_n_player;
priority_queue<Player, vector<Player>, cmp_player> w_vip_player;


string addMinutes(string time, int min)
{
	int hours = atoi(time.substr(0, 2).c_str());
	int minutes = atoi(time.substr(3, 5).c_str());
	int seconds = atoi(time.substr(6, 8).c_str());
	hours += min / 60;
	minutes += min % 60;
	if (minutes >= 60)
	{
		hours++;
		minutes = minutes % 60;
	}
	stringstream ss;
	if (hours < 10)
	{
		ss << 0;
	};
	ss << hours << ':';
	if (minutes < 10)
	{
		ss << 0;
	};
	ss << minutes << ':';

	if (seconds < 10)
	{
		ss << 0;
	};
	ss << seconds;
	return ss.str();
}

int cal_wait_time(string time_c, string time_s)
{
	int hours_c = atoi(time_c.substr(0, 2).c_str());
	int minutes_c = atoi(time_c.substr(3, 5).c_str());
	int seconds_c = atoi(time_c.substr(6, 8).c_str());

	int hours_s = atoi(time_s.substr(0, 2).c_str());
	int minutes_s = atoi(time_s.substr(3, 5).c_str());
	int seconds_s = atoi(time_s.substr(6, 8).c_str());
	

	int sec_to_min = 0;
	if (seconds_s - seconds_c >= 30)
	{
		sec_to_min = 1;
	}
	if (seconds_s - seconds_c <= -30)
	{
		sec_to_min = -1;
	}

	
	


	return (hours_s - hours_c) * 60 + minutes_s - minutes_c + sec_to_min;
}

void handle_player_come(Event &event)
{

	//cout << "player" + event.event_time << "come";
	int freeTabe_num = -1;
	for (int i = 1; i <= tables_num; i++)
	{
		if (table_isValid[i])
		{
			freeTabe_num = i;
			i = tables_num ;
		}
	}
	if (freeTabe_num != -1)
	{
		//cout << "player" + event.event_time << "play table " << freeTabe_num << endl;
		table_isValid[freeTabe_num] = false;
		string event_time = addMinutes(event.event_time, event.player->playTime);
		struct Event e_table_free = { table_free,0 ,freeTabe_num ,event_time };
		q_events.push(e_table_free);
		cout << event.player->time << ' ' << event.event_time << ' ' << 0 << endl;
		table_count[freeTabe_num]++;


	}
	else
	{
		//cout << "player" + event.event_time << "wait" << endl;
		if (event.player->isvip)
		{
			w_vip_player.push(*event.player);
		}
		else
		{
			w_n_player.push(*event.player);
		}

	}

}

void handle_free_table(Event &event)
{
	//cout << "table" <<event.table_num<< "    "+event.event_time << "free" << endl;
	if (w_n_player.empty() && w_vip_player.empty())
	{
		table_isValid[event.table_num] = true;
	}
	else {

		int playtime = 0;
		if (table_isVip[event.table_num] && !w_vip_player.empty())
		{
			Player player = w_vip_player.top();
			cout << player.time << ' ' << event.event_time << ' ' << cal_wait_time(player.time, event.event_time) << endl;
			table_count[event.table_num]++;

			playtime = player.playTime;
			w_vip_player.pop();

		}
		else {
			Player player;
			if (!w_n_player.empty() && !w_vip_player.empty())
			{
				Player player_n =  w_n_player.top();
				Player player_v = w_vip_player.top();

				if (player_n.time < player_v.time)
				{
					player = player_n;
					w_n_player.pop();
				}
				else {
					player = player_v;
					w_vip_player.pop();
				}
			}
			else
			{
				if (w_vip_player.empty())
				{
					player = w_n_player.top();
					w_n_player.pop();
				}
				else
				{
					player = w_vip_player.top();
					w_vip_player.pop();
				}
			}
			cout << player.time << ' ' << event.event_time << ' ' << cal_wait_time(player.time, event.event_time) << endl;
			table_count[event.table_num]++;
			//cout << "player" + event.event_time << "play table "<<event.table_num <<endl;
			playtime = player.playTime;

		}
		string eventTime_f_t = addMinutes(event.event_time, playtime);

		struct Event event_f_t = { table_free , 0 ,event.table_num,eventTime_f_t };
		q_events.push(event_f_t);





	}
}

int main(int argc, const char * argv[]) {
	cin >> players_num;
	for (int i = 0; i < players_num; i++)
	{
		string time;
		int playTme;
		int isVip;
		cin >> time >> playTme >> isVip;
		struct Player player { time, playTme, isVip == 1 };
		players.push_back(player);
	}

	cin >> tables_num;
	int vip_tables_num;
	cin >> vip_tables_num;

	for (int i = 1; i <= tables_num; i++)
	{
		table_count[i] = 0;
		table_isValid[i] = true;
	}
	for (int i = 1; i <= vip_tables_num; i++)
	{
		int vip_table_num;
		cin >> vip_table_num;
		table_isVip[vip_table_num] = true;

	}

	for (int i = 0; i < players_num; i++)
	{
		struct Event event_p_c = { player_come,&players[i],0,players[i].time };


		q_events.push(event_p_c);
	}
	while (!q_events.empty())
	{
		struct Event event = q_events.top();
		if (event.event_time < "21:00:00")
		{
			if (event.event_type == player_come)
			{
				handle_player_come(event);
			}
			else
			{
				handle_free_table(event);
			}
		}
		q_events.pop();

	}
	for (int i = 1; i <= tables_num; i++)
	{
		cout << table_count[i] << " ";
	}
	cout << endl;

	//cin >> tables_num;//TODO



	return  0;
}
