# include <stdlib.h> // malloc, system
# include <string.h> // strcpy
#include <stdio.h> // printf

void m() // 0x8048468
{
	static const char nope[] = "Nope"; // 0x80485d1
	printf(nope); // The compiler optimize the code replacing printf by puts
}

void n() // 0x8048454
{
	static const char cmd[] = "/bin/cat /home/user/level7/.pass"; // 0x80485b0
	system(cmd);
}

int main(int ac, char** av)
{
	void	(*fun)(); // {esp + 0x18}
	char*	ptr1; // {esp + 0x1c}

	ptr1 = malloc(sizeof(char) * 0x40); // 64
	fun = malloc(sizeof(fun)); // 4 bytes in 32bits arch
	fun = &m;
	strcpy(ptr1, av[1]);
	fun();
}