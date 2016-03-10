#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * UW User ID:  c46zhou
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;                //tree_root is the address of the pair(x0,y0)
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

template <typename T>
Quadtree<T>::~Quadtree() {
    delete tree_root;
}

template <typename T>
int Quadtree<T>::size() const {                                      //simply return the count which indicates size. O(1)
	return count;
}

template <typename T>
bool Quadtree<T>::empty() const {                                    //simply check the size.O(1)
	return count == 0;
}

template <typename T>
T Quadtree<T>::min_x() const {
    if(empty()){
        throw underflow();
    }
    return tree_root->min_x();                                    //root is a pointer. it calls min_x method in root node
}

template <typename T>
T Quadtree<T>::min_y() const {
    if (empty()) {
        throw underflow();
    }
    return tree_root->min_y();
}

template <typename T>
T Quadtree<T>::max_x() const {
    if (empty()) {
        throw underflow();
    }
    return tree_root->max_x();
}

template <typename T>
T Quadtree<T>::max_y() const {
    if (empty()) {
        throw underflow();
    }
    return tree_root->max_y();
}

template <typename T>
T Quadtree<T>::sum_x() const {
    if (empty()) {
        return 0;
    }
    return tree_root->sum_x();
}

template <typename T>
T Quadtree<T>::sum_y() const {
    if (empty()) {
        return 0;
    }
    return tree_root->sum_y();
}

template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
    if (empty()) {
        return 0;
    }
	return tree_root;
}

template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
    if (empty()) {
        return false;
    }
    return tree_root->member(x, y);                      //call member function inside node. use & to get value in x and y
}

template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {    //if no tree is initiated, we create root.
    if (tree_root == 0) {
        tree_root = new Quadtree_node<T>(x,y);
        count++;
    }
    else{
        if(tree_root->insert(x, y)){                    //we use recursion to go to the leave to cretae new tree node
            count++;
        }
    }
}

template <typename T>
void Quadtree<T>::clear() {
    tree_root->clear();
    count = 0;
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
