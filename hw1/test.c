#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int n1, n2;

	// Show
	syscall(337);

	// Multiply
	scanf("%d%d", &n1, &n2);
	printf("%ld\n", syscall(338, n1, n2));

	// Min
	scanf("%d%d", &n1, &n2);
	printf("%ld\n", syscall(339, n1, n2));

	// bonus
	syscall(341);
	return 0;
}
