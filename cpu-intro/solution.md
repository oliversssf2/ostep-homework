1. CPU utilization should be 100% as there is no IO operation. Program output:
    ```
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
2. It takes 4 time unit for the first process to finish; it takes 7 time units for the second process to finish (RUN:io -> BLOCKED (5 time units) -> RUN:io_done). Program output is:
    ```
    ./process-run.py -l 4:100,1:0 -cp
    Time        PID: 0        PID: 1           CPU           IOs
    1        RUN:cpu         READY             1          
    2        RUN:cpu         READY             1          
    3        RUN:cpu         READY             1          
    4        RUN:cpu         READY             1          
    5           DONE        RUN:io             1          
    6           DONE       BLOCKED                           1
    7           DONE       BLOCKED                           1
    8           DONE       BLOCKED                           1
    9           DONE       BLOCKED                           1
    10           DONE       BLOCKED                           1
    11*          DONE   RUN:io_done             1          

    Stats: Total Time 11
    Stats: CPU Busy 6 (54.55%)
    Stats: IO Busy  5 (45.45%)
    ```
3. It only takes 7 time units in total to finish both processes as the 4 cpu operations of the second process can be executed while the IO process is blocked (for 5 time unit). Program outputs are:
    ```
    ./process-run.py -l 1:0,4:100 -cp
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED       RUN:cpu             1             1
    3        BLOCKED       RUN:cpu             1             1
    4        BLOCKED       RUN:cpu             1             1
    5        BLOCKED       RUN:cpu             1             1
    6        BLOCKED          DONE                           1
    7*   RUN:io_done          DONE             1          

    Stats: Total Time 7
    Stats: CPU Busy 6 (85.71%)
    Stats: IO Busy  5 (71.43%)
    ```
4. The second process only starts after the first process is finished, thus requires 11 time units in total. Program outputs:
    ```
    ./process-run.py -l 1:0,4:100 -S SWITCH_ON_END -cp
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED         READY                           1
    3        BLOCKED         READY                           1
    4        BLOCKED         READY                           1
    5        BLOCKED         READY                           1
    6        BLOCKED         READY                           1
    7*   RUN:io_done         READY             1          
    8           DONE       RUN:cpu             1          
    9           DONE       RUN:cpu             1          
    10           DONE       RUN:cpu             1          
    11           DONE       RUN:cpu             1          

    Stats: Total Time 11
    Stats: CPU Busy 6 (54.55%)
    Stats: IO Busy  5 (45.45%)
    ```
5. Same as Q3. Only 7 time units are required. Program outputs:
    ```
    ./process-run.py -l 1:0,4:100 -S SWITCH_ON_IO -cp
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1          
    2        BLOCKED       RUN:cpu             1             1
    3        BLOCKED       RUN:cpu             1             1
    4        BLOCKED       RUN:cpu             1             1
    5        BLOCKED       RUN:cpu             1             1
    6        BLOCKED          DONE                           1
    7*   RUN:io_done          DONE             1          

    Stats: Total Time 7
    Stats: CPU Busy 6 (85.71%)
    Stats: IO Busy  5 (71.43%)
    ```
6. System resources are not effectively utilized. Program Outputs:
    ```
    ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -cp -I IO_RUN_LATER
    Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY         READY             1             1
    3        BLOCKED       RUN:cpu         READY         READY             1             1
    4        BLOCKED       RUN:cpu         READY         READY             1             1
    5        BLOCKED       RUN:cpu         READY         READY             1             1
    6        BLOCKED       RUN:cpu         READY         READY             1             1
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
    19        BLOCKED          DONE          DONE          DONE                           1
    20        BLOCKED          DONE          DONE          DONE                           1
    21        BLOCKED          DONE          DONE          DONE                           1
    22        BLOCKED          DONE          DONE          DONE                           1
    23        BLOCKED          DONE          DONE          DONE                           1
    24*   RUN:io_done          DONE          DONE          DONE             1          
    25         RUN:io          DONE          DONE          DONE             1          
    26        BLOCKED          DONE          DONE          DONE                           1
    27        BLOCKED          DONE          DONE          DONE                           1
    28        BLOCKED          DONE          DONE          DONE                           1
    29        BLOCKED          DONE          DONE          DONE                           1
    30        BLOCKED          DONE          DONE          DONE                           1
    31*   RUN:io_done          DONE          DONE          DONE             1          

    Stats: Total Time 31
    Stats: CPU Busy 21 (67.74%)
    Stats: IO Busy  15 (48.39%)
    ```
7. THis time `RUN:io_done`'s are run immediately after the IO is finished. This allows the CPU and IO processes to interleaves CPU control when the IO process is blocked. Program Outputs:
    ```
    ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -cp -I IO_RUN_IMMEDIATE
    Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1          
    2        BLOCKED       RUN:cpu         READY         READY             1             1
    3        BLOCKED       RUN:cpu         READY         READY             1             1
    4        BLOCKED       RUN:cpu         READY         READY             1             1
    5        BLOCKED       RUN:cpu         READY         READY             1             1
    6        BLOCKED       RUN:cpu         READY         READY             1             1
    7*   RUN:io_done          DONE         READY         READY             1          
    8         RUN:io          DONE         READY         READY             1          
    9        BLOCKED          DONE       RUN:cpu         READY             1             1
    10        BLOCKED          DONE       RUN:cpu         READY             1             1
    11        BLOCKED          DONE       RUN:cpu         READY             1             1
    12        BLOCKED          DONE       RUN:cpu         READY             1             1
    13        BLOCKED          DONE       RUN:cpu         READY             1             1
    14*   RUN:io_done          DONE          DONE         READY             1          
    15         RUN:io          DONE          DONE         READY             1          
    16        BLOCKED          DONE          DONE       RUN:cpu             1             1
    17        BLOCKED          DONE          DONE       RUN:cpu             1             1
    18        BLOCKED          DONE          DONE       RUN:cpu             1             1
    19        BLOCKED          DONE          DONE       RUN:cpu             1             1
    20        BLOCKED          DONE          DONE       RUN:cpu             1             1
    21*   RUN:io_done          DONE          DONE          DONE             1          

    Stats: Total Time 21
    Stats: CPU Busy 21 (100.00%)
    Stats: IO Busy  15 (71.43%)
    ```
8. Everything becomes quite unpredictable. SWITCH_ON_IO is significantly faster than SWITCH_ON_END but IO_RUN_IMMEDIATE doesn't perform any better than IO_RUN_LATER (probably due to the randomnesss?)