#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_show(void)
{
	printk("b04902053 YJC\n");
	return 0;
}
