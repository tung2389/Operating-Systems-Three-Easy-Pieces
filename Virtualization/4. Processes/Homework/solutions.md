1. The CPU utilization would be 100%. Since we specify that 100% chances that an instruction will use the CPU. 

```
prompt> ./process-run.py : -l 5:100,5:100

Produce a trace of what would happen when you run these processes:
Process 0
cpu
cpu
cpu
cpu
cpu

Process 1
cpu
cpu
cpu
cpu
cpu

Important behaviors:
System will switch when the current process is FINISHED or ISSUES AN IO
After IOs, the process issuing the IO will run LATER (when it is its turn)
```

```
prompt> ./process-run.py : -l 5:100,5:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
1        RUN:cpu         READY             1
2        RUN:cpu         READY             1
3        RUN:cpu         READY             1
4        RUN:cpu         READY             1
5        RUN:cpu         READY             1
6           DONE       RUN:cpu             1
7           DONE       RUN:cpu             1
8           DONE       RUN:cpu             1
9           DONE       RUN:cpu             1
10           DONE       RUN:cpu             1

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```

2. We have 4 clock tikcs for 4 CPU instructions, 1 clock tick for I/O initiation, 5 clock tick (default option) for I/O to complete, 1 clock tick for I/O completion. Therefore, it takes 4 + 1 + 5 + 1 = 11 clock ticks to complete both processes.

```
prompt> ./process-run.py -l 4:100,1:0
Produce a trace of what would happen when you run these processes:
Process 0
cpu
cpu
cpu
cpu

Process 1
io
io_done

Important behaviors:
System will switch when the current process is FINISHED or ISSUES AN IO
After IOs, the process issuing the IO will run LATER (when it is its turn)
```

```
prompt> ./process-run.py -l 4:100,1:0 -c -p
Time        PID: 0        PID: 1           CPU           IOs
1        RUN:cpu         READY             1
2        RUN:cpu         READY             1
3        RUN:cpu         READY             1
4        RUN:cpu         READY             1
5           DONE        RUN:io             1
6           DONE       WAITING                           1
7           DONE       WAITING                           1
8           DONE       WAITING                           1
9           DONE       WAITING                           1
10           DONE       WAITING                           1
11*          DONE   RUN:io_done             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```

3. The first process, which is one with I/O, will run first (because that's how we specify the order). In the WAITING states of the first process, the CPU is idle and therefore the CPU can be used to handle the second process while the first process is waiting for I/O to complete. The I/O takes 5 clock tick (not including I/O initiation and I/O completion), and the second process only takes 4 clock ticks to complete. Therefore, the second process will complete before the first process's I/O completes. Therefore, the time it takes for both processes to complete is 1 + 5 + 1 = 7 clock ticks.

```
prompt> ./process-run.py -l 1:0,4:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
1         RUN:io         READY             1
2        WAITING       RUN:cpu             1             1
3        WAITING       RUN:cpu             1             1
4        WAITING       RUN:cpu             1             1
5        WAITING       RUN:cpu             1             1
6        WAITING          DONE                           1
7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```

4. Now the system will wait for the first process to complete before executing the second process, even though when the first process is in waiting state it doesn't use CPU (this is a waste).time = 1 + 5 + 1 + 4 = 11 clock ticks

```
prompt> ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END
Time        PID: 0        PID: 1           CPU           IOs
1         RUN:io         READY             1
2        WAITING         READY                           1
3        WAITING         READY                           1
4        WAITING         READY                           1
5        WAITING         READY                           1
6        WAITING         READY                           1
7*   RUN:io_done         READY             1
8           DONE       RUN:cpu             1
9           DONE       RUN:cpu             1
10           DONE       RUN:cpu             1
11           DONE       RUN:cpu             1
```

5. The system will switch to handle the second process while the first process is in WAITING state (because I/O hasn't finished yet). time = 1 + 5 + 1 = 7 clock ticks

```
prompt> ./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO
Time        PID: 0        PID: 1           CPU           IOs
1         RUN:io         READY             1
2        WAITING       RUN:cpu             1             1
3        WAITING       RUN:cpu             1             1
4        WAITING       RUN:cpu             1             1
5        WAITING       RUN:cpu             1             1
6        WAITING          DONE                           1
7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```

6. The system switches to other processes when the process with I/O (process 0) is in the waiting state. However, when the process 0 finishes, the system doesn't run it back but uses the CPU for all other processes. When all other processes except process 0 have finished, the system switches back to run process 0. But system resources are not being effectively utilized, since after all other processes have finished, process 0 still have a lot of waiting time in which the CPU is idle. It would be better if the system runs process 0 immediately after it has come back to READY state, and uses its next waiting time to handle other processes.

```
prompt> ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
1         RUN:io         READY         READY         READY             1
2        WAITING       RUN:cpu         READY         READY             1             1
3        WAITING       RUN:cpu         READY         READY             1             1
4        WAITING       RUN:cpu         READY         READY             1             1
5        WAITING       RUN:cpu         READY         READY             1             1
6        WAITING       RUN:cpu         READY         READY             1             1
7*         READY          DONE       RUN:cpu         READY             1
8          READY          DONE       RUN:cpu         READY             1
9          READY          DONE       RUN:cpu         READY             1
10          READY          DONE       RUN:cpu         READY             1
11          READY          DONE       RUN:cpu         READY             1
12          READY          DONE          DONE       RUN:cpu             1
13          READY          DONE          DONE       RUN:cpu             1
14          READY          DONE          DONE       RUN:cpu             1
15          READY          DONE          DONE       RUN:cpu             1
16          READY          DONE          DONE       RUN:cpu             1
17    RUN:io_done          DONE          DONE          DONE             1
18         RUN:io          DONE          DONE          DONE             1
19        WAITING          DONE          DONE          DONE                           1
20        WAITING          DONE          DONE          DONE                           1
21        WAITING          DONE          DONE          DONE                           1
22        WAITING          DONE          DONE          DONE                           1
23        WAITING          DONE          DONE          DONE                           1
24*   RUN:io_done          DONE          DONE          DONE             1
25         RUN:io          DONE          DONE          DONE             1
26        WAITING          DONE          DONE          DONE                           1
27        WAITING          DONE          DONE          DONE                           1
28        WAITING          DONE          DONE          DONE                           1
29        WAITING          DONE          DONE          DONE                           1
30        WAITING          DONE          DONE          DONE                           1
31*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
```

7. The system now immediately runs the process that issued the I/O after it has completed. This way utilizes resources better because we can utilize more idle time of the CPU to handle other processes.

```
prompt> ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1
  8         RUN:io          DONE         READY         READY             1
  9        WAITING          DONE       RUN:cpu         READY             1             1
 10        WAITING          DONE       RUN:cpu         READY             1             1
 11        WAITING          DONE       RUN:cpu         READY             1             1
 12        WAITING          DONE       RUN:cpu         READY             1             1
 13        WAITING          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1
 15         RUN:io          DONE          DONE         READY             1
 16        WAITING          DONE          DONE       RUN:cpu             1             1
 17        WAITING          DONE          DONE       RUN:cpu             1             1
 18        WAITING          DONE          DONE       RUN:cpu             1             1
 19        WAITING          DONE          DONE       RUN:cpu             1             1
 20        WAITING          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)
```