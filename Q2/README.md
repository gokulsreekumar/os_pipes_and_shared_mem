# Q2 README

## Contents

##### Using Shared Memory Files:

1. P1.c
2. P2.c
3. P3.c

# Instructions

### Shared Memory
1. Open Terminal inside this folder after downloading
2.  Compile the C files by running: <br /> ``` gcc  P1.c -o p1```<br /> ``` gcc  P2.c -o p2```<br /> ``` gcc P3e.c -o p3```
3. Now Run the Programs in multiple windows of terminal to see the outputs as: ```./p1```,```./p2```,```./p3```
4. Program 1 will prompt to enter the Password of length 10
5. P1 will pass password to P2 using shared memory, P2 will pass the number of alphanumeric and special characters to P3, and then P3 will pass the strength information to P1, which will print whether it is weak or strong, the corresponding logs can be seen as the output in P2 and P3. ( Same shared memory is used for passing all data and flags between processes )
