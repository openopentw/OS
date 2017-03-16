#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_hello(void)
{
	printk("HELLO SYSTEM CALL \n");
	return 0;
}
