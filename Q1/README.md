# Q1 README

## Contents

##### Using FIFO (Named Pipes)

1. P1tempwrite.c
2. P2avgsd.c
3. P3update.c

##### Using Unnamed Pipes 

1. unnamed.c


# Instructions

### 1. Using FIF0
1. Open Terminal inside this folder after downloading
2. Run: <br />``` mkfifo pipe1 ``` ,<br />``` mkfifo pipe2 ```,<br /> ``` mkfifo pipe3``` <br /> this will Create 3 files which will be associated with each of the pipes used inside the programs
3.  Compile the C files by running: <br /> ``` gcc  P1tempwrite.c -o p1```<br /> ``` gcc  P2avgsd.c -o p2```<br /> ``` gcc P3update.c -o p3```
4. Now Run the Programs in multiple windows of terminal to see the outputs as: ```./p1```,```./p2```,```./p3```
5. Program 1 will prompt to enter the Temperatures for 5 locations, enter them in the valid range
6. P1 will pass the temperature array data to P2, P2 will pass the average and standard deviation, as well as the input temperatures to P3, and then P3 will pass the categories to P1 which will use the categories to revise temperature and print it to terminal, the corresponding logs can be seen as the output in P2 and P3.


### 2. Using Unnamed Pipes
1. Open Terminal inside this folder after downloading
2. Compile the C Program  ``` gcc  unnamed.c -o u```
3. Run ``` ./u ```
4. Enter the Temperatures from 5 locations (in valid range)
5. Output of Revised Temperatures for each location is printed.