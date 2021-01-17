
# include <stdio.h> // puts
# include <string.h> // strcpy
# include <unistd.h> // read

void p(char *out, char* dest)
{
	char buff[0x1008]; // {ebp - 0x1008}

	puts(out);
	read(STDIN_FILENO, buff, sizeof(buff) - 0x08ul); // always shitty code or non sense sizes ...
	*strchr(buff, 0xa) = 0x0; // '\n'
	strncpy(dest, buff, 0x14);
}

void pp(char *buff)
{
	static const char out[] = " _ "; // 0x80486a0
	static const char espace[] = " "; // 0x80486a4

	char b1[0x50 - 0x30];	// {esp - 0x30}
	char b2[0x30 - 0x1c];	// {esp - 0x1c}

	p(out, b1);
	p(out, b2);
	strcpy(buff, b1);
	buff[strlen(buff)] = espace; // inlined strlen at 0x08048579 
	strcat(buff, b2);
}

int main(int ac, char** av)
{
	char buff[0x40 - 0x16]; // so big ?
	pp(buff);
	puts(buff);
	return (0x0);
}
// FIRST READ == MAX 20 BYTES (more does not copy (could segfault))
// SECOND READ == MAX 16 BYTES (more segfault)
