#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <time.h>
#include <math.h>

int main() {
    int fd = open("pipe2", O_RDONLY);
    int fd1 = open("pipe3", O_WRONLY);
    double arr[2];//avg and sd
    double t[5];//temperatures
    int i=0;
    printf("Start Reading P2...\n");
    for(i=0; i<2; i++) {
        if(read(fd, &arr[i], sizeof(double))==-1) {
            return 2;
        }
    }
    for(i=0; i<5; i++) {
        if(read(fd, &t[i], sizeof(double))==-1) {
            return 2;
        }
    }
    close(fd);
    int avg = arr[0];
    int sd = arr[1];
    int cat;
    for(int i = 0; i < 5; i++) {
        if( t[i] == avg ) {
            cat = 0;
            write(fd1, &cat, sizeof(cat));
        } else if( t[i] > avg+sd ) {
            cat = 1;
            write(fd1, &cat, sizeof(cat));
        } else if(t[i] < avg+sd && t[i] > avg) {
            cat = 2;
            write(fd1, &cat, sizeof(cat));
        } else if(t[i] < avg && t[i] > avg-sd) {
            cat = 3;
            write(fd1, &cat, sizeof(cat));
        } else if(t[i] < avg-sd) {
            cat = 4;
            write(fd1, &cat, sizeof(cat));
        }
    }
    printf("Categories Written!\n");
    close(fd1);
    return 0;
}