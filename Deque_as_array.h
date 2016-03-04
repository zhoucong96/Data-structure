#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * UW User ID:  c46zhou
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 ******************************************/

#include "Exception.h"
#include <iostream>


class Deque_as_array {
	private:
		int array_size;
		int*array;
		int ihead;
		int itail;
		int count;

	public:
		Deque_as_array( int = 10 );
		~Deque_as_array();

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		bool full() const;
		int capacity() const;

		void enqueue_head( int const & );
		void enqueue_tail( int const & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
		int modulus(int, int) const;
		int operator[]( int ) const;
		void print();


};

 
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ), 
array( new int[array_size] ), 
count( 0 ), 
ihead( 0 ),                    // We need to initiate itail and ihead since it won't exist if we don't initiate them
itail( 0 ){
	// empty
}

 
Deque_as_array::~Deque_as_array() {
	// Deallocate the memory location assigned to the array
	delete[] array;
}

 
int Deque_as_array::size() const {
	// It's simply the number of elements we added which is just the count value
	return count;
}

 
int Deque_as_array::capacity() const {
	// It returns the capacity of the array which is the size of array we created.
	//this value is fixed once we create the array
	return array_size;
}

 
bool Deque_as_array::empty() const {
	// if the array size is 0 then it's empty
	return (size() == 0);
}

bool Deque_as_array::full() const {
	// if the array size is 0 then it's empty
	// according to the algorithm the tail is the next availble sapce so there is always one empty slot
	return (size() == capacity());
} 

int Deque_as_array::head() const {
	// return head value
	if(empty()){
		throw underflow();
	}
	return array[modulus(ihead, capacity())];     // we need modulus so that it's circular
}

 
int Deque_as_array::tail() const {
	// return tail value
	if(empty()){
		throw underflow();
	}
	return array[modulus(itail-1, capacity())];   
}


void Deque_as_array::enqueue_head( int const &obj ) {
	if(full()){
		throw overflow();
	}
	if(empty()){
		array[modulus(ihead, capacity())] = obj;    //if empty we make it to be ihead to head and itail to
		itail ++;									//next availbable space
		count ++;
	}
	else if((ihead - 1) % capacity() != itail-1){   //this accounts for other cases. we allow ihead = itail
		ihead = modulus((ihead - 1) , capacity());
		array[ihead] = obj;
		count ++;
	}
}


void Deque_as_array::enqueue_tail( int const &obj ) {
	if(full()){
		throw overflow();
	}
	if(empty()){
		array[modulus(ihead, capacity())] = obj;     //same as above for the implementation
		itail ++;
		count ++;
	}
	else if((ihead - 1) % capacity() != itail-1){
		array[itail] = obj;
		itail = modulus((itail + 1) , capacity());
		count ++;
	}
}

 
int Deque_as_array::dequeue_head() {
	int tmp;
	if(empty()){
		throw underflow();
	}
	tmp = array[modulus((ihead) , capacity())];     //tmp placeholder for return value
	array[modulus(ihead,capacity())] = 0;			//make it 0. however we don't need to care about it since
	ihead = modulus((ihead + 1) , capacity());		//we just need to lose the reference
	count --;

	return tmp;     // This returns the value we deleted
}

 
int Deque_as_array::dequeue_tail() {
	int tmp;
	if(empty()){
		throw underflow();
	}
	tmp = array[modulus((itail - 1) , capacity())];  //same as above for return value
	array[modulus(itail-1, capacity())] = 0;
	itail = modulus((itail - 1) , capacity());
	count --;
	
	return tmp; 
}

 
void Deque_as_array::clear() {
	// abondon the reference and thus initiate a new deque
	ihead = 0;
	itail = 0;
	count = 0;
}

int Deque_as_array::modulus (int a, int n) const   //self-defined modulus function to get -1mod10 = 9
{
	int result = 0;
	result = a%n;
	if(result < 0){
		result += n;
	}
	return result;
}
int Deque_as_array::operator[]( int n ) const {    //overload [] to access the value in the queue
	return array[n];
}

void Deque_as_array::print() {
	if (!empty()){
		for (int i = 0; i < count; i++){
			std::cout << array[modulus(ihead + i, capacity())] << std::endl;
		}
	}
}
// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
