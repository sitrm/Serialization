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
		int32_t count = 0; // ��� �� ��������� 
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
			arr->wrapper = static_cast<int8_t>(Wrapper::ARRAY);     //������ -  �������� � �������� ���� int8_t
			arr->type = static_cast<int8_t>(type);
			arr->count = (int32_t)value.size();
			arr->data = new std::vector<int8_t>(arr->count * sizeof(T));   // ���������� ����� ���� � ������ - ������ � ������
			arr->size += (int32_t)arr->count * sizeof(T);                          //��������� ������!!!
			//������������
			// ������ ���� � ������ � ������� ������ int8_t
			int16_t iterator = 0;
			Core::template encode<T>(arr->data, &iterator, value);  //��������� ��� encode ���� template

			return arr;
		}

		template<typename T>
		static Array* createString(std::string name, Type type, T value) {
			Array* str = new Array();
			str->setName(name);
			str->wrapper = static_cast<int8_t>(Wrapper::STRING);     //������ -  �������� � �������� ���� int8_t
			str->type = static_cast<int8_t>(type);
			str->count = (int32_t)value.size();
			str->data = new std::vector<int8_t>(value.size());   // ���������� ����� ���� � ������ - ������ � ������
			str->size += (int32_t)value.size();                          //��������� ������!!!
			//������������
			// ������ ���� � ������ � ������� ������ int8_t
			int16_t iterator = 0;
			Core::template encode<T>(str->data, &iterator, value);  //��������� ��� encode ���� template

			return str;
		}

		void pack(std::vector<int8_t>* buffer, int16_t* iterator) {
			Core::encode<std::string>(buffer, iterator, name);
			Core::encode<int16_t>(buffer, iterator, nameLength);
			Core::encode<int8_t>(buffer, iterator, wrapper);
			Core::encode<int8_t>(buffer, iterator, type);
			Core::encode<int32_t>(buffer, iterator, count);
			Core::encode<int8_t>(buffer, iterator, *data);     //�������������� ���� ������
			Core::encode<int32_t>(buffer, iterator, size);
		}

	}; // class Array
} // namespace ObjectMOdel