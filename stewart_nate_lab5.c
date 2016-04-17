/*
 * Name: Nate Steawrt
 * Date: 04-19-16
 * Description: Implementation of Ping Pong using MVAPICH2 
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#include "stewart_nate_lab5.h"

int main(int argc, char **argv) {
	
	int rank, size;

	// Set up MPI processes and grab rank/size
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Exit if the user supplied invalid number of processes
	if (size != 2) {
		if (rank == 0) // Only output the warning message once
			printf("Ping pong is a 2 process program. Only supply two processes using '-np 2'\n");
		return -1;
	}

	// Create and seed a buffer
	double *buffer = malloc(sizeof(*buffer) * 2048);
	seed(buffer, 2048);

	// Complete the 5 ping interactions
	ping(rank, buffer, 32);
	ping(rank, buffer, 256);
	ping(rank, buffer, 512);
	ping(rank, buffer, 1024);
	ping(rank, buffer, 2048);
	
	// Finalize, free, and return
	MPI_Finalize();
	free(buffer);
	return 0;

}

void ping(int senderRank, double *buffer, int bufferSize) {

	int i;
	int receiverRank = (senderRank + 1) % 2; // Calculate the rank of the receiver
	int messageSend = senderRank, messageRcv = receiverRank;
	MPI_Status status;
	double runtime, timePerMessage, bandwidth;
	clock_t clockTime;
	
	// Block until both threads are ready to transact
	MPI_Barrier(MPI_COMM_WORLD);

	// Start timer and run through all iterations
	clockTime = clock();
	for (i = 0; i < NUM_ITERATIONS; i++) {
		MPI_Send(buffer, bufferSize, MPI_DOUBLE, receiverRank, messageSend, MPI_COMM_WORLD);
		MPI_Recv(buffer, bufferSize, MPI_DOUBLE, receiverRank, messageRcv, MPI_COMM_WORLD, &status);
		MPI_Send(buffer, bufferSize, MPI_DOUBLE, receiverRank, messageSend + 2, MPI_COMM_WORLD);
		MPI_Recv(buffer, bufferSize, MPI_DOUBLE, receiverRank, messageRcv + 2, MPI_COMM_WORLD, &status);
	}
	
	// Stop timer and calculate runtime/bandwidth
	clockTime = clock() - clockTime;
	runtime = clockTime * 1.0 / 1000000;
	timePerMessage = runtime / (4.0 * NUM_ITERATIONS);
	bandwidth = sizeof(*buffer) * bufferSize / timePerMessage;

	// Output results to console if rank is 0
	if (senderRank == 0)
		outputStats(runtime, bandwidth, bufferSize);
}

void outputStats(double runtime, double bandwidth, int bufferSize) {
	printf("*****************************************\n");
	printf("Test             :\t%d\n", bufferSize);
	printf("Runtime (clock)  :\t%.5lf seconds\n", runtime);
	printf("Bandwidth        :\t%.5lf\n bytes/sec", bandwidth);
	printf("*****************************************\n");
}

void seed(double *buffer, int bufferSize) {
	int i;
	double range = RANDOM_VALUE_MAX - RANDOM_VALUE_MIN;
	double dist = RAND_MAX / range;
	for (i = 0; i < bufferSize; i++) {
		buffer[i] = RANDOM_VALUE_MIN + (rand() / dist);
	}
}

