/*
 * Author: Travis Hoover
 * Class: CSCI 3240
 * Professor: Dr. Hyrum Carroll
 * Date: May the 4th be with you in 2016
 */
#include "finalProject-mysteryFunction.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int highestReturnValue = 2; //initialize variable that is passed between pthreads. Set to 2 to ensure
                            //that is is being updated (if set to 0 it could be misinterpreted as failing)

 struct threadStruct {
    int (*C)[2];
    int x;
} threadStruct;

void *runMysteryFunction(void *argument);




int main(int argc, char** argv) {

    void *status = 0;
    int numberOfThreads = atoi(argv[1]); //Declare and initialize variable for the number of threads
    pthread_t mysteryThreads[numberOfThreads];
    struct threadStruct z[numberOfThreads];

    //handles the situation based on number of threads to be made
    int threadArray[numberOfThreads][2];
    if(numberOfThreads == 1) {
        threadArray[0][0] = 0;
        threadArray[0][1] = 100;
    }
    else if(numberOfThreads == 2) {
        threadArray[0][0] = 0;
        threadArray[0][1] = 50;
        threadArray[1][0] = 51;
        threadArray[1][1] = 100;
    }
    else if(numberOfThreads == 3) {
        threadArray[0][0] = 0;
        threadArray[0][1] = 33;
        threadArray[1][0] = 34;
        threadArray[1][1] = 66;
        threadArray[2][0] = 67;
        threadArray[2][1] = 100;
    }
    else {
        threadArray[0][0] = 0;
        threadArray[0][1] = 24;
        threadArray[1][0] = 25;
        threadArray[1][1] = 50;
        threadArray[2][0] = 51;
        threadArray[2][1] = 75;
        threadArray[3][0] = 76;
        threadArray[3][1] = 100;
    }


    for(int i = 0; i < numberOfThreads; i++){
        z[i].x = i;
        z[i].C = threadArray;
        pthread_create(&mysteryThreads[i], NULL, &runMysteryFunction, &z[i]);
    }
    for(int i = 0; i < numberOfThreads; i++)
         pthread_join(mysteryThreads[i], &status);


    printf("The maximum value that mysteryFunction() returns is %d\n", highestReturnValue);

    pthread_exit(NULL);
}

void *runMysteryFunction(void *argument)
{
    struct threadStruct* data = (struct threadStruct*)(argument);
    for(int a = data->C[data->x][0]; a < data->C[data->x][1]; a++){
        int value = mysteryFunction(a);
        if (value > highestReturnValue) { highestReturnValue = value; }
    }
    pthread_exit(data);
}