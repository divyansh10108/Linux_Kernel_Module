#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>

#include <linux/sched.h>

#include <pid.h>

#define INFO_PROCESSOR 287
#define TABLE sys_call_table

void alternate_RW(int x)
{
    if (x == 1)
    {
        set_memory_rw(PAGE_ALIGN(TABLE), 1);
        sys_call_table[287] = sys_read_task_struct;
        set_memory_ro(PAGE_ALIGN(TABLE), 1);
    }
    else
    {
        set_memory_rw(PAGE_ALIGN(sys_call_table), 1);
        sys_call_table[__NR_read_task_struct] = original_sys_call_function;
        set_memory_ro(PAGE_ALIGN(sys_call_table), 1);
    }
}
void printTasks(struct task_struct *task)
{
    printk("pid: %d\n", task->pid);
    printk("uid: %d\n", task->uid);
    printk("pgid: %d\n", task->pgid);
    printk("comm: %s\n", task->comm);
}
void __init sys_call_init()
{
    alternate_RW(1);
}

void __exit sys_call_exit()
{
    alternate_RW(2);
}
SYSCALL_DEFINE1(provessInfo, pid_t, pid)
{
    struct task_struct *task = pid_task(find_vpid(pid), PIDTYPE_PID);

    printTasks(task);
    module_init(sys_call_init);
    module_exit(sys_call_exit);

    return 0;
}