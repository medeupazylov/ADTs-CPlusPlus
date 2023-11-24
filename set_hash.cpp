
#include "set.h"

size_t case_insensitive::hash( const std::string& s )
{ 
	size_t hash_value=0;
	size_t c=1;
	for (size_t i = s.length()-1; i>=0; --i) {
		hash_value=hash_value+(tolower(s[i])*c);
		c=c*31;
		if(i==0)
			break;
	}
	return hash_value;
}

bool case_insensitive::equal( const std::string& s1, const std::string& s2 )
{
    if(s1.length()==s2.length()) {
		for (size_t i=0; i<s1.length(); i++) {
			if(tolower(s1[i])!=tolower(s2[i])) {
				return false;
			}
		}
    } else {
        return false;
    }
	return out;
}

bool set::insert_norehash( const std::string& s )
{ 
	size_t h = case_insensitive::hash(s)%buckets.size();
	for (const auto& str : buckets[h]) {
		if(case_insensitive::equal(str, s)) {
			return false;
		}
	}
	buckets[h].push_back(s);
	set_size++;
	return true;
}

void set::consider_rehash( )
{ 
	if ((static_cast<double> (set_size)/buckets.size())>max_load_factor) {
		size_t new_bsize = 8;
		while ((static_cast<double> (set_size)/new_bsize)>max_load_factor) {
			new_bsize*=2;
		}
		size_t old_size = buckets.size();
		std::vector<buckettype> term[new_bsize];
		
		for(size_t i=0; i<old_size; i++ ) {
                      for (auto it=buckets[i].begin(); it !=buckets[i].end(); ++it) {
				size_t h = case_insensitive::hash(*it)%new_bsize;
      				term[h].push_back(*it);			
		      }
		}
		buckets = term;
	}
}

set::set( std::initializer_list< std::string > init, double max_load_factor ): 
	max_load_factor( max_load_factor ),
	set_size(0),
	buckets( std::vector<buckettype> (8))
{ 
	for(const std::string str : init) {
		insert(str);
	}
}

bool set::contains( const std::string& s ) const
{ 
	size_t h = case_insensitive::hash(s)%buckets.size();
        for (const auto& str : buckets[h]) {
                if(case_insensitive::equal(str, s)) {
                        return true;
                }
        }
        return false;

}

bool set::insert( const std::string& s )
{ 
	if(insert_norehash(s)) {
		consider_rehash();
		return true;	
	}
	return false;
}

bool set::remove( const std::string& s )
{ 
	size_t h = case_insensitive::hash(s)%buckets.size();
	for (auto it=buckets[h].begin(); it !=buckets[h].end(); ++it) {
		if(case_insensitive::equal(*it, s)) {
                        buckets[h].erase(it);
			set_size--;
			return true;
                }

	}
	return false;
}

size_t set::size( ) const
{ 
	return set_size;
}

bool set::empty( ) const
{ 
	if(set_size)
		return false;
	else
		return true;
}

void set::clear( )
{ 
	for(size_t i=0; i<buckets.size(); i++) {
		buckets[i].clear();
	}
	set_size=0;
}

void set::print( std::ostream& out ) const
{ 
	for(size_t i=0; i<buckets.size(); i++) {
		out<<"Bucket["<<i<<"]: {";
		size_t j = 0;
		for (const auto& str : buckets[i]) {
			if(j)
				out<<", ";
			out<<str;
			j++;
		}
		out<<"}"<<"\n";
	}
}
