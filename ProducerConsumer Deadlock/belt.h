/* Belt Class Header File: Belt.h */

#ifndef MY_BELT_CLASS
#define MY_BELT_CLASS

using namespace std;

class belt
{

	public:

		belt(); 						//creates a belt of size 10;
		~belt();
		void Enqueue( int prodIdent ); 	//add item to queue
		int  Dequeue( void ); 			//remove item from queue
		void printBelt( void );		 	//prints status of belt
		int  retProdCount( void );		//returns product counter
		int  retConsumeCount( void );	//returns consumed counter

	protected:

		int head; 				//index removal point
		int tail; 				//index of insertion point
		int frogsOnBelt;		//current number of frogs on belt
		int escargotsOnBelt;	//current number of escargots on belt
		int productCount; 		//total number of productions
		int consumeCount;		//total number of consumes
		int myBelt[];
		int productHolder;

};

#endif

