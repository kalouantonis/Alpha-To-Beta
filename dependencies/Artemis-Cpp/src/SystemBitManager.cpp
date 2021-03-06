#include "Artemis/SystemBitManager.h"

namespace artemis {
	int SystemBitManager::POS = 0;
	std::unordered_map< const std::type_info*, std::bitset<BITSIZE>* > SystemBitManager::systemBits;
  
	void SystemBitManager::removeBitSets(){
		std::unordered_map< const std::type_info*, std::bitset<BITSIZE>*>::iterator it;
		
		for(it = systemBits.begin(); it != systemBits.end(); it++)
		{
			delete it->second;
		}
    systemBits.clear();
    POS = 0;
	}
  
	std::bitset<BITSIZE> & SystemBitManager::getBitFor(const std::type_info & type) {
    
		//assert((std::is_base_of< EntitySystem, system >::value == true));
        
		std::bitset<BITSIZE> * bit = systemBits[&type];
    
		if(bit == NULL) {
      
			bit = new std::bitset<BITSIZE>(1);
			(*bit)  <<=  POS++;
      
			systemBits[&type] = bit;
		}
    
		return *bit;
    
	}
}
