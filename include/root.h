#pragma once

#include <string>
#include <vector>

#include <stdint.h>
#include "meta.h"


namespace ObjectModel {

	//----------------------------------------------------------------------------------------------------
	class Root {
	protected:
		std::string name;
		int16_t     nameLength;
		
		int32_t     size;
		int8_t      type;
	public:
		int8_t      wrapper;
		
		Root() :
			name("unknow"),
			wrapper(0),
			nameLength(0),
			size(sizeof(nameLength) + sizeof(wrapper) + sizeof(size)) { }; //protected конструктор - нельзя создавать объект класса из вне.
			// Могут только унаследованные классы совдавать объекты
			// или нужно создать чисто виртуальную фукнцию 
			//virtual void pack() = 0; 
	public:
		inline int32_t  getSize() const { return this->size; };

		void  setName(std::string name) {
			this->name = name;
			nameLength = (int16_t)name.length();
			size += nameLength;
		}

		std::string  getName() const { return this->name; };
		
		virtual void pack(std::vector<int8_t>*, int16_t*) = 0;

	};
}      //namespace ObjectModel
