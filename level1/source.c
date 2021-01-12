#include <stdio.h> // gets
#include <stdlib.h> // system

void run()
{
	static const char bin_sh[] = "/bin/sh"; // 0x8048584 (not in the stack)
	static const char msg[] = "Good.. Wait what?\n"; // 0x8048570 (not in the stack)
	fwrite((void*)msg, 0x1ul, sizeof(msg), stdout);
	system(bin_sh);
}

int main(int ac, char** argv)
{
	(void)ac;
	char buff[64];	// 64 bytes cause esp is descremented by 0x50 in the stack frame creation
					// and as argument of gets {esp + 0x10} address is mv to the stack
					// 0x50 - 0x10 = 0x40 = 64 in decimal

	gets(buff);
}