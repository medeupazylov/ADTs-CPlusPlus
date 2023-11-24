#include <stdexcept>
#include "queue.h"


queue::queue( ) :
	queue_size(0),
	front(nullptr),
	back(nullptr)
{
}

queue::queue( const queue& q ) :
	queue_size(0),
	front(nullptr),
	back(nullptr)
{
	node *term = q.front;
	push(term->value);
	front = back;
	term=term->next;
	while(term) {
		push(term->value);
		term=term->next;
	}
}

const queue& queue::operator = ( const queue& q ) {
	if (!(front==q.front && queue_size==q.queue_size)) {
		clear();
		node *term = q.front;
		push(term->value);
       		front = back;
        	term=term->next;
        	while(term) {
                	push(term->value);
                	term=term->next;
        	}
	}
	return *this;
}

queue::~queue( ) {
	clear();
}

queue::queue( std::initializer_list< std::string > init ) : 
        queue_size(0),
        front(nullptr),
        back(nullptr)
{
	size_t i=0;
	for (std::string val : init) {
		if (i==0) {
			node* cur = new node(val);
			back = cur;
			front = cur;
			queue_size++;
			i++;
		} else {
			push(val);
		}
	}
}

void queue::push( const std::string& s ) {
	node* cur = new node(s);
	if (back)
	back->next = cur;
	back = cur;
	queue_size++;
}

void queue::pop( ) {
	if (queue_size==0)
		throw std::runtime_error( "peek: stack is empty" );
	node *term = front;
	front=front->next;
	delete term;
	queue_size--;
}

void queue::clear( ) {
	node *cur = front;
	front = nullptr;
	back = nullptr;
	while(cur) {
		node *to_delete = cur;
		cur=cur->next;
		delete to_delete;
	}
	queue_size=0;
}

void queue::reset( size_t s ) {
	if (s>queue_size) {
		throw std::runtime_error( "reset: the new size is qreater than queue size" );
	}
	while (s!=queue_size) {
		pop();
	}
}

const std::string& queue::peek( ) const {
	if (queue_size==0) 
		throw std::runtime_error( "peek: queue is empty" );
	return front->value;
}

size_t queue::size( ) const {
	return queue_size;
}

bool queue::empty( ) const {
	if (queue_size==0) 
		return true;
	else
		return false;
}

void queue::print( std::ostream& out ) const {
	node* cur = front;
	size_t i=0;
	while (cur) {
		if (i>0) {
                        out << ", ";
                }
		out<<cur->value;
		cur=cur->next;
		i++;
	}
}


