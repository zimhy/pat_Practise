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
bool table_isValid[101];
bool table_isVip[101];
int table_count[101];
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
queue<Player> w_n_player;
queue<Player> w_vip_player;
queue<Player> w_all_player;



int getValidTable(Player * player)
{
	int result = -1;
	
		for (int i = 1; i <= tables_num; i++)
		{
			if (table_isValid[i] )
			{
				return i;
			}
		}
	

	return -1;
}


string addMinutes(string time, int min)
{
	if (min > 120)
	{
		min = 120;
	}
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
	int freeTabe_num = getValidTable(event.player);
	if (freeTabe_num != -1)
	{
		
		//cout << "player" + event.event_time << "play table " << freeTabe_num << endl;
		table_isValid[freeTabe_num] = false;
		string event_time = addMinutes(event.event_time, event.player->playTime);
		struct Event e_table_free = { table_free,0 ,freeTabe_num ,event_time };
		q_events.push(e_table_free);
		//cout << event.player->time << ' ' << event.event_time << ' ' << 0 << endl;
		printf("%s %s %d %d %d\n", event.player->time.data(), event.player->time.data(), 0 ,freeTabe_num ,event.player->playTime);
		table_count[freeTabe_num]++;
	}
	else
	{
		//cout << "player" + event.event_time << "wait" << endl;
		if (event.player->isvip)
		{
			w_vip_player.push(*event.player);
			w_all_player.push(*event.player);
		}
		else
		{
			w_n_player.push(*event.player);
			w_all_player.push(*event.player);
		}

		//cout << "player--" << event.player->time << "wait--"  << endl;
	}

}

Player seclectPlayer(int tableNum)
{
	Player player;
	if (table_isVip[tableNum] && w_vip_player.empty())
	{
		return player;
	}
	if (!table_isVip[tableNum]&&w_vip_player.empty() && w_n_player.empty())
	{
		return player;
	}
	if (!w_vip_player.empty() && !w_n_player.empty())
	{
		Player v_player = w_vip_player.front();
		Player *p_v_player = &v_player;
		Player n_player = w_n_player.front();
		Player *p_n_player = &n_player;
		if (v_player.time > n_player.time)
		{
			return n_player;
		}
		else
		{
			return v_player;
		}
	}
	if (w_vip_player.empty() && !w_n_player.empty())
	{
		Player n_player = w_n_player.front();
		return n_player;
	}
	if (!w_vip_player.empty() && w_n_player.empty())
	{
		Player v_player = w_vip_player.front();
		return v_player;
	}
}

void handle_free_table(Event &event)
{
	Player player = seclectPlayer(event.table_num);
	if (player.time.compare(string("")) == 0)
	{
		table_isValid[event.table_num] = true;
	}
	else
	{
		
		
		printf("%s %s %d %d %d \n", player.time.data(), event.event_time.data(), cal_wait_time(player.time, event.event_time),event.table_num,player.playTime);
		//cout << player.time << ' ' << event.event_time << ' ' << cal_wait_time(player.time, event.event_time) << endl;
		table_count[event.table_num]++;
		int playtime = player.playTime;
		string eventTime_f_t = addMinutes(event.event_time, playtime);
		struct Event event_f_t = { table_free , 0 ,event.table_num,eventTime_f_t };
		q_events.push(event_f_t);
		if (player.isvip)
		{
			w_vip_player.pop();
		}
		else
		{
			w_n_player.pop();
		}
	}
}



int main_1026(int argc, const char * argv[]) {
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
	//cout << endl;
	cin >> tables_num;//TODO
	return  0;
}
