//
//  main.cpp
//  pat_Practise
//
//  Created by menghaizhang on 15/10/16.
//  Copyright ? 2015Äê menghaizhang. All rights reserved.
//
#include <iostream>
#include <string>
#include <sstream>
#include<algorithm>
#include <vector>
#include <map>

using namespace std;




bool matrix_c_s[40000][2500];

int main_1039(int argc, const char * argv[]) {
	int amount_stu;
	int amount_course;
	cin >> amount_stu >> amount_course;
	int student_count = 0;
	map<string, int> students_map;
	for (int i = 0; i < amount_course; i++)
	{
		int num_course;
		int num_stu;
		map <string, bool > students;

		cin >> num_course >> num_stu;
		for (int j = 0; j < num_stu; j++)
		{
			string name_stu;
			cin >> name_stu;
			if (students_map.find(name_stu) == students_map.end())
			{
				int student_num = student_count;
				student_count++;
				matrix_c_s[student_num][num_course] = true;
				students_map[name_stu] = student_num;
//				free(&student_num);
			}
			else
			{
				int student_num = students_map[name_stu];
				matrix_c_s[student_num][num_course] = true ;
				
				students_map[name_stu] = student_num;
			}
		}
	}
	vector<string> names_stu;
	for (int i = 0; i < amount_stu; i++)
	{
		string name_stu;
		cin >> name_stu;

		names_stu.push_back(name_stu);
		//free(&name_stu);
		
	}
	for (int i = 0; i < amount_stu; i++)
	{
		if (students_map.find(names_stu[i]) == students_map.end())
		{
			cout << names_stu[i] << ' ' << 0<<endl;
		}
		else
		{
			stringstream ss;
			int student_num= students_map[names_stu[i]];
			int count = 0;
			for (int i = 0; i < 2500; i++)
			{
				if (matrix_c_s[student_num][i])
				{
					ss << ' ' << i;
					count++;
				}
			}
			cout << names_stu[i] << ' ' << count << ss.str();
			
			cout << endl;

		}


	}



	//cin >> amount_stu;
	return 0;
}

