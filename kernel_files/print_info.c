#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_print_info(int pid, long startSec, long startDec, long endSec, long endDec) {
	printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld\n", pid, startSec, startDec, endSec, endDec);
}