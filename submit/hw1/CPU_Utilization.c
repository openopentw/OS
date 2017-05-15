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

// #ifndef arch_idle_time
// #define arch_idle_time(cpu) 0
// #endif

asmlinkage unsigned long long sys_CPU_Utilization(void)
{
	int i;
	cputime64_t user, nice, system, idle;
	cputime64_t user2, nice2, system2, idle2;
	unsigned long long cpu;
	unsigned long long total;
	unsigned long long mod;

	user = nice = system = idle = cputime64_zero;
	user2 = nice2 = system2 = idle2 = cputime64_zero;

	for_each_possible_cpu(i) {
		user = cputime64_add(user, kstat_cpu(i).cpustat.user);
		nice = cputime64_add(nice, kstat_cpu(i).cpustat.nice);
		system = cputime64_add(system, kstat_cpu(i).cpustat.system);
		idle = cputime64_add(idle, kstat_cpu(i).cpustat.idle);
		// idle = cputime64_add(idle, arch_idle_time(i));
	}

	ssleep(2);

	for_each_possible_cpu(i) {
		user2 = cputime64_add(user2, kstat_cpu(i).cpustat.user);
		nice2 = cputime64_add(nice2, kstat_cpu(i).cpustat.nice);
		system2 = cputime64_add(system2, kstat_cpu(i).cpustat.system);
		idle2 = cputime64_add(idle2, kstat_cpu(i).cpustat.idle);
		// idle2 = cputime64_add(idle2, arch_idle_time(i));
	}

	// calc cpu_utilization
	total = (user2 + nice2 + system2 + idle2)
		- (user + nice + system + idle);
	cpu = (user2 + nice2 + system2)
		- (user + nice + system);
	cpu *= 100000;
	mod = do_div(cpu, total);

	// rounding
	mod = do_div(cpu, 10);
	if(mod > 5) {
		++cpu;
	}

	mod = do_div(cpu, 100);
	printk("%llu.%llu%%\n", cpu, mod);

	return cpu;
}
