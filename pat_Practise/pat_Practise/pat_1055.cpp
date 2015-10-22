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
bool compare(Person &a, Person &b)
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
	for (int i = 0; i < number_per; i++)
	{
		string name;
		int age, wealth;
		cin >> name >> age >> wealth;
		Person person = { name ,age ,wealth };
		persons.push_back(person);
	}

	sort(persons.begin(),persons.end(), compare);
	for (int i = 0; i < number_case; i++)
	{
		Case out_case  ;
		cin >> out_case.num >> out_case.min_age >> out_case.max_age;
		cases.push_back(out_case);
	}
	for (int i = 0; i < number_case; i++)
	{
		Case output_case = cases[i];
		bool is_full = false;
		for (int j = 0; j<persons.size()&&!is_full; j++)
		{
			Person person = persons[j];
			if (person.age <= output_case.max_age && person.age >= output_case.min_age)
			{
				output_case.persons.push_back(person) ;
				if (output_case.persons.size()>=output_case.num)
				{
					is_full = true;
				}
			}
		}
		cases[i] = output_case;
	}
	for (int i = 0; i < cases.size();i++)
	{
		Case output_case = cases[i];
		cout << "Case #" << i + 1 <<":"<< endl;
		if (output_case.persons.empty())
			cout << "None" << endl;
		else
		{
			for (int j = 0; j < output_case.persons.size(); j++)
			{
				Person person = output_case.persons[j];
				cout << person.name << " " << person.age << " " << person.wealth << endl;
			}
		}

	}

	cin >> number_case;
}