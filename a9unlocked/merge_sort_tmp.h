#include<iostream>
#include<vector>
#include<array>

template<typename Container>
void display_container(const Container& c) {
	for(const auto& index:c){
		std::cout<<index<<"\t";	
	}
	std::cout<<std::endl;
}

void merge(int* arr, int start, int middle, int end)
{
	size_t lsize = (middle-start)+1;
	std::vector<int> lmembers;
	lmembers.reserve(lsize);
	for(size_t index=0;index<lsize;index++){
		lmembers.push_back(arr[index]);
	}
	std::cout<<"Left Side Members"<<std::endl;
	display_container(lmembers);

	size_t risze = end-middle;
	std::vector<int> rmembers;	
	rmembers.reserve(risze);
	for(size_t index=lsize;index<risze;index++){
		rmembers.push_back(arr[index]);
	}		
	std::cout<<"Right Side Members"<<std::endl;
	display_container(rmembers);
}



void merge_sort(int* arr, int start, int end)
{
	//base case
	if(start >= end-1) {
		return;
	}
	//recursion
	int middle = (start + end)/2;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle+1, end);
	merge(arr,start,middle,end);
}




int main()
{
	//std::vector<int> ivec {12,9,3,7,14,11,6,2,10,5};
	std::vector<int> ivec {38,27,43,3,9,82,10};
	merge_sort(ivec.data(),0,ivec.size());
	return 0;
}


