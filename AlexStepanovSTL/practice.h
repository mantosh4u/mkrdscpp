#include<iostream>
#include<string>
#include"Vector.h"
#include"stack.h"
#include<string>


//Forward Declration Of The Method From 
unsigned long __long_random(unsigned long limit);




namespace utility {

	template<typename T>
	inline void display(const T& val) {
		std::cout<<val<<std::endl;
	}


	template<typename T>
	inline void basicdisplaywithtab(const T& val) {
		std::cout<<val<<",\t";
	}


	template<typename C>
	void displaycontainer(const C& cont) {
		for(const auto& it:cont) {
			utility::basicdisplaywithtab(it);
		}
		utility::display("\n");
	}

	
	template<typename T>
	inline T random(T limit) {
		unsigned long limit_val = static_cast<unsigned long>(limit);
		unsigned long output = __long_random(limit_val);
		return(static_cast<T>(output));
	}
}





void vector_uses(void) {
	vector<int> alexvec;
	int maxlimit = 1000;
	for(auto sz = 0; sz < 10; sz++)
		alexvec.push_back(utility::random(maxlimit));

	utility::displaycontainer(alexvec);
}






void stack_uses(void) {
	stack<vector<int>> alexstack;
	int maxlimit = 100;
	int tmp = 0;
	for(auto sz = 0; sz < 10; sz++) {
		tmp = utility::random(maxlimit);
		alexstack.push(tmp);
	}
	//display the members as the 
	utility::display("Top of The Stack");
	while(!alexstack.empty()) {
		utility::basicdisplaywithtab(alexstack.top());
		utility::display(alexstack.size());
		alexstack.pop();
	}

	stack<vector<int>> alexstack2;
	int maxlimit2 = 1000;
	int tmp2 = 0;
	for(auto sz = 0; sz < 10; sz++) {
		tmp2 = utility::random(maxlimit2);
		alexstack2.push(tmp2);
	}

	if(alexstack.size() == alexstack2.size()){
		utility::display("Is Equal");
	} else {
		utility::display("Not Equal");
	}

}


void priority_queue_uses_basic(void) {
	priority_queue<vector<int>,less<int>> alexpqueue;
	int maxlimit = 100;
	int tmp = 0;
	for(auto sz = 0; sz < 10; sz++) {
		tmp = utility::random(maxlimit);
		utility::display(tmp);
		alexpqueue.push(tmp);
	}
	//display the members as the 
	utility::display("Top of The Priority Queue");
	while(!alexpqueue.empty()) {
		utility::basicdisplaywithtab(alexpqueue.top());
		utility::display(alexpqueue.size());
		alexpqueue.pop();
	}

}




struct person {
	std::string name;
	std::size_t age;
	std::string information;
	person(std::string nm, std::size_t ag, std::string info):
	name(nm), age(ag), information(info) {}
	~person() {}
};

template<typename T>
struct lessage {
	inline bool operator()(const T& a, const T& b) { 
		return a.age < b.age; 
	}
};


void priority_queue_uses_advance(void) {
	priority_queue<vector<person>,lessage<person>> alexpqueue;
	alexpqueue.push(person("Mantosh",28,"Bokaro"));
	alexpqueue.push(person("Aniket",36, "Mumbai"));
	alexpqueue.push(person("Chetan",35,"Belapur"));
	alexpqueue.push(person("Abhay",30,"Goregaon"));
	while(!alexpqueue.empty()) {
		person tmp = alexpqueue.top();
		utility::basicdisplaywithtab(tmp.name);
		utility::basicdisplaywithtab(tmp.age);
		utility::display(tmp.information);
		alexpqueue.pop();
	}
}

