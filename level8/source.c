
// I didn't check the code from https://exploit.education/protostar/heap-one/
// Is not funny if i do, trust me
// This is of corse reverse style from scracth
// Just i have to say i remember about the shitty code who name all the same way
	// probally if i did not remember that, this code would fck my brain for a long time
	// in asm it seem offuscated but is just CODED LIKE SHIT (something to learn about that ?)

# include <stdio.h> // printf, fgets, fwrite
# include <stdlib.h> // malloc, free
# include <string.h> // strncmp

struct auth
{
	char str[64]; // is never allocated so can't be a ptr ...
	int val;
};

struct auth* auth; // The only explenation possible malloc does sizeof 0x4
							// sizeof(auth) is size of ptr auth and not struct auth
							// Shitty code
							// 0x8049aac

char* service;				// 0x8049ab0

// using in gdb "x/wx <addr>"" to a global var is possible to visualise it name

int main(int ac, char** argv)
{
	(void)ac, (void)argv;

	static const char cmp1[] = "auth"; // 0x8048819
	static const char cmp2[] = "reset"; // 0x804881f
	static const char cmp3[] = "service"; // 0x8048825
	static const char cmp4[] = "login"; // 0x804882d

	char buff[0x80]; // see size intruction 0x0804859f, addr is {esp + 20}

	while (1)
	{
		// <main + 16>
		static const char format[] = "%p, %p \n"; // 0x8048810
		printf(format, auth, service);
		if (!fgets(buff, sizeof(buff), stdin)) // stdin loaded from libc 0x8049a80
			break ; // je <main + 456> (the end)
		if(!strncmp(cmp1, buff, sizeof(cmp1) - 0x1ul)) // inline strncmp: repz cmps BYTE PTR<> PTR<>
		{
			auth = malloc(sizeof(auth)); // sizeof(auth) == 0x4 cause it takes the pointer and not the struct
			auth->val = 0; // instruction 0x080485fa
			// previous if jump to <main + 222> this if jumps to <main + 222> so this if is in the previous if
			if (!(strlen(buff + sizeof(cmp1)) > 0x1e)) // inline strlen, 0x1e == 30, increment buff instruction 0x08048604
				strcpy(auth->str, buff + sizeof(cmp1)); // incrementation of src instruction 0x0804862e
		}
		// <main + 222>
		if (!strncmp(cmp2, buff, sizeof(cmp2) - 0x1ul)) // inline strncmp: repz cmps BYTE PTR<> PTR<>, size in intruction 0x0804864d
			free(auth);
		// <main + 276>
		if (!strncmp(cmp3, buff, sizeof(cmp3) - 0x2ul)) // size 6 in instruction 0x0804867e and inline too
			service = strdup(buff + sizeof(cmp3) - 0x1ul); // size 7 in instruction 0x080486a5
		// <main + 337>
		if (!strncmp(cmp4, buff, sizeof(cmp4) - 0x1ul)) // inline strncmp: repz cmps BYTE PTR<> PTR<>, size in instruction 0x080486c0
		{
			if (auth->val)
			{
				static const char binsh[] = "/bin/sh"; // 0x8048833

				system(binsh);
			}
			else // <main + 411>
			{
				static const char passw[] = "Password:\n"; // 0x804883b

				fwrite(passw, 0x1ul, sizeof(passw) - 0x1ul, stdout);
			}
		}
	}
	// <main + 456>
	return (0x0);
}