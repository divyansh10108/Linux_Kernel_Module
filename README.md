
<H1 align = "center"> Kernel Module </H1>

Kernel modules are pieces of code that can be loaded and unloaded into the kernel upon demand. They extend the functionality of the kernel without the need to reboot the system. A module can be configured as built-in or loadable.

## Q3) Kernel Module
<p align="Left">
Implementing a kernel system call as a module. The task of the system call would be to read the entries of the process task_struct corresponding to any given process (supplied as input via command line argument) and prints the values of the following field: pid, user id, process group id (pgid) and command path. The system call should be implemented in the kernel and not directly as
a mainline kernel function.
</p>

#### Implementation

For this Implementation the ```task_struct``` of the given ```PID``` is fetched using the ```pid_task(find_pid_ns(id, &init_pid_ns), PIDTYPE_PID);``` then the ```task_struct``` is read for the specific  ```PID``` and the output is dumped to the ```SYSLOG``` using the ```printk``` and read to the user space using the ```dmesg``` call.



## `Installation`

```console
# run the Makefile
$> make -f Makefile
       OR
$> make
```
`Load the Module with PID as parameter`
```console
$> sudo insmod main.ko pid=(PID)

```
`Check Output`

```console
$> sudo tail -n 50 /var/log/syslog

```
`Unload the Module`

```console
$> sudo rmmod main

```
<br><br><br>
<br><br><br>
<br><br><br>
<br><br><br>

<br>

<p align=center> --- EOF --- </p>
