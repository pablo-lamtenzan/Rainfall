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
	char*	ptr1; // {esp + 0x1c}
	void	(*fun)(); // {esp + 0x18}

	ptr1 = malloc(sizeof(char) * 0x40); // 64
	fun = malloc(sizeof(fun)); // 4 bytes in 32bits arch
	fun = &m; // this line could be wrong and i need a pointer to the function pointer...
				// fun = (void**)malloc(sizeof(fun));
				// *fun = m;
	strcpy(ptr1, av[1]);
	fun();
}