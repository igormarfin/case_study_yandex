#ifndef CPUTIME_H
#define CPUTIME_H

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

double get_cpu_time(){
    return (double)clock()/CLOCKS_PER_SEC;
}

#endif
