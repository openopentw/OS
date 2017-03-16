#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	// syscall(337);
	syscall(338);
	long int a = syscall(339, 2, 3);
	long int b = syscall(340, 2, 3);
	printf("%ld\n", a);
	printf("%ld\n", b);
	return 0;
}
