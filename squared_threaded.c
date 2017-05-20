/* This was done in Spring 2016 */
/* This was an experiment with using threads */

/* Jacob Chapin, jrc354 */
/* OS programming assignment 2 */
/* This is the threaded version of squared_unthreaded */
/* It runs significantly slower than squared_unthreaded */
/* I believe this to be the result of the thread switching cost */
/* outweighing the benefits of parallelism using threads */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define START_NUMBER 1
#define END_NUMBER 10000
#define THREADCOUNT 8
FILE *f;
long truenum; //use this in case for loop doesn't finish the job
/* Get square of numbers; threads will execute this function */
void* getsquare(void* i)
{
	long num = (long) i;
	fprintf(f, "%lu squared = %lu\n", num, num*num);
	if (num > truenum)
	{
		truenum = num;
	}
	pthread_exit(NULL);
}

int main()
{
	// START: Do not modify anything here
	struct timeval start_time, end_time;
	gettimeofday(&start_time, 0);
	long unsigned i;
	f = fopen("./squared_numbers.txt", "w");
	// END: Do not modify anything here
	pthread_t threads[THREADCOUNT]; //make thread array of length THREADCOUNT
	long status;
	for (i = START_NUMBER; i <= END_NUMBER; i++) //get most of the squared numbers
	{
			status = pthread_create(&threads[i%THREADCOUNT], NULL, getsquare, (void *)i);
			if (status != 0) //error checking/reporting code
			{
				int errorcode = (int) status;
				printf("pthread_create returned error code %d\n", errorcode);
				exit(-1);
			}
	}
	/* This solution is kind of gross but it works */
	if (truenum < END_NUMBER)
	{
		truenum++;
		while (truenum <= END_NUMBER)
		{
			status = pthread_create(&threads[i%THREADCOUNT], NULL, getsquare, (void *)truenum);
			if (status != 0)
			{
				int errorcode = (int) status;
				printf("pthread create returned error code %d\n", errorcode);
				exit(-1);
			}
			truenum++;
		}
	}
	// START: Do not modify anything here
	fclose(f);
	gettimeofday(&end_time, 0);
	float elapsed = (end_time.tv_sec-start_time.tv_sec) * 1000.0f + \
	(end_time.tv_usec-start_time.tv_usec) /1000.0f;
	printf("took %0.2f milliseconds\n", elapsed);
	// END: Do not modify anything here
	for (i=0; i<THREADCOUNT; i++)
	{
		if (pthread_join(threads[i], NULL))
		{
			int errorthread = (int) i;
			printf("Thread %0d failed to join\n", errorthread);
		}
	}
	exit(1);
}
