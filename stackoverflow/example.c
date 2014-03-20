
#include<stdlib.h>

typedef struct base {
	int x;
	int y;
}base;
typedef struct derived {
	int a;
	base* bb;
}derived;


int main() {
	//allocating the 1st memory
	derived* dd= (derived*)malloc(sizeof(derived));
	//derived =(derived*)calloc(1,sizeof(derived));
	dd->a = 100;
	
	// Suppose your logic of allocating the 2nd memory is based on some logic, 
	// Here checking with 10 which is obiously not true hence it would not 
	// allocate. This means derived->bb can have some unintialized/garbaze value.

	if(dd->a == 10) {
		//allocate the 2nd memory
		dd->bb = (base*)malloc(sizeof(base));
		// derived->bb =(base*)calloc(1,sizeof(base));
	}

	//While freeing the memory just check whether the addresses are NULL or not.
	// The 2nd free call is valid but the 1st call is not valid in this case. Due to unintialized
	// values in derived->bb, it would pss NULL check and would try to free the memory
	// (treating 4 byte garbaze as address )which is never allocated.
	
	//Now if we use calloc(), while allocating the 1st memory, then it would put 0 everywhere
	// and due to that even though 2nd allocation does not happen,  free() call would not
	// be called as derived->bb would be NULL instead of grabaze.
	if(dd->bb) {	
		free(dd->bb);
	}
	if(dd) {
		free(dd);	
	}

	return 0;
}




/* If we run this program using the valgrind, it gives the follwing warning
mantosh@mantosh4u:~/practice$ valgrind ./out
==3154== Memcheck, a memory error detector
==3154== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==3154== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==3154== Command: ./out
==3154== 
==3154== Conditional jump or move depends on uninitialised value(s)
==3154==    at 0x4005AB: main (bakwas.c:37)
==3154== 
==3154== 
==3154== HEAP SUMMARY:
==3154==     in use at exit: 0 bytes in 0 blocks
==3154==   total heap usage: 1 allocs, 1 frees, 16 bytes allocated
==3154== 
==3154== All heap blocks were freed -- no leaks are possible
==3154== 
==3154== For counts of detected and suppressed errors, rerun with: -v
==3154== Use --track-origins=yes to see where uninitialised values come from
==3154== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)
*/









