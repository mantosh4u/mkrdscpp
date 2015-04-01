#include<iostream>
#include<vector>
#include<array>
#include<algorithm>

std::vector<int> my_merge(int* first, int fsize, int* second, int ssize)
{
    int sz = std::min(fsize, ssize);
    int firstpos  = 0;
    int secondpos = 0;
    std::vector<int> output;
	
	 // The common elements logic	
    for (int index = 0; index <= sz; index++)
    {
        if (first[firstpos] < second[secondpos]){
            output.push_back(first[firstpos]);
            firstpos++;
        }
        else{
            output.push_back(second[secondpos]);
            secondpos++;
        }
    }
	
    if (first[firstpos] < second[secondpos]){
        output.push_back(first[firstpos]);
        firstpos++;
    }


    int remaining = std::min(firstpos, secondpos);
    int maxsize = 0;
	 int* remain = nullptr;
	
	  if(fsize < ssize) {
			maxsize = ssize;
			remain  = second;
		}else {
			maxsize = fsize;
			remain  = first;
		}
	
    for (int index = remaining; index < maxsize; index++){
       output.push_back(remain[index]);
    }

    return output;
}


int main()
{
    std::array<int, 5> ax = {3,7,9,12,14 };
    std::array<int, 5> ay = {2, 5, 6, 10,11};
    auto output = my_merge(ax.data(), ax.size(), ay.data(), ay.size());
    for (const auto& index : output) {
        std::cout << index << "\t";
    }
    std::cout << std::endl;

    return 0;
}
