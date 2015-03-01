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


#ifndef COMMONHEADERR_H
#define COMMONHEADERR_H

#include<iostream>
#include<thread>
#include<chrono>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<random>

using namespace std::chrono;

template<typename T>
inline void display(const T& val) {
	std::cout << val << std::endl;
}

template<typename T>
inline void displaytab(const T& val) {
	std::cout << val <<"\t";
}

template<typename Container>
void display_container(const Container& c){
	for (const auto& iter : c){ 
		displaytab(iter); 
	}
	display("\n");
}


template<typename Tprecision = milliseconds>
class timemeasure
{
private:
	steady_clock::time_point   tbegin{};
	steady_clock::time_point   tend{};
	steady_clock::duration      diff{};
public:
	using unit = steady_clock::duration::rep;
	timemeasure()  = default;
	~timemeasure() = default;
	void start_point(){
		tbegin = steady_clock::now();
	}
	unit end_point() {
		tend = steady_clock::now();
		diff = tend - tbegin;
		Tprecision  dur{};
		dur = duration_cast<Tprecision>(diff);
		unit  val = dur.count();
		return val;
	}
};

using tmeasureapp = timemeasure<microseconds>;

std::vector<int> random_generated_collections(int size) {
	std::default_random_engine drge;
	std::uniform_int_distribution<int>	distributionapp(0,size);
	std::vector<int> out;

	for (size_t index = 0; index < size; ++index){
		out.push_back(distributionapp(drge));
	}
	return out;
}

#endif
