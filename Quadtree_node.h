#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * UW User ID:  c46zhou
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"
using namespace std;

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );
        ~Quadtree_node();

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

template <typename T>
Quadtree_node<T>::~Quadtree_node() {            //recursively call clear to do the delete. Linaer operation O(n)
    north_east -> clear();
    north_west -> clear();
    south_east -> clear();
    south_west -> clear();
}

template <typename T>
T Quadtree_node<T>::retrieve_x() const {                       
	return x_value;
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

template <typename T>
T Quadtree_node<T>::min_x() const {                             //recursively call itself to go to the leave
	// you may use std::min                                     //O(n)
    if(north_west == 0 && south_west == 0){
        return x_value;
    }
    if (north_west == 0 || south_west == 0) {                   //check which direction has last node.
        if(north_west != 0){
            return north_west->min_x();
        }
        else if(south_west != 0){
            return south_west->min_x();
        }
        return x_value;
    }
    if (x_value < min(north_west->min_x(),south_west->min_x())) {       //compare the value of current node and min
        return x_value;
    }
    if (north_west->retrieve_x() < south_west->retrieve_x()) {
        return north_west->retrieve_x();
    }
    else{
        return south_west->retrieve_x();
    }
}

template <typename T>
T Quadtree_node<T>::min_y() const {
	// you may use std::min
    if (south_east == 0 && south_west == 0) {
        return y_value;
    }
    if (south_east == 0 || south_west == 0) {
        if(south_east != 0){
            return south_east->min_y();
        }
        else if(south_west != 0){
            return south_west->min_y();
        }
        return y_value;
    }
    if (y_value < min(south_east->min_y(),south_west->min_y())) {
        return y_value;
    }
    if (south_east->retrieve_y() < south_west->retrieve_y()) {
        return south_east->retrieve_y();
    }
    else{
        return south_west->retrieve_y();
    }
}

template <typename T>
T Quadtree_node<T>::max_x() const {
	// you may use std::max
    if (south_east == 0 && north_east == 0) {
        return x_value;
    }
    if (south_east == 0 || north_east == 0) {
        if(south_east != 0){
            return south_east->max_x();
        }
        else if(north_east != 0){
            return north_east->max_x();
        }
        return x_value;
    }
    if (x_value > max(south_east->max_x(),north_east->max_x())) {
        return x_value;
    }
    if (north_east->retrieve_x() > south_east->retrieve_x()) {
        return north_east->retrieve_x();
    }
    else{
        return south_east->retrieve_x();
    }
}

template <typename T>
T Quadtree_node<T>::max_y() const {
	// you may use std::max
    if (north_east == 0 && north_west == 0) {
        return y_value;
    }
    if (north_east == 0 || north_west == 0) {
        if(north_east != 0){
            return north_east->max_y();
        }
        else if(north_west != 0){
            return north_west->max_y();
        }
        return y_value;
    }
    if (y_value > max(north_east->max_y(),north_west->max_y())) {
        return y_value;
    }
    if (north_west->retrieve_y() < north_east->retrieve_y()) {
        return north_east->retrieve_y();
    }
    else{
        return north_west->retrieve_y();
    }
}

template <typename T>                       //Linaer operation O(n)
T Quadtree_node<T>::sum_x() const {
    T sum = 0;
	if ( this == 0) {
		// hint... if empty, it returns 0 which means we have got to the last node.
        return 0;
    }
    
    else {
        //recursively sum the value and the value of current node. Linear operation. O(n)
        sum += x_value + north_east->sum_x() + north_west->sum_x() + south_east->sum_x() + south_west->sum_x();
        return sum;
	}
}

template <typename T>
T Quadtree_node<T>::sum_y() const {
    T sum = 0;
	if ( this == 0 ) {
		// hint...
        return 0;
    }
    else {
        sum =+ y_value + north_east->sum_y() + north_west->sum_y() + south_east->sum_y() + south_west->sum_y();
        return sum;
    }
}

template <typename T>               //compare each value to the value we check, if no do recursion until we find it.O(n)
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0) {
        return false;
    }
    if (x == x_value && y == y_value) {
        return true;
    }
    else if (x >= x_value && y >= y_value){
        return north_east->member(x, y);
    }
    else if (x < x_value && y >= y_value){
        return north_west->member(x, y);
    }
    else if (x >= x_value && y < y_value){
        return south_east->member(x, y);
    }
    else if (x < x_value && y < y_value){
        return south_west->member(x, y);
    }
    return false;
}

template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {          //recursively call to insert until it's done. O(n)
    if (member(x, y)) {                                         //avoid duplicated node
        return false;
    }
    if (x >= x_value && y >= y_value) {                         //create new node based on the quadtree rule
        if (north_east == 0) {
            north_east = new Quadtree_node<T>(x,y);
            return true;
        }
        else{
            north_east->insert(x, y);
        }
    }
    else if (x >= x_value && y < y_value) {
        if (south_east == 0) {
            south_east = new Quadtree_node<T>(x,y);
            return true;
        }
        else{
            south_east->insert(x, y);
        }
    }
    else if (x < x_value && y >= y_value) {
        if (north_west == 0) {
            north_west = new Quadtree_node<T>(x,y);
            return true;
        }
        else{
            north_west->insert(x, y);
        }
    }
    else if (x < x_value && y < y_value) {
        if (south_west == 0) {
            south_west = new Quadtree_node<T>(x,y);
            return true;
        }
        else{
            south_west->insert(x, y);
        }
    }
    return false;
}

template <typename T>
void Quadtree_node<T>::clear() {            //recursively delete the node calling it.O(n)
    if(this != 0){
        north_west->clear();
        north_west = 0;
        north_east->clear();
        north_east = 0;
        south_west->clear();
        south_west = 0;
        south_east->clear();
        south_east = 0;
        delete this;
    }
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
