//
//  pat_1055.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/20.
//  Copyright © 2015年 menghaizhang. All rights reserved.
//
#include <string>
#include <stdio.h>
#include <vector> 
# include <iostream>
#include<algorithm>
using namespace std;
struct Person {
	string name;
	int age;
	int wealth;
};
bool compare(const Person &a,const  Person &b)
{
	if(a.wealth != b.wealth)
		return a.wealth > b.wealth;
	else if (a.age != b.age)
	{
		return a.age < b.age;
	}
	else
	{
		int result =  a.name.compare(b.name);
		if (result >=0)
			return false;
		else
			return true;
	}
}
struct Case
{
	int num;
	int max_age;
	int min_age;
	vector <Person> persons ;

};

int main (int argc, const char * argv[])
{
	vector <Person> persons;
	vector <Case> cases;
	int number_per, number_case;
	cin >> number_per >> number_case;
	if (number_case > 1000)
	{
		number_case = 1000;
	}
	
	for (int i = 0; i < number_per; i++)
	{
		string name;
		int age, wealth;
		cin >> name >> age >> wealth;

		if (age <= 200)
		{
			Person person = { name ,age ,wealth };
			persons.push_back(person);
		}
	}

	sort(persons.begin(),persons.end(), compare);
	
	for (int i = 0; i < number_case; i++)
	{
		Case out_case;
		cin >> out_case.num >> out_case.min_age >> out_case.max_age; 
		if (out_case.num > 100)
		{
			out_case.num = 100;
		}
		cases.push_back(out_case);
		
	}
	
	for (int i = 0; i < cases.size(); i++)
	{
		Case output_case = cases[i];
		bool is_full = false;
		bool is_empty = true;
		int person_count = 0;
		cout << "Case #" << i + 1 << ":" << endl;
		for (int j = 0; j<persons.size()&&!is_full; j++)
		{
			
			Person person = persons[j];
			if (person.age <= output_case.max_age && person.age >= output_case.min_age)
			{
				//output_case.persons.push_back(person) ;
				is_empty = false;
				cout << person.name << " " << person.age << " " << person.wealth << endl;
				person_count++;
				
			}
			if (person_count>= output_case.num)
			{
				is_full = true;
			}
		}
		if (is_empty)
		{
			cout << "None" << endl;
		}
		//cases[i] = output_case;
	}
	system("PAUSE");
	//system.
}