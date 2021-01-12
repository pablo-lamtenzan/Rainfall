
# include <stdio.h> // fgets, printf
# include <stdlib.h> // exit

void o() // 0x80484a4
{
	static const char binsh[] = "/bin/sh"; // 0x80485f0
	system(binsh);
	_exit(0x1);
}

void n()
{
	// buffer could be bigger ... stack frame is 0x218
	char buff[512]; // {ebp - 0x208}

	fgets(buff, sizeof(buff), stdin); // stdin 0x8049848
	printf(buff);
	exit(0x1); // GOT addr is 0x8049838
}

int main(int ac, char** argv)
{
	(void)ac, (void)argv;

	n();
}