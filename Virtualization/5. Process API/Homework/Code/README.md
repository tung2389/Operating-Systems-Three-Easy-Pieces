1. The parent process and the child process both have their own private memory. Therefore, no process affects another's variable

Output:
```
Now x value in parent process is 300
x value in child process is 100
Now x value in child process is 200
```

2. They can both access the file descriptor. The content written in the file depends on whether the parent or child process execute first.

Output:
```
Parent process's file descriptor is 3
Child process's file descriptor is 3
```

file.txt:
```
Written by parent processWritten by child process
```

3. To suspend the parent's process output before the child process print, we just need to write to some file after the child process print, and use a while loop to suspend the parent process until it have read some message in that file. Please check [my code](./q3.c) for more detail