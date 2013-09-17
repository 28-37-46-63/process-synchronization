process-synchronization
=======================
Develop a software that will serve as an interactive demonstration (e - learning) of the process synchronization problem 
using semaphores, busy waiting, spinlocks, monitors, critical section,etc. 
Develop the software as a group by dividing the problems into modules for the individuals and 
upload individually into github. 
Provide the url of the github site for your group today.

README

1) Execute in Linux since the program makes use of Linux/Unix system calls like fork()

2) "itemProduced" is the shared memory variable which acts as a semaphore

3) Producer produces (into a file called "abc") when itemProduced is "false"; Consumer consumes from the same file otherwise

4) the global bool variable called locking is to implement busy waiting; to ensure busy waiting, just make sure you provide any argument to './a.out' when you run (Eg: ./a.out 5) since locking is set to true when argc > 1

5) when either of the processes writes/reads (ie, they are in their critical section) they lock the file (using the lockf function)

6) the "itemProduced" semaphore together with the lock applied on the file ensures mutual exclusion between the processes

