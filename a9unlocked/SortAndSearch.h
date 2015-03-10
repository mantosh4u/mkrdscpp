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

#ifndef SORTANDSEARCH_H
#define SORTANDSEARCH_H


/***** Chapter: 3 *****/
#include"CommonHeader.h"


namespace ch03a9unlocked
{
	/******************************* Binary Search ****************************/
	int binary_search(int* arr, size_t size, const int& value)
	{
		int p = 0;
		int r = size;
		int answer = -1;

		while (p <= r) {
			answer = (p + r) / 2;

			if (arr[answer] == value)
				break;
			else if (arr[answer] > value)
				r = answer - 1;
			else
				p = answer + 1;
		}
		return answer;
	}

	void display_result(int out) {
		if (out == -1)
			display("Value Did Not Find");
		else
			display("Value Found on Index: " + std::to_string(out));
	}

	void client_api_binary_search(const int& input) {
		std::vector<int> ivec = random_generated_collections(input);
		display_container(ivec);

		display("Value To Be Found:" + std::to_string(input));
		tmeasureapp timer;
		timer.start_point();
		int out = binary_search(ivec.data(), ivec.size(), input);
		auto totaltime = timer.end_point();

		display_result(out);
		display("TimeTaken(nanoseconds) by the binary_search: ");
		display(totaltime);

	}

	/******************************* Selection Sort ****************************/
	int find_minimum(int* arr, size_t size)
	{
		int smallest = 0;
		size_t index = 0;
		while (size) {
			if (arr[index] < arr[smallest]) {
				smallest = index;
			}
			--size;
			++index;
		}
		return smallest;
	}

	void selection_sort(int* arr, size_t size)
	{
		if (size == 0){
			return;
		}
		for (size_t i = 0; i < size - 1; i++){
			int smallest = find_minimum((arr + i), (size - i));
			if (arr[smallest + i] < arr[i]) {
				std::swap(arr[smallest + i], arr[i]);
			}
		}
		return;
	}

	void client_api_selection_sort(const int& input)
	{
		std::vector<int> ivec = random_generated_collections(input);
		display_container(ivec);
		selection_sort(ivec.data(), ivec.size());
		display_container(ivec);
	}



	/******************************* Insertion Sort ****************************/
	void insertion_sort(int* arr, size_t size)
	{
		if (size == 0){
			return;
		}
		
		for (size_t i = 1; i < size; i++){
	
			//initialization
			int key = arr[i];
			int j = i - 1;

			// movement of other at appropriate place based on key
			while ((j >= 0) && (arr[j] > key)){
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			// insert the key value to its position
			arr[j+1] = key;
		}
		return;
	}

	void client_api_insertion_sort(const int& input) {
		std::vector<int> ivec = random_generated_collections(input);
		std::sort(ivec.begin(), ivec.end());
		std::reverse(ivec.begin(), ivec.end());
		display_container(ivec);
		insertion_sort(ivec.data(), ivec.size());
		display_container(ivec);
	}


	
	/******************************* Merge Sort ****************************/





}







#endif
