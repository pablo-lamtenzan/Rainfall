
# include <cstring> // strlen, memcpy
# include <unistd.h> // _exit

class N
{
	int	 value;				// {ebp + 0x8} instruction 0x080486f9
	char annotation[100];	// {ebp + 0x12} instructions 0x0804871f, 0x08048722

	public:

	N(int n) : value(n) { } // 0x080486f6

	virtual int operator+(N& other) { return (value + other.value); } // 0x0804873a
	virtual int operator-(N& other) { return (value - other.value); } // 0x0804874e

	// Why virtual ? Virtual function in c++ can be overwritten by derivated classes,
	//		for make it work in that way the compiler store all the possible definitions
	//		in a list of function pointers, after that, during the running time the
	//		required function pointer is asigned dynamically before to be used.
	// We can observe at instruction 0x08048693 that edx is called. That means a call to an address stored
	//		in a value, so a function pointer.
	// I know that oprator + is called at the end and is called like a function pointer, so the only possible
	//		explenation is the operator + is declarated as virtual.
	// I have no idea if the operator - is virtual or not because is never called.

	void setAnnotation(char* i) { memcpy(annotation, i, strlen(i)); } // 0x0804870e
};

int main(int ac, char** argv)
{
	if (ac < 2)
		_exit(0x1);

	N *x1; // {esp + 0x1c}
	N *y1; // {esp + 0x18}

	x1 = new N(0x5); // new is _Znwj@plt (0x8048530), sizeof(N) == 0x6c (0x08048610), N::N(int) is _ZN1NC2Ei (0x80486f6)
	y1 = new N(0x6); // new is _Znwj@plt (0x8048530), sizeof(N) == 0x6c (0x08048632), N::N(int) is _ZN1NC2Ei (0x80486f6)

	N &x2 = *x1; // x2 == {esp + 14}, instruction 0x08048658
	N &y2 = *y1; // y2 == {esp + 10}, instruction 0x08048660

	x2.setAnnotation(argv[1]); // I'VE BACKTRACKED "setAnnotation" is part of x2 (i don't really know how know that with the asm, have to do my research about it)

	return (y2 + x2); // {esp + 14} and {esp + 10} are set as arguments before the call, 
						// I'VE BACKYTACKED that too ...
}