#include<string>
#include<iostream>
#include<fstream>
#include<boost/regex.hpp>

/* hello world */
void learn_regex_uses1(void) {
	std::ifstream in("/home/mantosh/practice/boost/filesystem/test.cpp");  	//input file
	if (!in) std::cerr << "no file"<<std::endl;
	
	boost::regex pat("^\\s*$");
	std::cout<<"pattern : " <<pat<<std::endl;    // ZIP code pattern
	int lineno = 0;
	std::string line;   //input buffer

	while (std::getline(in,line)) {
		++lineno;
		boost::smatch  matches;     //matched strings go here
		if (boost::regex_search(line, matches, pat))
			std::cout<<lineno<< ": " <<matches[0]<<std::endl;
	}
}


void learn_regex_uses2(void) {
	std::ifstream in("/home/mantosh/practice/boost/filesystem/test.cpp");  	//input file
	if (!in) std::cerr << "no file"<<std::endl;
	
	boost::regex pat("^\\s*//");
	std::cout<<"pattern : " <<pat<<std::endl;    // ZIP code pattern
	int lineno = 0;
	std::string line;   //input buffer

	while (std::getline(in,line)) {
		++lineno;
		boost::smatch  matches;     //matched strings go here
		if (boost::regex_search(line, matches, pat))
			std::cout<<lineno<< ": " <<matches[0]<<std::endl;
	}
}



void learn_regex_uses3(void) {
	std::ifstream in("/home/mantosh/practice/boost/filesystem/test.cpp");  	//input file
	if (!in) std::cerr << "no file"<<std::endl;
	
	// boost::regex pat("([_[:alnum:]]*)([*/])");
	// boost::regex pat("([*/])([[:space:]]*$)");
	// boost::regex pat("([/*]{1}\\s*$)");
	// boost::regex pat("(\\s*[/*])(\\w*)([*/])");
	boost::regex pat("([\\s{0,}]?[/][*])|([\\s{0,}]?[*][/][\\s{0,}]?$)");
	
	std::cout<<"pattern : " <<pat<<std::endl;    // ZIP code pattern
	int lineno = 0;
	std::string line;   //input buffer

	while (std::getline(in,line)) {
		++lineno;
		boost::smatch  matches;     //matched strings go here
		if (boost::regex_search(line, matches, pat)) {
			for(size_t  index = 0; index < matches.size(); ++index) {
			std::cout<<lineno<< ": " <<matches[index]<<"\t"<<matches[index].matched<<std::endl;
		  }
		  
	 }
}
   
 }  



int main() {
	// learn_regex_uses1();
	// learn_regex_uses2();
	learn_regex_uses3();
}

																			
//         

//aaaaaaaaaaaaaaa




