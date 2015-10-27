#include<stdio.h> 
#include<iostream>
#include<vector> 
#include<map> 
#include <stdlib.h>
#include <time.h>
using namespace std;



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
	int event_type;
	string time;
	string plate_number;

};

void  cal_stay_time(Car &car)
{
	time_t *lt;
	*lt = time(NULL);
	tm *tm_in = localtime(lt) ;
	tm *tm_out = localtime(lt);
	if (car.in_time.length() == car.out_time.length && car.out_time.length == 8)
	{
		tm_in->tm_hour = atoi(car.in_time.substr(0, 2).data());
		tm_in->tm_min = atoi(car.in_time.substr(3, 5).data());
		tm_in->tm_sec = atoi(car.in_time.substr(6, 8).data());
		tm_out->tm_hour = atoi(car.out_time.substr(0, 2).data());
		tm_out->tm_min = atoi(car.out_time.substr(3, 5).data());
		tm_out->tm_sec = atoi(car.out_time.substr(6, 8).data()); 

	}
	else {
		car.stay_time == "";
		
	}
}
void handle_in(Event &event, map<string, Car> &map_car ,int &car_count )
{
	if (map_car.find(event.plate_number) != map_car.end())
	{
		car_count++;
	}
	Car car = { true ,event.plate_number ,event.time ,string (""),string("") };
	map_car[event.plate_number] = car;
}

void handle_out(Event &event, map<string, Car> &map_car, int &car_count ,vector<Car> cars_record )
{
	if (map_car.find(event.plate_number) != map_car.end())
	{
		car_count--;
		Car car = map_car[event.plate_number];
		car.out_time = event.time;

	}
}
int main_1060(int argc, const char * argv[])
{

}