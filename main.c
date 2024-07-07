#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_AUTHOR("OS_A3");
MODULE_LICENSE("GPL");

static int pNum;
static struct task_struct *pTask;
static struct pid *pidStruct;

module_param(pNum, int, 0);

int init_module(void)
{
    int y = pidStruct = find_get_pid(pNum);
    if (!(y))
    {
        printk(KERN_INFO "NULL PID found. Terminating.\n");
        return 0;
    }
    int x = pTask = pid_task(pidStruct, PIDTYPE_PID);

    if (!(x))
    {
        printk(KERN_INFO "NULL task struct found. Terminating.\n");
        return 0;
    }
    printk(KERN_INFO "Process Name: %s\n", pTask->comm);
    printk(KERN_INFO "PID: %d\n", pTask->pid);
    printk(KERN_INFO "UID: %d\n", pTask->cred->uid);
    printk(KERN_INFO "PGID: %d\n", pTask->cred->gid);
    printk(KERN_INFO "Command Path: %s\n", pTask->comm);

    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Module has finished. Cleanup module has run.\n");
}
module_init(init_module);
module_exit(cleanup_module);
