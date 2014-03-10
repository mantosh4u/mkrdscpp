struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};


template<typename Iterator>
size_t distance(Iterator* first,Iterator* last,input_iterator_tag){
	size_t diff = last - first;
	return diff;
}

template<typename Iterator>
size_t distance(Iterator* first,Iterator* last,forward_iterator_tag){
	size_t n = 0;
	while (first != last) { ++first; ++n; }
	return n;
}


void iterator_understanding(void) {
	size_t ncount = 10;
	int* start = new int[ncount];
	int* end = start + ncount;
	size_t out = distance(start, end,input_iterator_tag());


	float* start2 = new float[ncount];
	float* end2 = start2 + ncount;
	size_t out2 = distance(start2, end2,forward_iterator_tag());

}
