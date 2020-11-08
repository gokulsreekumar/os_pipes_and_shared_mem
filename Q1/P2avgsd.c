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
    int fd = open("pipe1", O_RDONLY);
    int fd1 = open("pipe2", O_WRONLY);
    double arr[5];
    int i=0;
    printf("Start Reading from P1...\n");
    for(i=0; i<5; i++) {
        if(read(fd, &arr[i], sizeof(double))==-1) {
            return 2;
        }
        printf("Reading!\n");
    }
    printf("Reading from P1 Over!\n");
    close(fd);
    // Avg
    double avg =0;
    double sd=0;
    for(i=0; i<5; i++) {
        avg += arr[i];
    }
    avg = avg / 5;
    for(i=0; i<5; i++) {
        sd += (arr[i]-avg)*(arr[i]-avg);
    }
    sd = sqrt(sd/5);
    // write avg and sd
    write(fd1, &avg, sizeof(double));
    write(fd1, &sd, sizeof(double));
    printf("Writing P2 Data.....\n");
    printf("Written avg = %lf, sd = %lf\n", avg, sd);
    //write p1_data
    for(i=0; i<5; i++) {
        if(write(fd1, &arr[i], sizeof(double))==-1) {
            return 2;
        }
    }
    printf("Written Temprature Array from P1\n");
    printf("P2 Data Written!\n");
    close(fd1);
    return 0;
}