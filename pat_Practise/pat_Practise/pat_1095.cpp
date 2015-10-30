#include<stdio.h> 
#include<iostream>
#include<vector> 
#include<map> 
#include <stdlib.h>
#include <time.h>
#include<string>
#include<queue>
#include<sstream>
#include<algorithm>

using namespace std;
const string  TYPE_IN = "in";
const string TYPE_OUT = "out";
const string TYPE_PRINT = "print";
struct Count_record
{
	string time;
	int count;
};
struct  Car 
{
	bool is_in;
	string plate_number;
	string in_time;
	string out_time;
	string stay_time;

};

struct  Event 
{
	string event_type;
	string time;
	string plate_number;

};

void  cal_stay_time(Car &car)
{
	time_t lt_in = time(NULL);
	time_t lt_out = time(NULL);
	tm *tm_in = localtime(&lt_in);
	tm *tm_out = localtime(&lt_out);
	if (car.in_time.length() == car.out_time.length() && car.out_time.length ()== 8)
	{
		tm_in->tm_hour = atoi(car.in_time.substr(0, 2).data());
		tm_in->tm_min = atoi(car.in_time.substr(3, 5).data());
		tm_in->tm_sec = atoi(car.in_time.substr(6, 8).data());
		time_t lt_in = mktime(tm_out);
		tm_out->tm_hour = atoi(car.out_time.substr(0, 2).data());
		tm_out->tm_min = atoi(car.out_time.substr(3, 5).data());
		tm_out->tm_sec = atoi(car.out_time.substr(6, 8).data()); 
		time_t lt_out = mktime(tm_in);
		double l_stay_seconds = difftime(lt_out,lt_in );
		char buffer[32];
		long stay_seconds = (long)l_stay_seconds;
		int hour = stay_seconds / 3600;
		int min = (stay_seconds % 3600) / 60;
		int seconds = stay_seconds % 60;
		stringstream ss;
		if (hour < 10)
			ss << '0';
		ss << hour;
		ss << ':';
		if (min < 10)
			ss << '0';
		ss << min;
		ss << ':';
		if (seconds < 10)
			ss << '0';
		ss << seconds;
		
	
		string stay_time;
		ss >> stay_time;
		car.stay_time = stay_time;

	}
	else {
		car.stay_time == "";
		
	}
}

void handle_in(Event &event, map<string, Car> &map_car ,int &car_count )
{
	if (map_car.find(event.plate_number) == map_car.end())
	{
		car_count++;
	}
	Car car = { true ,event.plate_number ,event.time ,string (""),string("") };
	map_car[event.plate_number] = car;
}

void handle_out(Event &event, map<string, Car> &map_car, int &car_count ,vector<Car> &cars_record )
{
	if (map_car.find(event.plate_number) != map_car.end())
	{
		car_count--;
		Car car = map_car[event.plate_number];
		car.out_time = event.time;
		cal_stay_time(car);
		cars_record.push_back(car);
		map_car.erase(event.plate_number);
	}
}


void handle_print(Event & event, map<string ,Car > &map_car )
{
	if (map_car.empty())
	{
		cout << "0"  << endl;
	}
	else
	{
		cout << map_car.size() << endl;
	}
}
struct cmp_event
{
	bool operator()(Event &a, Event &b)
	{
		int result = a.time.compare(b.time);
		if (result != 0)
		{
			if (result > 0)
			{
				return true;
			}else
			{
				return false;
			}
		}
		else
		{
			result = a.event_type.compare(b.event_type);
			if (result != 0)
			{
				if (result < 0)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				result = a.plate_number.compare(b.plate_number);
				if (result != 0)
				{
					if (result < 0)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
};


bool compare_car (const Car &a ,const Car &b )
{
	int result = a.stay_time.compare(b.stay_time);
	if (result != 0)
	{
		if (result > 0)
			return true;
		else
			return false;
	}
	else
	{
		result = a.plate_number.compare(b.plate_number);
		if (result >= 0)
			return false;
		else
			return true;
	}
}


int main_1095(int argc, const char * argv[])
{
	priority_queue <Event ,vector<Event> ,cmp_event> event_queue;
	map<string, Car > map_car;
	vector <Car> car_record;
	int car_count = 0;
	int car_num, query_num;
	cin >> car_num >> query_num;
	for (int i = 0; i < car_num; i++)
	{
		string plate_num; 
		string in_time, type;
		int event_type;
		cin >> plate_num >> in_time >> type;
		Event event = { type ,in_time ,plate_num };
		event_queue.push(event);
	}
	for (int i = 0; i < query_num; i++)
	{
		
		string time;
		cin >> time ;
		if (time.compare("24:00:00") < 0)
		{
			Event event = { "print" ,time ,"" };
			event_queue.push(event);
		}
	}
	while (!event_queue.empty())
	{
		Event event = event_queue.top();
		if (TYPE_IN.compare(event.event_type) == 0)
		{
			handle_in(event, map_car, car_count);
		}else
		if (TYPE_OUT.compare(event.event_type) == 0)
		{
			handle_out(event ,map_car, car_count, car_record);
		}
		else
		if (TYPE_PRINT.compare(event.event_type) == 0)
		{
			cout << car_count << endl;
		}

		event_queue.pop();

	}
	sort(car_record.begin(), car_record.end(), compare_car);
	string longest = car_record[0].stay_time;
	int i = 0;
	while (longest.compare(car_record[i].stay_time) == 0&i<car_record.size())
	{
		cout << car_record[i].plate_number << " ";
		i++;
	}
	cout << longest;

	//cin >> query_num;
	return 0; 
}