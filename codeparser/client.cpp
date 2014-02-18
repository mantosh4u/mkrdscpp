


int main(int agrc,char* argv[])
{
	codeparser parser(argc, argv);
	parser.start_execution();

	long long totallines = parser.total_valid_line();
	std::cout<<"Total Lines: "<<totallines<<std::endl;
}

