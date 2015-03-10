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

#include"LinearSearch.h"
#include"SortAndSearch.h"


int main(int argc, const char* argv[]) {

	int input = 0;
	if (argc >= 2)
		input = std::atoi(argv[1]);
	else
		input = 6;

	// ch02a9unlocked::client_api_linear_search(input);
	// ch03a9unlocked::client_api_binary_search(input);
	// ch03a9unlocked::client_api_selection_sort(input);
	// ch03a9unlocked::client_api_insertion_sort(input);


	//int count = 0;
	//while (1)
	//{
	//	ch03a9unlocked::client_api_insertion_sort(input);
	//	MySleep(10);
	//	count++;
	//	if (count == 10){
	//		count = 0;
	//	}
	//}

	return 0;
}
