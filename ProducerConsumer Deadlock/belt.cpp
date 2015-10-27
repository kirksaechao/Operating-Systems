/* Belt Class Source Code: Belt.cpp */

/* 	DESCRIPTION
	__________________

	Belt Class is used to take care of simulating the belt.
	producerFunction calls Enqueue to add to queue.
	consumerFunction calls Dequeue to remove from queue.

*/
#include "myFunctions.h"

//default constructor
belt::belt(void)
{
	int myBelt[10]; 
	head = 0;
	tail = 0;
	frogsOnBelt = 0;
	escargotsOnBelt = 0;
	productCount = 0;
	consumeCount = 0;
	productHolder = 0;
}

//deconstructor
belt::~belt(void) {};

//Add an item into queue
void belt::Enqueue( int prodIdent )
{
	if ( prodIdent == 0)
		frogsOnBelt++;
	else
		escargotsOnBelt++;

	myBelt[tail % 10] = prodIdent;
	tail++;

	productCount++;
}

//Remove an item from queue
int  belt::Dequeue( void )
{
	productHolder = myBelt[head % 10];	
	head++;

	if ( productHolder == 0 )
		frogsOnBelt--;
	else
		escargotsOnBelt--;

	consumeCount++;

	return productHolder;	//returns 0 or 1
}


//Print state of belt
void belt::printBelt( void )
{
	cout << "Belt: " << frogsOnBelt << " frogs + " << escargotsOnBelt << " escargots = " <<
			(frogsOnBelt + escargotsOnBelt) << ". ";

	cout << "produced: " << productCount;
}

int belt::retProdCount( void )
{
	return productCount;
}

int belt::retConsumeCount( void )
{
	return consumeCount;
}


