#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main() {
    int fd1[2], fd2[2], fd3[2];
    int pid1, pid2;
    
    // Create Pipes
    if (pipe(fd1) == -1) {
        printf("Error while creating pipe 1 \n");
        return 1;
    }
    if (pipe(fd2) == -1) {
        printf("Error while creating pipe 2 \n");
        return 1;
    }
    if (pipe(fd3) == -1) {
        printf("Error while creating pipe 3 \n");
        return 1;
    }

    pid1 = fork();
    if (pid1 != 0) { // Parent process P1
        pid2 = fork();
        if(pid2 != 0) { // Parent process P1

            close(fd1[0]); // Close unused pipe1 read side
            close(fd3[1]); // Close unused pipe3 write side

            close(fd2[0]); // Close unused pipe2 read side
            close(fd2[1]); // Close unused pipe2 write side

            double t[5];

            for(int i = 0; i < 5; i++) {
                printf("Enter Temperature for Loc-(%d):\n", i+1);
                scanf("%lf", &t[i]);
                if(t[i]<15 || t[i]>45) {
                printf("Temperature Out Of Range (15-45)! Enter Again:\n");
                i = i-1;
                }
            }

            for(int i = 0; i < 5; i++) {
                write(fd1[1], &t[i], sizeof(t[i]));
            }

            double newTemp;
            int category;

            printf("Revised Temperatures:\n");
            for(int i = 0; i < 5; i++) {
                read(fd3[0], &category, sizeof(category));
                if( category == 0 ) {
                    newTemp = t[i];
                    printf("Loc(%d) = %lf\n", i+1, newTemp);
                } else if( category == 1 ) {
                    newTemp = t[i]-3;
                    printf("Loc(%d) = %lf\n", i+1, newTemp);
                } else if( category == 2 ) {
                    newTemp = t[i]-1.5;
                    printf("Loc(%d) = %lf\n", i+1, newTemp);
                } else if( category == 3 ) {
                    newTemp = t[i]+2;
                    printf("Loc(%d) = %lf\n", i+1, newTemp);
                } else if( category == 4 ) {
                    newTemp = t[i]+2.5;
                    printf("Loc(%d) = %lf\n", i+1, newTemp);
                }
            }

            close(fd1[1]); // Close used pipe1 write side
            close(fd3[0]); // Close used pipe3 read side

        }
        else { //child process P3

            close(fd2[1]); // Close unused pipe1 write side
            close(fd3[0]); // Close unused pipe3 read side

            close(fd1[0]); // Close unused pipe1 read side
            close(fd1[1]); // Close unused pipe1 write side

            double t[5], avg, sd;
            
            for(int i = 0; i < 5; i++) {
                read(fd2[0], &t[i], sizeof(t[i]));
            }

            read(fd2[0], &avg, sizeof(avg));
            read(fd2[0], &sd, sizeof(sd));

            int cat;
            for(int i = 0; i < 5; i++) {
                if( t[i] == avg ) {
                    cat = 0;
                    write(fd3[1], &cat, sizeof(cat));
                } else if( t[i] > avg+sd ) {
                    cat = 1;
                    write(fd3[1], &cat, sizeof(cat));
                } else if(t[i] < avg+sd && t[i] > avg) {
                    cat = 2;
                    write(fd3[1], &cat, sizeof(cat));
                } else if(t[i] < avg && t[i] > avg-sd) {
                    cat = 3;
                    write(fd3[1], &cat, sizeof(cat));
                } else if(t[i] < avg-sd) {
                    cat = 4;
                    write(fd3[1], &cat, sizeof(cat));
                }
            }

            close(fd2[0]); // Close used pipe2 read side
            close(fd3[1]); // Close used pipe3 write side
        }
        
    } else { //child process P2

        close(fd1[1]); // Close unused pipe1 write side
        close(fd2[0]); // Close unused pipe2 read side

        close(fd3[0]); // Close unused pipe3 read side
        close(fd3[1]); // Close unused pipe3 write side

        double t[5], avg = 0.0, sd = 0.0;
            
        for(int i = 0; i < 5; i++) {
            read(fd1[0], &t[i], sizeof(t[i]));
        }

        for(int i = 0; i < 5; i++) {
            avg += t[i];
        }
        avg /= 5;

        for(int i = 0; i < 5; i++) {
            sd += pow(t[i] - avg, 2);
        }
        sd = sqrt(sd / 5);

        for(int i = 0; i < 5; i++) {
            write(fd2[1], &t[i], sizeof(t[i]));
        }

        write(fd2[1], &avg, sizeof(avg));
        write(fd2[1], &sd, sizeof(sd));

        close(fd1[0]); // Close used pipe1 read side
        close(fd2[1]); // Close used pipe2 write side
    }
    return 0;
}