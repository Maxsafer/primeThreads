/**
 * Write a multithreaded program that outputs prime numbers.
 * This program should work as follows:
 * The user will run the program and will enter a number on the command line.
 * The program will then create a separate thread that outputs
 * all the prime numbers less than or equal to the number entered by the user.
 *
 * Most Unix/Linux/OS X users
 * gcc threadLab.c -lpthread
 *
 *
 * Figure 4.6
 *
 * @authors 
 * Operating System ITESM CSF
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *runner(void *param); /* this is the thread */

int main(int argc, char *argv[])
{

    pthread_t tid;       /* the thread identifier */
    pthread_attr_t attr; /* set of thread sttributes */

    //Verify two args were passed in
    if (argc < 2)
    {
        fprintf(stderr, "USAGE: ./primo.out <Integer value>\n");
        exit(1);
    }

    //verify the input is greater then or equal to two
    if (atoi(argv[1]) < 2)
    {
        fprintf(stderr, "USAGE: %d must be >= 2\n", atoi(argv[1]));
        exit(1);
    }
    printf("Prime Numbers: ");

    /* Get the default attributes */
    pthread_attr_init(&attr);
    /* Create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* Wait for the thread to exit */
    pthread_join(tid, NULL);
    printf("\nComplete\n");
}

/* The thread will begin control in this function */
void *runner(void *param)
{
    int i, j, upper = atoi(param);
    /* Check to see if a number is prime */
    for (i = 2; i < upper + 1; i++)
    {
        int trap = 0;
        /* Check each number for divisibility */
        for (j = 2; j < i; j++)
        {
            int result = i % j;
            /* If any of the numbers divide cleanly
             then this number is not prime. So
             stop checking. */
            if (result == 0)
            {
                trap = 1;
                break;
            }
        }
        //iteración del 2 al upper e imprimimos sólo los que si
        if (trap == 0)
        {
            printf("[%d] ", i);
        }
    }
    //Exit the thread
    pthread_exit(0);
}