#pragma once
#include <bitset>
#include <fstream>
#include <vector>
#include "root.h"
#include <stdint.h>


namespace Core {
	//утилиты
	namespace Util {
		bool isLittleEndian(uint8_t a);

		void save(const char* file, std::vector<int8_t> buffer);

		void retrivenNsave(ObjectModel::Root* root);
	}   // namespace Util

	// 0x00 0x00 0x00 0000 0101   32 бита = 4 байта   - LE 
    // 0000 0101 0x00 0x00 0x00  -  BE
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value) {
	// 0 1 2 3 
	// Littel endiean 0x00 0x00 0x00 0x5   =     0x00000005
	//Надо в первый элемент вектора записать именно то, что находится в 4 байте (то есть в младшем байте)
	//(*buffer)[(*iterator)++] = value >> 24;  // старший байт
	//(*buffer)[(*iterator)++] = value >> 16;  // третий байт 
	//(*buffer)[(*iterator)++] = value >> 8;   // второй байт
	//(*buffer)[(*iterator)++] = value;        // младший байт - первые 8 бит 
		for (size_t i = 0, j = 0; i < sizeof(T); i++) {
			(*buffer)[(*iterator)++] = (int8_t)(value >> (((sizeof(T) * 8) - 8) - ((i == 0) ? j : j += 8)));
		}
	}
	//inline - чтобы не было множественного определения
	template<>      // явная специализация 
	inline void encode<float>(std::vector<int8_t>* buffer, int16_t* iterator, float value) {
		int32_t result = *(reinterpret_cast<int32_t*>(&value));     // float в указаетль int32_t
		encode<int32_t>(buffer, iterator, result);
	}

	template<>
	inline void encode<double>(std::vector<int8_t>* buffer, int16_t* iterator, double value) {
		int64_t result = *(reinterpret_cast<int64_t*>(&value));
		encode<int64_t>(buffer, iterator, result);
	}

	template<>
	inline void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value) {
		//��� string
		for (size_t i = 0; i < value.size(); i++) {
			encode<int8_t>(buffer, iterator, value[i]);     // decltype typename(value)::value_type - вычислять тип символа динамичсеки
		}
	}

	template<typename T>
	inline void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value) {
		for (size_t i = 0; i < value.size(); i++) {
			encode<T>(buffer, iterator, value[i]); 
		}
	}

} //namespace Core