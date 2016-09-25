#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/timer.h>

MODULE_DESCRIPTION("TEST!!");
MODULE_LICENSE("GPL");

int my_monitor(void *argc)
{
	/* fork a process here by using do_fork */

	/* execute program */

	/* Check signal */
	
	return 0; 
}

static int __init kernel_object_test_init(void)
{
    int result, result1;
    struct pid *kpid;
    struct task_struct *task;
    struct sched_param param;

	/* Write your Code here */

    /* create a kernel thread to run my_fork */
	return 0;
}

static void __exit kernel_object_test_exit(void)
{
    printk("<0>Remove the module\n");
}

module_init(kernel_object_test_init);
module_exit(kernel_object_test_exit);


