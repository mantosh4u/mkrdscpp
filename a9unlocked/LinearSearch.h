/*
* C++ Implementation of Algorithms From "Algorithm Unlocked By Thomas H. Cormen"
* Copyright (C) 2015  Mantosh Kumar(mantosh4u@gmail.com).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H


/****** Chapter: 2 *****/
#include"CommonHeader.h"

namespace ch02a9unlocked
{
	/******************************* Linear Search ****************************/
	template<typename Predicate>
	int linear_search(int* arr, size_t size, const int& value, Predicate pred)
	{
		int answer = -1;
		size_t index = 0;
		while (size) {
			if (pred(arr[index], value)) {
				answer = index;
			}
			--size;
			++index;
		}
		return answer;
	}

	template<typename Predicate>
	int better_linear_search(int* arr, size_t size, const int& value, Predicate pred)
	{
		int answer = -1;
		size_t index = 0;
		while (size) {
			if (pred(arr[index], value)) {
				answer = index;
				break;
			}
			--size;
			++index;
		}
		return answer;
	}

	template<typename Predicate>
	int sentinel_linear_search(int* arr, size_t size, const int& value, Predicate pred)
	{
		int answer = -1;
		size_t index = 0;

		//save the orginal value and insert the to be found value in sentinel
		int last = arr[size];
		arr[size] = value;

		while (!pred(arr[index], value)) {
			++index;
		}

		//Restore to the original value in the array
		arr[size] = last;

		if ((index < size) || (pred(arr[size], value))){
			answer = index;
		}

		return answer;
	}

	void display_result(int out) {
		if (out == -1)
			display("Value Did Not Find");
		else
			display("Value Found on Index: " + std::to_string(out));
	}


	void client_api_linear_search(const int& input) {
		std::vector<int> ivec = random_generated_collections(input);
		/* display_container(ivec); */
		display("Value To Be Found:" + std::to_string(input));
		int fnumber = input;
		{
			tmeasureapp timer;
			timer.start_point();
			int out = linear_search(ivec.data(), ivec.size(), fnumber, std::equal_to<int>());
			auto totaltime = timer.end_point();

			display_result(out);
			display("TimeTaken(microsecond) by the linear_search: ");
			display(totaltime);
		}
	
		{
			tmeasureapp timer;
			timer.start_point();
			int out = better_linear_search(ivec.data(), ivec.size(), fnumber, std::equal_to<int>());
			auto totaltime = timer.end_point();

			display_result(out);
			display("TimeTaken(microsecond) by the better_linear_search: ");
			display(totaltime);
		}

		{
			tmeasureapp timer;
			timer.start_point();
			int out = sentinel_linear_search(ivec.data(), ivec.size(), fnumber, std::equal_to<int>());
			auto totaltime = timer.end_point();

			display_result(out);
			display("TimeTaken(microsecond) by the sentinel_linear_search: ");
			display(totaltime);
		}
	}
}

#endif
