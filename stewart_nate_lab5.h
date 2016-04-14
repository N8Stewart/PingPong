/*
 * Name: Nate Steawrt
 * Date: 04-19-16
 * Header file to hold all constants and function prototypes 
 */

// Number of times the message transfer should occur
#define NUM_ITERATIONS 1000000

#define RANDOM_VALUE_MIN 1.0
#define RANDOM_VALUE_MAX 4.0

/*
 * Process the ping interaction NUM_ITERATIONS number of times.
 * Send and receive buffer[0:bufferSize) between the two processes.
 * Supply rank to determine which process to send to.
 * Output the bandwidth and time achieved using 'outputStats' function
 */
void ping(int rank, double *buffer, int bufferSize);

/* 
 * Output the stats to the console for the specific run
 * param 'time' is how long the interaction took
 * param 'bandwidth' represents how much data was sent over the interface during the interaction
 * param 'bufferSize' allows the output to specify which test was just run
 */
void outputStats(double time, double bandwidth, int bufferSize);

/*
 * Seed the buffer with random double values
 */
void seed(double *buffer, int bufferSize);

