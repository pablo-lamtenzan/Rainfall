
# define _GNU_SOURCE // man strdup - > man 7 feature_test_macros

# include <stdio.h> // fflush, gets, printf
# include <string.h> // strdup
# include <unistd.h> // exit

void p()
{
	static const char format[] = "(%p)\n"; // 0x8048620 (not in the stack)
	size_t eip;	// located at {ebp - 0xc}
	char buff[64]; 	// {ebp - 0x4c} address is loaded as argument of gets
					// 0x4c = 76
					// After gets call, the eip (ebp + 0x4) is move into {ebp - 0xc}
					// That means there's other local var after the buff
					// So the buff size is 0x4c - 0xc = 0x40 = 64

	fflush(stdout); // stdout loaded from libc at address 0x8049860
	gets(buff);
	eip = (size_t)__builtin_return_address(0); // return {ebp + 4}, the argument indicates the target frame
	if ((eip & 0xb00000000ul) == 0xb00000000ul)
	{
		printf(format, eip); // takes as argument 0x8048620 and {ebp - 0xc}
		exit(0x1);
	}
	printf(buff); // Compiler optimize the code with puts when there's no string format in printf.
	strdup(buff);
}

int main(int ac, char** argv)
{
	(void)ac;
	p();
}