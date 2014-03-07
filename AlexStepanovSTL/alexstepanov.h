#include<string>
#include"vector.h"
#include"list.h"
#include"stack.h"
#include"deque.h"

#include"myutility.h"
#include"timeutility.h"





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





void deque_uses(void) {
	deque<int> alexdeque;
	alexdeque.push_front(1);
	alexdeque.push_front(2);
	alexdeque.push_back(3);
	alexdeque.push_back(4);
	
	utility::displaycontainer(alexdeque);
}



class mydeque
{
private:
	size_t numberofslab;
	size_t sizeofeachslab;
	list<vector<int>> deque;

public:

	mydeque(size_t x, size_t y){
		numberofslab = x;
		sizeofeachslab = y;
		for(size_t i = 0; i <numberofslab; i++) {
			vector<int> tmp;
			deque.push_back(tmp);
		}
	}

	~mydeque() {}

	void push_front(const int& node) {
		list<vector<int>>::size_type sz = deque.size();
		list<vector<int>>::iterator it = deque.begin();
		for(list<vector<int>>::size_type i = 0; i < sz; i++){
			++it;
		}

		list<vector<int>>::value_type& frontvec = *it;
		
		if(frontvec.size()< sizeofeachslab) {
			frontvec.push_back(node);
		}
		/*utility::displaycontainer(frontvec);*/
	}


	void push_back(const int& node){
		list<vector<int>>::iterator it = deque.begin();
		list<vector<int>>::value_type& backvec = *it;
		if(backvec.size()< sizeofeachslab) {
			backvec.push_back(node);
		}
		/*utility::displaycontainer(backvec);*/
	}


	void displayall() {
		for(list<vector<int>>::iterator it = deque.begin();it != deque.end();++it) {
			list<vector<int>>::value_type& tmp = *it;
			utility::displaycontainer(tmp);
		}
	}

};


void mydeque_uses(void) {
	mydeque testdeque(2,10);
	testdeque.push_front(1);
	testdeque.push_front(2);
	testdeque.push_back(3);
	testdeque.push_back(4);
	testdeque.displayall();
}

