#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  c46zhou
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
        bool full() const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
        int modulus(int ,int ) const;
        int operator[]( int ) const;
        bool odd(int) const;
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),                    // << m is used to left shift the binary number by m digits which is 2^m
array( new T [array_size] ),
array_state( new state[array_size] ) {      //state array is attached to hashtable

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;              //Assign all elements in state array to be EMPTY in status
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete[] array;                       //deallocate the memory
    delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;                           //simply return count O(1)
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;                      //simply return the capacity  O(1)
}


template<typename T >
bool DoubleHashTable<T >::empty() const {
    return count == 0;                      //if not count then it means empty  O(1)
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int index = static_cast<int>(modulus(obj, capacity()));         //primary hash function
	return index;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    int index = static_cast<int>(modulus(obj/capacity(), capacity()));      //secondary hash function
    if (!odd(index)) {
        index++;
    }
	return index;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {             //similar to inseetion to find the index. end if repeated
    if(empty()){
        return false;
    }
    int probe = h1(obj);
    int offset = h2(obj);
    while (array_state[probe] != EMPTY) {
        if (array[probe] == obj && array_state[probe] == OCCUPIED) {
            return true;
        }
        probe = static_cast<int>(modulus((probe+offset),capacity()));
        if(probe == h1(obj))
        {
            return false;
        }
    }
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    if (array_state[n] == OCCUPIED) {
        return array[n];                    //It return the value if it's filled. otherwise unpredicatable O(1)
    }
	return NULL;
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    if (full()) {
        throw overflow();
    }
    if(!member(obj)){
        int probe = h1(obj);
        int offset = h2(obj);
        while (array_state[probe] == OCCUPIED) {       //It is implemented to be able to insert when slot is deleted
            probe = static_cast<int>(modulus((probe+offset),capacity()));
        }
        array[probe] = obj;
        count++;
        array_state[probe] = OCCUPIED;
    }
}

template<typename T >                                       //same way to find the index and remove only if it's a member
bool DoubleHashTable<T >::remove( T const &obj ) {
    if (empty()) {
        throw underflow();
    }
    if (member(obj)) {
        int probe = h1(obj);
        int offset = h2(obj);
        while (array_state[probe] != EMPTY) {
            if (array[probe] == obj && array_state[probe] == OCCUPIED) {
                array[probe] = NULL;
                count --;
                array_state[probe] = DELETED;
            }
            probe = static_cast<int>(modulus((probe+offset),capacity()));
        }
        return true;
    }
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    count = 0;                                  //abandon reference
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = DELETED;              //Re-assign all elements to be DELETED in status O(M)
    }
}

template<typename T >
void DoubleHashTable<T >::print() const {
    for (int i = 0; i < capacity(); i++) {
        if (array_state[i] == OCCUPIED) {
            cout<< array[i] <<endl;
        }
        else if(array_state[i] == DELETED)
        {
            cout<<"Deleted"<<endl;
        }
        else if(array_state[i] == EMPTY)
        {
            cout<<"Empty"<<endl;
        }
    }
}

template<typename T >
int DoubleHashTable<T >::modulus(int a, int b) const {
    int result = a % b;
    if(result < 0){
        result += b;
    }
    return result;
}

template<typename T >
int DoubleHashTable<T >::operator[]( int n ) const {    //overload [] to access the value in the hashtable
    return array[n];
}

template<typename T >
bool DoubleHashTable<T >::odd(int value) const {
    return value%2 != 0;
}

template<typename T >
bool DoubleHashTable<T >::full() const {
    return count==capacity();
}

#endif
