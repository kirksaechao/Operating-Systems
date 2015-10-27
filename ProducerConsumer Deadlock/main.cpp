/*	Main function source code: main.cpp */

/*	Assignment #3 : Consumer and Producer Problem
* 	Kirk Saechao - REDID: 814994434
* 	San Diego State University
* 	CS570 : Operating Systems
*
*	This program simulates the common consumer
*	producer problem.
*
*	STATUS OF PROGRAM:
*	There was only one problem I could not solve.
*	Given zero or little delay, consumer threads will
*	sometimes consume a candy even if there are no
*	candies of that type on the belt; resulting
*	in a negative number.
*
*		This error does not occur when time specified
*		for each argument is larger than 50 milliseconds.
*/


#include "myFunctions.h"

using namespace std;

#define DEFAULT_DELAY 0;

int main(int argc, char *argv[])
{
	extern char *optarg;
	int cmdLineParser;

	/*Belt object is used to simulate the belt.
	*
	* It is an array implementation of a FIFO wrapping queue
	*
	* When belt is declared, an integer array
	* of size ten is created inside.
	*
	* It has two main functions: Enqueue and Dequeue.
	*/

	belt theBelt;

	//Semaphores declaration
	sem_t mutex; 			//mutual exclusion area
	sem_t slotsUsed; 		//tracks number of items on belt
	sem_t slotsAvailable; 	//tracks number of empty slots on belt
	sem_t mainBarrier; 		//barrier to stop main function -- incremented in consumerFunction
	sem_t frogController;	//limits frogs on belt to 3

	/* Declare threads */
	pthread_t prodCrunchyFrog;
	pthread_t prodEscargSucker;
	pthread_t consumeEthel;
	pthread_t consumeLucy;
	
	/*Declare Data structures*/
	/*Strucutre elements defined in myFunctions.h*/
	PRODUCT_DATA frogBitesData; //productIdentifier = 0
	PRODUCT_DATA escargotData; // product ident = 1
	CONSUMER_DATA lucyData;
	CONSUMER_DATA ethelData;

	/*  Inside consume/produce functions
	* 	and our integer array..
	*	0 = crunchy frog bites
	*	1 = escargot suckers
	*/


	//initialize frogBitesData Struct Parameters
	frogBitesData.productIdentifier = 0;
	frogBitesData.MutexPtr = &mutex;
	frogBitesData.slotsUsedPtr = &slotsUsed;
	frogBitesData.slotsAvailablePtr = &slotsAvailable;
	frogBitesData.frogControllerPtr = &frogController;
	frogBitesData.produceTime = DEFAULT_DELAY;
	frogBitesData.theBeltPtr = &theBelt;
	frogBitesData.producedCounter = 0;

	//initialize escargotData Struct Parameters
	escargotData.productIdentifier = 1;
	escargotData.MutexPtr = &mutex;
	escargotData.slotsUsedPtr = &slotsUsed;
	escargotData.slotsAvailablePtr = &slotsAvailable;
	escargotData.produceTime = DEFAULT_DELAY;
	escargotData.theBeltPtr = &theBelt;
	escargotData.producedCounter = 0;

	//initialize lucyData Struct Parameters
	lucyData.consumerName = "Lucy";
	lucyData.MutexPtr = &mutex;
	lucyData.slotsUsedPtr = &slotsUsed;
	lucyData.slotsAvailablePtr = &slotsAvailable;
	lucyData.frogControllerPtr = &frogController;
	lucyData.mainBarrierPtr = &mainBarrier;
	lucyData.consumeTime = DEFAULT_DELAY;
	lucyData.theBeltPtr = &theBelt;
	lucyData.numBitesConsumed = 0;
	lucyData.numSuckersConsumed = 0;

	//initialize ethelData Struct Parameters
	ethelData.consumerName = "Ethel";
	ethelData.MutexPtr = &mutex;
	ethelData.slotsUsedPtr = &slotsUsed;
	ethelData.slotsAvailablePtr = &slotsAvailable;
	ethelData.frogControllerPtr = &frogController;
	ethelData.mainBarrierPtr = &mainBarrier;
	ethelData.consumeTime = DEFAULT_DELAY;
	ethelData.theBeltPtr = &theBelt;
	ethelData.numBitesConsumed = 0;
	ethelData.numSuckersConsumed = 0;


	//parsing command line for arguments
		while ( (cmdLineParser = getopt(argc, argv, "E:L:f:e:")) != -1)
		{
			switch (cmdLineParser)
			{
			case 'E':
				ethelData.consumeTime = atoi(optarg);
				break;
			case 'L':
				lucyData.consumeTime = atoi(optarg);
				break;
			case 'f':
				frogBitesData.produceTime = atoi(optarg);
				break;
			case 'e':
				escargotData.produceTime = atoi(optarg);
				break;
			}
		}

	//creating semaphores
	if (sem_init(&mutex,0,1) == -1)
	{
		cout << "Could not create semaphore" << endl;
	}

	if (sem_init(&slotsUsed,0,0) == -1)
	{
		cout << "Could not create semaphore" << endl;
	}

	if (sem_init(&slotsAvailable,0,10) == -1)
	{
		cout << "Could not create semaphore" << endl;
	}

	if (sem_init(&mainBarrier,0,0) == -1)
	{
		cout << "Could not create semaphore" << endl;
	}

	if (sem_init(&frogController,0,3) == -1)
	{
		cout << "Could not create semaphore" << endl;
	}


	//create threads
	if (pthread_create(&prodCrunchyFrog, NULL, produce, &frogBitesData))
		cout << "Could not create Crunchy Frog Legs thread" << endl;

	if (pthread_create(&prodEscargSucker, NULL, produce, &escargotData))
		cout << "Could not create Escargot Sucker thread" << endl;

	if (pthread_create(&consumeEthel, NULL, consume, &ethelData))
		cout << "Could not create Ethel thread" << endl;

	if (pthread_create(&consumeLucy, NULL, consume, &lucyData))
		cout << "Could not create Lucy thread" << endl;

	//wait for threads to finish

	sem_wait(&mainBarrier);  //semaphore incremented in consumerFunction.cpp

	//PRODUCTION REPORT OUTPUT

	cout << endl << "PRODUCTION REPORT" << endl;
	cout << "---------------------------------------" << endl;

	cout << "Crunchy Frog Bite Producer generated " << frogBitesData.producedCounter
		 << " candies" << endl;

	cout << "Escargot Sucker Producer generated " << escargotData.producedCounter
		 << " candies" << endl;

	cout << "Lucy consumed " <<  lucyData.numBitesConsumed << " crunchy frog bites + "
		 << lucyData.numSuckersConsumed << " escargot suckers = " <<
		 ((lucyData.numBitesConsumed) + (lucyData.numSuckersConsumed)) << endl;

	cout << "Ethel consumed " <<  ethelData.numBitesConsumed << " crunchy frog bites + "
		 << ethelData.numSuckersConsumed << " escargot suckers = " <<
		 ((ethelData.numBitesConsumed) + (ethelData.numSuckersConsumed)) << endl;

	return 0;
}

