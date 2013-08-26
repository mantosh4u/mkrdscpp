#ifndef  STACK_H
#define  STACK_H

namespace mdatastruct {

	class stack
	{
	public:
		stack();
		~stack();
		inline bool    empty(void);
		inline size_t  size(void);
		inline void    push(int);
		inline int     pop(void);
	private:
		enum	{ASIZE = 100};
		size_t  top;
		int     S[ASIZE];
	};
};

#endif
