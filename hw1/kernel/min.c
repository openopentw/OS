#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_min(long a, long b)
{
	return (a < b)? a : b;
}
