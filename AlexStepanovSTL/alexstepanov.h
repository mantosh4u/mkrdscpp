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



template<typename T>
class mydeque {
private:
	list<vector<T>> deque;
public:
	mydeque() {
		/*front vector and back vector to grow in two direction(1+1)*/
		for (size_t i = 0; i < 2; i++) {
			vector<T> tmp;
			deque.push_back(tmp);
		}
	}
	~mydeque() { }
	void push_front(const typename vector<T>::value_type& node) {
		list<vector<T>>::iterator it = deque.begin();
		list<vector<T>>::value_type& frontvec = *it;
		frontvec.push_back(node);
	}
	void push_back(const typename vector<T>::value_type& node) {
		list<vector<T>>::iterator it = deque.begin();
		++it;
		list<vector<T>>::value_type& backvec = *it;
		backvec.push_back(node);
	}
	typename vector<T>::size_type size() const {
		vector<T>::size_type sz = 0;
		for(const auto& it:deque){
			sz += (it).size();
		}
		return sz;
	}
	typename vector<T>::size_type max_size() const {
		vector<T>::size_type sz = 0;
		for(const auto& it:deque){
			sz += (it).max_size();
		}
		return sz;
	}
	bool empty() const {
		return(size()== 0);
	}
	typename vector<T>::reference operator[](size_t n) {
		list<vector<T>>::iterator it = deque.begin();
		list<vector<T>>::value_type& frontvec = *it;
		++it;
		list<vector<T>>::value_type& backvec = *it;
		size_t frontsize = frontvec.size();
		size_t bacsize = backvec.size();

		if(n >= frontsize) {
			/*member stored into the backvector*/
			size_t index = n - frontsize;
			return backvec[index];
		}else {
			/*member stored into the frontvector*/
			size_t index = bacsize - n;
			return frontvec[index];
		}
	}
	typename vector<T>::reference front(){
		list<vector<T>>::iterator it = deque.begin();
		list<vector<T>>::value_type& frontvec = *it;
		size_t vecsize = frontvec.size();
		return frontvec[vecsize -1];
	}
	typename vector<T>::reference back(){
	    list<vector<T>>::iterator it = deque.begin();
		++it;
		list<vector<T>>::value_type& backvec = *it;
		size_t vecsize = backvec.size();
		return backvec[vecsize -1];
	}

	void pop_front(){
		list<vector<T>>::iterator it = deque.begin();
		list<vector<T>>::value_type& frontvec = *it;
		frontvec.pop_back();
	}
	void pop_back(){
		list<vector<T>>::iterator it = deque.begin();
		++it;
		list<vector<T>>::value_type& backvec = *it;
		backvec.pop_back();
	}
	/*debugging purpose*/
	void displayall() {
		list<vector<T>>::iterator it = deque.begin();
		list<vector<T>>::value_type& frontvec = *it;
		size_t vecsize = frontvec.size();
		for(size_t index = vecsize; index !=0; index--){
			utility::basicdisplaywithtab(frontvec[index-1]);
		}
		++it;
		list<vector<T>>::value_type& backvec = *it;
		utility::displaycontainer(backvec);
	}
};




void mydeque_uses(void) {
	mydeque<int> testdeque;
	testdeque.push_front(1);
	testdeque.push_front(2);
	testdeque.push_front(5);
	testdeque.push_back(3);
	testdeque.push_back(4);
	utility::display(testdeque.size());
	utility::display(testdeque.max_size());
	utility::display(testdeque.empty());
	utility::display(testdeque[4]);
	testdeque.displayall();
	utility::display(testdeque.front());
	utility::display(testdeque.back());
	std::cout<<std::endl<<std::endl;
	for(size_t i = 0; i < testdeque.size(); i++) {
		utility::basicdisplaywithtab(testdeque[i]);
	}
	testdeque.pop_front();
	testdeque.displayall();
	testdeque.pop_back();
	testdeque.displayall();
	utility::display("\n");
}


