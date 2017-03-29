#include <linux/kernel.h>
#include <linux/linkage.h>

#include <linux/delay.h>

#include <linux/cpumask.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/irqnr.h>
#include <asm/cputime.h>
#include <asm/div64.h>		// do_div()

#ifndef arch_idle_time
#define arch_idle_time(cpu) 0
#endif

asmlinkage long sys_CPU_Utilization(void)
{
	int i;
	cputime64_t user, nice, system, idle, iowait, irq, softirq;
	unsigned long long total = user + nice + system + idle + iowait + irq + softirq;
	unsigned long mod;

	user = nice = system = idle = iowait =
		irq = softirq = cputime64_zero;

	for_each_possible_cpu(i) {
		user = cputime64_add(user, kstat_cpu(i).cpustat.user);
		nice = cputime64_add(nice, kstat_cpu(i).cpustat.nice);
		system = cputime64_add(system, kstat_cpu(i).cpustat.system);
		idle = cputime64_add(idle, kstat_cpu(i).cpustat.idle);
		idle = cputime64_add(idle, arch_idle_time(i));
		iowait = cputime64_add(iowait, kstat_cpu(i).cpustat.iowait);
		irq = cputime64_add(irq, kstat_cpu(i).cpustat.irq);
		softirq = cputime64_add(softirq, kstat_cpu(i).cpustat.softirq);
	}

	ssleep(2);

	for_each_possible_cpu(i) {
		user -= cputime64_add(user, kstat_cpu(i).cpustat.user);
		nice -= cputime64_add(nice, kstat_cpu(i).cpustat.nice);
		system -= cputime64_add(system, kstat_cpu(i).cpustat.system);
		idle -= cputime64_add(idle, kstat_cpu(i).cpustat.idle);
		idle -= cputime64_add(idle, arch_idle_time(i));
		iowait -= cputime64_add(iowait, kstat_cpu(i).cpustat.iowait);
		irq -= cputime64_add(irq, kstat_cpu(i).cpustat.irq);
		softirq -= cputime64_add(softirq, kstat_cpu(i).cpustat.softirq);
	}

	printk("TOTAL: %llu\n", total);
	printk("IDLE: %llu\n", idle);
	idle *= 100000;
	mod = do_div(idle, total);
	printk("IDLE: %llu\n", idle);

	return 0;
}
