 
#include "stack.h"

void stack::ensure_capacity( size_t c ) {
	if (c>current_capacity) {
                size_t new_size=1;
		while (new_size<c) {
                        new_size=new_size*2;
                }
                double *new_data(new double[new_size]);
                std::copy(data, data+current_size, new_data);
                delete[] data;
		data=new_data;
		current_capacity = new_size;
        }
}

   // Keep current_capacity always in powers of two.

stack::stack( ) :
	current_size(0),
	current_capacity(4),
	data(new double[4])
{
}
   // Constructs empty stack. 

stack::stack( const stack& s ) :
	current_size(s.current_size),
	current_capacity(s.current_capacity),
	data(new double[s.current_capacity])
{
	std::copy(s.data,s.data+s.current_size, data);
}
   // use std::copy

const stack& stack::operator = ( const stack& s ) {
	ensure_capacity(s.current_size);
	std::copy(s.data, (s.data+s.current_size), data);
	current_size=s.current_size;
	return *this;
}
   // use ensure_capacity and std::copy. 

stack::~stack( ) {
	delete[] data;
}

void stack::push( double d ) {
	ensure_capacity(current_size+1);
	data[current_size]=d;
	current_size++;
}

  
stack::stack( std::initializer_list< double > init ) :
	current_size(0),
        current_capacity(init.size()),
        data(new double[init.size()])

{
	for (size_t val : init) {
		push(val);
	}	
}	
   // 1. either use push( ), or 
   // 2. ensure_capacity.
  
void stack::pop( ) {
	if (current_size==0)
		throw std::runtime_error( "pop: stack is empty" );
	--current_size;
}	

void stack::clear( ) {
	current_size=0;
}	

void stack::reset( size_t s ) {
	current_size=s;
}

double stack::peek( ) const {
	if (current_size==0) 
		throw std::runtime_error( "peek: stack is empty" );
	return data[current_size-1];
}	

size_t stack::size( ) const {
	return current_size;
}

bool stack::empty( ) const {
	if (current_size==0)
		return true;
	else 
		return false;
}

void stack::print( std::ostream& out ) const {
	out << "stack: ";
        for (size_t i=0; i < current_size; ++i) {
                if (i>0) {
                        out << ", ";
                }
                out << data[i];
        }
}
   // make sure that printing is correct and commas are put properly
   // between the stack elements. Make sure to print into out and not
   // std::cout. 


