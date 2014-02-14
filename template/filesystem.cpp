#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>


typedef  boost::filesystem::path  fspath;
typedef boost::filesystem::recursive_directory_iterator rdir_iterator;


class maindirectory {
public:
	 maindirectory() = default;
	~maindirectory() = default;
	 maindirectory(const maindirectory& obj) = delete;
	 maindirectory& operator= (const maindirectory& obj) = delete;
	 maindirectory(maindirectory&& obj) = delete;
	 maindirectory& operator=(maindirectory&& obj) = delete;

	void     start_application(int	argc, char** argv);
	inline   fspath	 current_working_direct() const { return dirpath; }
	
private:
	fspath   dirpath;
	bool	 valid_directory{false};		
};


void	 maindirectory::start_application(int	argc, char** argv)  {
		if( argc !=2) {
			fspath tmpath = boost::filesystem::current_path();
			dirpath = tmpath.c_str();		
		} else {
			dirpath = argv[1];
		}
		
		//Check whether user input is valid directory.
		valid_directory = boost::filesystem::is_directory(dirpath);					
}







class scaninputdirectory{
public:
	scaninputdirectory() = default;
	~scaninputdirectory() = default;
	void scan_the_inputdirectory(maindirectory& input);
	void	display_all_entry_with_complete_path();
	std::vector<fspath> get_files_list(void) { return input_files; }
	
private:
	void	recursive_directory_information();
	bool  validate_each_node(fspath node);	
	std::vector<fspath> 	input_files;
	fspath	cur_dir;
};



void scaninputdirectory::scan_the_inputdirectory(maindirectory& input) {
	
		cur_dir = input.current_working_direct();
		// do some sanity check before doing final processing
		bool output = cur_dir.empty();
		if(output == true) 
			return;

		recursive_directory_information();	
		display_all_entry_with_complete_path();
}


bool scaninputdirectory::validate_each_node(fspath node) {

	std::string name = node.extension().native();
	const size_t arrsize = 5;
	std::array<std::string, arrsize> arrextension = {".h",".c",".cpp",".hpp",".cxx"};
	std::string::size_type sz = 0;
	bool output;

	for(const auto& itr: arrextension) {
		sz = input.find(itr);
		output = (sz != std::string::npos)&&(input.size() == itr.size());
		if(output == true) break;
	}
	return output;
}



void	scaninputdirectory::recursive_directory_information(void) {
      rdir_iterator rbgnitr(cur_dir);
		rdir_iterator renditr;
	
		for(rdir_iterator	itr = rbgnitr; itr != renditr; ++itr) {
			if(validate_each_node(*itr)) {
				input_files.push_back(*itr);
			}
		}
		
}



void scaninputdirectory::display_all_entry_with_complete_path(void) {
	for(const auto& itr:input_files) {
          std::cout <<itr<<std::endl;
      }
      
   std::cout<<"Number Of Valid Files Are: "<<input_files.size()<<std::endl;   
}




int main(int argc, char* argv[] ) {
	maindirectory	dirobject;
	dirobject.start_application(argc, argv);
	scaninputdirectory inputdir;
	inputdir.scan_the_inputdirectory(dirobject);

}



