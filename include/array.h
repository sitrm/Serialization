#pragma once
#include "root.h"
#include "meta.h"
#include "core.h"
#include <memory>
#include <stdint.h>

namespace ObjectModel {

	class Array : public Root {
	private:
		int8_t type = 0;
		int32_t count = 0;   // кол во элементов 
		std::vector<int8_t>* data = nullptr;
	private:
		Array() {
			size += sizeof(type) + sizeof(count);
		}
	public:
		template<typename T>
		static Array* createArray(std::string name, Type type, std::vector<T> value) {
			Array* arr = new Array();
			arr->setName(name);
			arr->wrapper = static_cast<int8_t>(Wrapper::ARRAY);     
			arr->type = static_cast<int8_t>(type);
			arr->count = (int32_t)value.size();
			arr->data = new std::vector<int8_t>(arr->count * sizeof(T));   
			arr->size += (int32_t)arr->count * sizeof(T);                      
		
			
			int16_t iterator = 0;
			Core::template encode<T>(arr->data, &iterator, value);

			return arr;
		}

		template<typename T>
		static Array* createString(std::string name, Type type, T value) {
			Array* str = new Array();
			str->setName(name);
			str->wrapper = static_cast<int8_t>(Wrapper::STRING); 
			str->type = static_cast<int8_t>(type);
			str->count = (int32_t)value.size();
			str->data = new std::vector<int8_t>(value.size());  
			str->size += (int32_t)value.size();                 
			
			
			int16_t iterator = 0;
			Core::template encode<T>(str->data, &iterator, value); 

			return str;
		}

		void pack(std::vector<int8_t>* buffer, int16_t* iterator) {
			Core::encode<std::string>(buffer, iterator, name);
			Core::encode<int16_t>(buffer, iterator, nameLength);
			Core::encode<int8_t>(buffer, iterator, wrapper);
			Core::encode<int8_t>(buffer, iterator, type);
			Core::encode<int32_t>(buffer, iterator, count);
			Core::encode<int8_t>(buffer, iterator, *data);     
			Core::encode<int32_t>(buffer, iterator, size);
		}

		Array unpack(std::vector<int8_t>* buffer, int16_t* it){
			Array arr;
			arr.wrapper = Core::decode<int8_t>(buffer, it);
			arr.nameLength = Core::decode<int16_t>(buffer, it);
			arr.name = Core::decode<std::string>(buffer, it);
			arr.type = Core::decode<int8_t>(buffer, it);
			arr.count = Core::decode<int32_t>(buffer, it);
			arr.data = new std::vector<int8_t>(getTypeSize((Type)arr.type) * count);
			Core::decode(buffer, it, arr.data);
			arr.size = Core::decode<int32_t>(buffer, it);

			return arr;
		}

		Array unpackS(std::vector<int8_t>* buffer, int16_t* it)
		{
			Array str;
			str.wrapper = Core::decode<int8_t>(buffer, it);
			str.nameLength = Core::decode<int16_t>(buffer, it);
			str.name = Core::decode<std::string>(buffer, it);
			str.type = Core::decode<int8_t>(buffer, it);
			str.count = Core::decode<int32_t>(buffer, it);
			str.data = new std::vector<int8_t>(str.count);
			Core::decode(buffer, it, str.data);
			str.size = Core::decode<int32_t>(buffer, it);


			return str;
		}

	}; // class Array

} // namespace ObjectMOdel