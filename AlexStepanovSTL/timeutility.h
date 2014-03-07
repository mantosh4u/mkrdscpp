#include<thread>
#include<chrono>
using namespace std::chrono;



template<typename Tprecision = milliseconds>
class timemeasure
{
private:
	steady_clock::time_point tbegin;
	steady_clock::time_point tend;
	steady_clock::duration diff;
public:
	typedef steady_clock::duration::rep unit;
	timemeasure() {}
	~timemeasure() {}
	void start_point(void){
			tbegin = steady_clock::now();
	}
	unit end_point() {
			tend = steady_clock::now();
			diff = tend - tbegin;
			Tprecision  dur{};
			dur = duration_cast<Tprecision>(diff);
			unit  val = dur.count();
			return val;
	}	
};
