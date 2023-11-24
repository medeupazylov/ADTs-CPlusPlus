
#include "set.h"

const treenode* find( const treenode* n, const std::string& s )
{
  while (n != nullptr){
    if (s > n->value){
      n = n->right;
    }else if (s < n->value){
      n = n->left;
    }else{
      return n;
    }
  }
  return nullptr;
}

treenode** find( treenode** n, const std::string& s ) {
  while (*n){
    if (s > (*n)->value){
      n = &((*n)->right);
    }else if (s < (*n)->value){
      n = &((*n)->left);
    }else{
      return n;
    }
  }
  return n;
}

size_t size( const treenode* n )
{
  if (!n){
    return 0;
  }
    return 1 + size(n->left) + size(n->right);
}

size_t height( const treenode* n )
{
 if (!n){
   return 0;
 }
   return (1 + (height (n->left) > height (n->right) ? height (n->left) : height (n->right)));
}

void deallocate( treenode* n )
{
  if (!n){
    return;
  }
  while(n){
    deallocate (n->left);
    treenode *node_to_delete = n;
    n = n->right;
    delete node_to_delete;
  }
}

treenode* makecopy( const treenode* n ) 
{
  if (!n){
    return nullptr;
  }
  treenode* node_copy = new treenode(n->value);
  node_copy->left = makecopy(n->left);
  node_copy->right = makecopy(n->right);
  return node_copy;
}


void print( std::ostream& out, const treenode* n, unsigned int indent )
{
   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> value ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const std::string* lowerbound, 
                   const std::string* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> value )
      {
         std::cout << "value " << ( n -> value );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" ); 
      }

      if( upperbound && n -> value >= *upperbound )
      {
         std::cout << "value " << ( n -> value );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );  
      }

      checkbetween( n -> left, lowerbound, &( n -> value ));
      lowerbound = & ( n -> value );
      n = n -> right;
   }
} 


unsigned int log_base2( size_t s )
{
  size_t power = 0;
  while (s != 1){
    s /= 2;
    power++;
  }
  return power;
}

bool set::contains( const std::string& s ) const
{
  if ((find (tr, s)) == nullptr) {
    return false;
  }else{
    return true;
  }
}


bool set::insert( const std::string& s )
{
  treenode **place_for_n = find(&tr, s);
  if (!(*place_for_n)){
    *place_for_n = new treenode (s);
    (*place_for_n)->left = nullptr;
    (*place_for_n)->right = nullptr;
    return true;
  }else{
    return false;
  }
}

size_t set::size( ) const
{
  return ::size(this->tr);
}

size_t set::height( ) const
{
  return ::height (this->tr);
}

bool set::empty( ) const
{
  if (!tr){
    return true;
  }else{
    return false;
  }
}

set:: ~set( )
{
  deallocate (this->tr);
}

void set::clear( )
{
  deallocate (this->tr);
  tr = nullptr;
}

set::set( const set& other )
{
  tr = nullptr;
  tr = makecopy (other.tr);
}


set& set::operator = ( const set& other )
{
  if (this->tr == other.tr){
    
  }else{
    deallocate (this->tr);
    tr = makecopy (other.tr);
  }
  return *this;
}



void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


void set::print( std::ostream& out, unsigned int indent ) const
{
   ::print( out, tr, indent );
}

