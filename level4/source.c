# include <stdio.h> // fgets
# include <stdlib.h> // system

int global; // 0x8049810

volatile void p(char* buff)
{
	printf(buff);
}

void n()
{
	// check for this lengh it seem not of if there aren't more variables
	// but why would be this offuscated ?
	// or just who coded that wanna troll ...
	// stack frame is size 0x218, i ve used 0x200
	// where are the 16 remaining bytes ?
	// really fgets is implemented witout sizeof ????

	char buff[512]; // {ebp - 0x208}

	fgets(buff, sizeof(buff), stdout); // stdout from libc 0x8049804
	p(buff);
	if (global == 0x1025544) // 16930116
	{
		static const char cmd[] = "/bin/cat /home/user/level5/.pass"; // 0x8048590
		system(cmd);
	}
}

int main(int ac, char** argv)
{
	(void)ac, (void)argv;

	n();
}