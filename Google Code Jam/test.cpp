#include <assert.h>
#include <map>
#include <limits>
#include <iostream>
	
template<class K, class V>
class interval_map {
    friend void IntervalMapTest();

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.begin(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    };

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, const V& val ) {
		
		if (!(keyBegin < keyEnd)) return;
		
		
		auto lowerIter_ = m_map.lower_bound(keyBegin);
		auto upperIter_ = m_map.lower_bound(keyEnd-1);
		
		if(lowerIter_ == m_map.end()) lowerIter_--;
		if(upperIter_ == m_map.end()) upperIter_--;
		
		while(lowerIter_->first > keyBegin)
			lowerIter_--;
		
		while(upperIter_->first > (keyEnd-1))
			upperIter_--;
		
		auto priorVal = lowerIter_->second;
		auto lastVal = upperIter_->second;
		auto lastKey = upperIter_->first;
	
		//std::cout << lowerIter_->first<< " " <<  lowerIter_->second << " " << upperIter_->first << " " << upperIter_->second << std::endl;
	
		bool addFront = false;
		bool addLast = false;
		if(priorVal != val) 
			addFront = true;
		
		if(lastVal != val)
			addLast = true;
		
		
		if(addFront) {
			if(m_map.size() == 1)
				m_map.insert({keyEnd, m_map.begin()->second});
			
			auto it = m_map.find(keyBegin);
			if(it != m_map.end()) m_map.erase(it);
			lowerIter_ = m_map.lower_bound(keyBegin);
			upperIter_ = m_map.lower_bound(keyEnd);
			m_map.erase(lowerIter_, upperIter_);
			
			m_map.insert({keyBegin, val});
		}
	
		if(addLast){
			lowerIter_ = m_map.lower_bound(keyBegin);
			lowerIter_++;
			upperIter_ = m_map.lower_bound(keyEnd);
			m_map.erase(lowerIter_, upperIter_);
			
			m_map.insert({keyEnd, lastVal});
		}
		
		if(m_map.size() != 1){
			auto it = m_map.find(keyEnd);
			
			while(it!= m_map.end() && it->second == val ){
				it = m_map.erase(it);
			}
		}
		
		if(m_map.size() != 1){
			auto it = m_map.find(keyBegin-1);
			it--;
			while( it!= m_map.end() && it->second == val){
				it = m_map.erase(it);
			}
		}
		
    }

	void printit(){
		std::cout << "=====================================" <<std::endl;
	
		for(auto &c: m_map)
			std::cout << c.first << "-->" << c.second << std::endl;
	
		std::cout << "=====================================" <<std::endl;
	}
	
	
	
    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

void IntervalMapTest(){

	interval_map<int,char> m('A');
	for(int i=0; i<5; i++){
		int start, end;
		char ch;
		std::cin >> start >> end >> ch;
		m.assign(start, end, ch);
		m.printit();
	}
	
	
}
int main(int argc, char* argv[]) {

    IntervalMapTest();	
    return 0;
}
