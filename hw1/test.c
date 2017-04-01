#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	syscall(337);
	long int a = syscall(338, 2, 3);
	long int b = syscall(339, 2, 3);
	printf("%ld\n", a);
	printf("%ld\n", b);
	syscall(341);
	return 0;
}
