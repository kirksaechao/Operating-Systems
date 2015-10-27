/* Producer Function Source Code: producerFunction.cpp */

/*	The passed structure has these elements:
*	int 	productIdentifier;		
*	int		produceTime; 			
*	int		producedCounter; 		
*	sem_t	*MutexPtr; 				
*	sem_t 	*slotsUsedPtr; 
*	sem_t 	*slotsAvailablePtr;
*	sem_t 	*frogControllerPtr;
*	belt 	*theBeltPtr;
*/

/* 	Production function used by CrunchyFrog and EscargSucker thread
	_________________________________________________________

	- Operates on a producer structure.
	- Inside the critical section, we use Enqueue and
		printBelt methods (defined in belt.cpp).
	- Runs until productCount in belt.cpp reaches 100.

*/

#include "myFunctions.h"

/* Produce an Crunchy Frog Leg or Escargot Sucker */
void * produce (void * VoidPointer)
{

	PRODUCT_DATA *DataPtr = (PRODUCT_DATA *) VoidPointer;

	//determing production time
	struct timespec CreationTime;
	CreationTime.tv_sec = ( (DataPtr->produceTime) / MSPERSEC); 				// # of seconds
	CreationTime.tv_nsec = ( (DataPtr->produceTime) % MSPERSEC) * NSPERMS; 		// # of nanoseconds


	while (true)
	{
		if ( (DataPtr->theBeltPtr->retProdCount()) > 98) 
			break;

		nanosleep (&CreationTime, NULL); 										//create product

		/* 	Check if this is a frog bite production thread.
		*	If so, do a down on frog controller semaphore.
		*/

		if ( (DataPtr->productIdentifier) == 0)
			sem_wait(DataPtr->frogControllerPtr);

		sem_wait(DataPtr->slotsAvailablePtr); 									// Slots available - 1

			sem_wait(DataPtr->MutexPtr); 										// Entry into critical section

				(DataPtr->producedCounter)++;	
													
				(DataPtr->theBeltPtr->Enqueue ( (DataPtr->productIdentifier) ) );	//Enqueue(productID)

				(DataPtr->theBeltPtr->printBelt() );								//printBelt()

				if ( (DataPtr->productIdentifier) == 0)
					cout << "   Added crunchy frog bite." << endl;
				else
					cout << "   Added escargot sucker." << endl;

			sem_post(DataPtr->MutexPtr); 										//Exit from critical section

		sem_post(DataPtr->slotsUsedPtr); 										// Slots used + 1

	}

	return NULL;
}

