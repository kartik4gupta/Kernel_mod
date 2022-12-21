#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");


static int pid;
module_param(pid, int, 0);


static int __init print_pgid_init(void)
{
    struct task_struct *task; //deplag
    struct timespec ts;
    getnstimeofday(&ts);

    printk("%ld.%09ld\n", (long)ts.tv_sec, ts.tv_nsec);

    // Find the task_struct for the given process ID
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    

    // Print the PGID of the process
   

    printk("pid: %d\n", task->pid);  //deplag
    printk("user_id: %d\n", task->cred->uid.val);
    printk("print_pgid: PGID of process with ID %d is %d\n", pid, task->tgid);
    printk("command path: %s\n", task->comm);

    return 0;
}

static int __exit print_pgid_exit(void)
{
    printk("Exited from the kernel module\n");
    return 0;
}

module_init(print_pgid_init);
module_exit(print_pgid_exit);
