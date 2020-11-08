#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int fd = open("pipe1", O_WRONLY);
    int fd1 = open("pipe3", O_RDONLY);
    double temp[5];
    for(int i=0; i<5; i++) {
        printf("Enter Temperature for Loc-(%d):\n", i+1);
        scanf("%lf", &temp[i]);
        if(temp[i]<15 || temp[i]>45) {
            printf("Temperature Out Of Range (15-45)! Enter Again:\n");
            i = i-1;
        }
    }
    for(int i=0; i<5; i++) {
        if(write(fd, &temp[i], sizeof(double))==-1) {
            return 2;
        }
        printf("writing!\n");
    }
    printf("Writing P1 Data Over\n");
    close(fd);

    int cats[5];
    printf("Reading Categories from P3.....\n");
    for(int i=0; i<5; i++) {
        if(read(fd1, &cats[i], sizeof(int))==-1) {
            return 2;
        }
    }
    
    for(int i=0; i<5; i++) {
        if(cats[i] == 0) {
            continue;
        } else if(cats[i] == 1) {
            temp[i]-=3;
        } else if(cats[i] == 2) {
            temp[i]-= 1.5;
        } else if(cats[i] == 3) {
            temp[i]+=2;
        } else if(cats[i] == 4) {
            temp[i]+=2.5;
        }
    }
    printf("Revised Temperatures: \n");
    for(int i=0; i<5; i++) {
        printf("Loc(%d) = %lf\n", i+1, temp[i]);
    }
    close(fd1);

    return 0;
}