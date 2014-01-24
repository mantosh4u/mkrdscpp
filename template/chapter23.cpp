#include<iostream>
#include<string>


namespace variadictemplate {

	// Display Any arbitary type
	template<typename T>
	void display(T& val) {
		std::cout<<val<<std::endl;
	}

	template<typename T>
	struct X {
		using value_type = T;
		int m1;
		T m2;
		X(const T& x): m1(10),m2(x) { }
		int& mf1(void) { return m1; }
		T& mf2();
	};

	template<typename T>
	T& X<T>::mf2() { return m2; }

	

	void learn_templates(void) {
		X<int> ox1(10);
		int tmp(20);
		X<int> ox2(tmp);

		display(ox1.mf1());
		display(ox1.mf2());

		display(ox2.mf1());
		display(ox2.mf2());

		X<int> ox3(40);
		X<int>::value_type val = ox3.mf2();
		display(val);


	}

}



int main(){
	variadictemplate::learn_templates();
}

