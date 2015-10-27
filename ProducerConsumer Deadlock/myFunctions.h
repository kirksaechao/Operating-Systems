/* Main Header File: myFunctions.h */

#ifndef MY_FUNCTIONS_INCLUDED
#define MY_FUNCTIONS_INCLUDED

#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string>
#include "belt.h"

#define NSPERMS 1000000
#define MSPERSEC 1000
	
using namespace std;

	void * produce (void * VoidPointer);
	void * consume (void * VoidPointer);

/* Structure for production threads */
typedef struct
{
	int 	productIdentifier;		//0 = frog bite -- 1 = escargot sucker
	int		produceTime; 			//time needed for production
	int		producedCounter; 		//number of items produced by thread
	sem_t	*MutexPtr; 				
	sem_t 	*slotsUsedPtr; 
	sem_t 	*slotsAvailablePtr;
	sem_t 	*frogControllerPtr;
	belt 	*theBeltPtr;

}PRODUCT_DATA;

/* Structure for consuming threads */
typedef struct
{
	string	consumerName; 			//is ethel or lucy consuming
	int		consumeTime;
	int		numBitesConsumed;
	int		numSuckersConsumed;
	sem_t	*MutexPtr;
	sem_t 	*slotsUsedPtr;
	sem_t 	*slotsAvailablePtr;
	sem_t 	*frogControllerPtr;
	sem_t 	*mainBarrierPtr;
	belt 	*theBeltPtr;

}CONSUMER_DATA;

#endif
