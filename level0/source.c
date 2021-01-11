
# define _GNU_SOURCE // man setresgid

# include <stdlib.h> // atoi
# include <string.h> // strdup
# include <unistd.h> // getegid, geteuid, setresuid, execv
# include <stdio.h> // fwrite

int main (int ac, char** argv)
{
	(void)ac;
	// (decimal)0x1a7 == 423
	if (atoi(argv[1]) == 0x1a7)
	{
		static const char str_bin_sh[] = "/bin/sh"; // 0x80c5348 (not in the stack)
		//argv[0]					// esp + 0x10
		//argv[1]					// esp + 0x14
		uid_t uid;					// esp + 0x18
		gid_t gid;					// esp + 0x1c

		argv[0] = strdup(str_bin_sh);	// call + move eax
		argv[1] = 0x0;				// mv 0x0 into {esp + 0x14}
		gid = getegid();			// call + move eax
		uid = geteuid();			// call + move eax
		setresgid(gid, gid, gid);	// mv {esp + 0x1c} into the stack 3 times before call
		setresgid(uid, uid, uid);	// mv {esp + 0c18} into the stack 3 times before call
		execv(str_bin_sh, argv);	// mv 0x80c5348 and {esp + 10} into the stack before call
	}
	else
	{
		static const char no[] = "No !\n"; // 0x80c5350 (not in the stack)
		fwrite((void*)no, 0x1ul, sizeof(no), stdout);
	}
	return (0x0);
}