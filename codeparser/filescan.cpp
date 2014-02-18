#include"stdafx.h"
#include<string>
#include<iostream>
#include<fstream>
#include<regex>
#include<array>
#include<utility>


const int count = 4;
std::array<std::pair<std::regex, bool>, count> regularexpression 
	= {std::make_pair(std::regex("^\\s*$"),false),					
	   std::make_pair(std::regex("^\\s*//"),false),					
	   std::make_pair(std::regex("([\\s{0,}]?[/][*])"),false),		
	   std::make_pair(std::regex("([\\s{0,}]?[*][/][\\s{0,}]?[\\W{0,}]?$)"),false) 
	  };



class fileinformation
{
public:
	fileinformation(std::string& input);
	long number_of_validlines();
private:
	bool validate_lines_information(std::string& line);
	std::ifstream  filehandle;
	long	nlines;
};


fileinformation::fileinformation(std::string& input) {
	filehandle.open(input);  	
	if (!filehandle) {
		std::cerr << "Unable To Open The File:"<<input<<std::endl;
	}
	nlines = 0;
}



bool fileinformation::validate_lines_information(std::string& line) {
	std::smatch  matches; 
	bool output = false;
	std::size_t index;
	static bool recursivecomment = false;

	for(index = 0; index < regularexpression.size(); ++index) {
		regularexpression[index].second = std::regex_search(line, matches, regularexpression[index].first);
		/*
		{
				output = true;
				if(index != 2){
					break;
				}
		}
		*/
	}

	recursivecomment = (regularexpression.at(2).second) && !(regularexpression.at(3).second);


	for(index = 0; index < regularexpression.size(); ++index) {
		regularexpression[index].second = false;
	}



	return output;
}



long fileinformation::number_of_validlines() {
	std::string line;
	while (std::getline(filehandle,line)) {
	 	if (!validate_lines_information(line)){
			nlines++;
		}
	}
	return nlines;
}
