#include<iostream>

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



