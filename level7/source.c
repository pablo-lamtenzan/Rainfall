
# include <stdlib.h> // malloc
# include <string.h> // strcpy
# include <stdio.h> // fopen, fgest, printf
# include <time.h> // time


struct strct
{
	char*	chars;
	int		value;
};

char data[0x44]; // 0x8049960

void m()
{
	static const char format[] = "%s - %d\n"; // 0x8049960

	printf(format, data, time(0x0l));
}

int main(int ac, char** av)
{
	static const char modes[] = "r"; // 0x80486e9
	static const char filename[] = "/home/user/level8/.pass"; // 0x80486eb
	static const char display[] = "~~"; // 0x8048703

	struct strct*	s1; // {esp + 0x1c}
	struct strct*	s2; // {esp + 0x18}
	
	s1 = malloc(sizeof(*s1));
	*s1 = (struct strct){.value=0x1, .chars=malloc(sizeof(char) * 0x8ul)};

	s2 = malloc(sizeof(*s2));
	*s2 = (struct strct){.value=0x2, chars=malloc(sizeof(char) * 0x8ul)};

	strcpy(s1->chars, av[1]);
	strcpy(s2->chars, av[2]);
	fgets(data, 0x44, fopen(filename, modes));
	puts(display);
}