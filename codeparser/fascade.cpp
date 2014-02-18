class codeparser
{
public:
	codeparser(int argc, char** argv);
	~codeparser();
	void start_execution(void);
	long long total_valid_line() const { return total_lines;}
private:
	long long total_lines;
	std::vector<fspath> files;
};



codeparser::codeparser(int argc, char** argv) {
	maindirectory	dirobject;
	dirobject.start_application(argc, argv);
	scaninputdirectory inputdir;
	inputdir.scan_the_inputdirectory(dirobject);
	files = std::move(inputdir.get_files_list());

	total_lines = 0;
}


codeparser::~codeparser() {

}



void codeparser::start_execution(void) {
	for(auto& itr:files) {
		fileinformation file(itr);
		long output = file.number_of_validlines();
		total_lines = total_lines + output;
	}
}

