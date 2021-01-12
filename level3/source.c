# include <stdio.h> // fgets, printf, fwrite
# include <stdlib.h> // system

int global; // 0x804998c

void v()
{
	char buff[512]; // size of buff is 0x200 == 512 (assuming the code is not shit and sizeof is used) --> see instruction 0x080484b6

	fgets(buff, sizeof(buff), stdin); // stdin loaded from libc (0x8049860)
	printf(buff);
	if (global == 0x40) // 64
	{
		static const char what[] = "Wait what?!\n"; // 0x8048600
		static const char binsh[] = "/bin/sh"; // 0x804860d

		fwrite(what, 0x1ul, sizeof(what) - 0x1ul, stdout);  // stdout loaded from libc (0X8049880)
		system(binsh);
	}
}

int main(int ac, char** argv)
{
	(void)ac, (void)argv;
	v();
}