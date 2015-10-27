/* Consumer Function Source Code: consumerFunction.cpp */

/*	The passed structure has these elements:
*	int		consumeTime;
*	int		numBitesConsumed;
*	int		numSuckersConsumed;
*	string	consumerName; 			
*	sem_t	*MutexPtr;
*	sem_t 	*slotsUsedPtr;
*	sem_t 	*slotsAvailablePtr;
*	sem_t 	*frogControllerPtr;
*	sem_t 	*mainBarrierPtr;
*	belt 	*theBeltPtr;
*/

#include "myFunctions.h"

/* 	Consume function used by Ethel and Lucy thread
	______________________________________________

	- Operates on a consumer structure.
	- Inside the critical section, we use Dequeue and
		printBelt methods (defined in belt.cpp).
	- Runs until consumeCount in belt.cpp reaches 100.

*/
void * consume (void * VoidPointer)
{
	CONSUMER_DATA *DataPtr2 = (CONSUMER_DATA *) VoidPointer;

	int returnInterpret = 0;

	//determining boxing time
	struct timespec BoxingTime;
	BoxingTime.tv_sec = ( (DataPtr2->consumeTime) / MSPERSEC); 
	BoxingTime.tv_nsec = ( (DataPtr2->consumeTime) % MSPERSEC) * NSPERMS; 

		while (true)
		{

		if ( (DataPtr2->theBeltPtr->retConsumeCount()) > 99) 
			break;

			sem_wait(DataPtr2->slotsUsedPtr);									// Slots Used - 1	

				sem_wait(DataPtr2->MutexPtr); 									// critical section entry

					returnInterpret = ( (DataPtr2->theBeltPtr->Dequeue()) );	// Dequeue()
	
					( DataPtr2->theBeltPtr->printBelt() );						// printBelt()

					//if we removed a crunchy frog
					if (returnInterpret == 0)
					{
						sem_post(DataPtr2->frogControllerPtr);					//free up frog slot on belt
						(DataPtr2->numBitesConsumed)++;
						cout << "   " << (DataPtr2->consumerName) << " consumed crunchy frog bite." << endl;
					}
					//if not, we removed a escargot sucker
					else
					{
						(DataPtr2->numSuckersConsumed)++;
						cout << "   " << (DataPtr2->consumerName) << " consumed escargot sucker." << endl;
					}

				sem_post(DataPtr2->MutexPtr); 			//critical section exit

			sem_post(DataPtr2->slotsAvailablePtr); 		//Slots available + 1

			nanosleep (&BoxingTime, NULL); 				//Sleep to simulate boxing the item
		}

		sem_post(DataPtr2->mainBarrierPtr);				//Unblock main function

	return NULL;
}

