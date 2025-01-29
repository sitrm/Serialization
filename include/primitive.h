#pragma once

#include <stdint.h>
#include <memory>
#include "core.h"
#include "root.h"

namespace ObjectModel {

	class Primitive : public Root {
	private:
		int8_t               type = 0;
		std::vector<int8_t>* data = nullptr;
	private:
		Primitive() {          // этот объект нельзя содать никому, кроме публичных статических методов данного класса
			size += sizeof(type);
		}
	public:
		std::vector<int8_t>* getPtrData() {return data;}


		template<typename T>
		static Primitive* create(std::string name, Type type, T value) {
			// шаблонный чтобы не делать create для каждого типа 
			Primitive* p = new Primitive();
			p->setName(name);
			p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);      //кастим -  приводим к базовому типу int8_t
			p->type = static_cast<int8_t>(type);
			p->data = new std::vector<int8_t>(sizeof(value));   // количество ячеек типо в памяти - размер в байтах
			p->size += (int32_t)p->data->size();                            //добавляем размер!!! 
			//сериализация
			// теперь надо в массив с данными запись int8_t
			int16_t iterator = 0;
			Core::template encode(p->data, &iterator, value);  //указываем что encode тоже template

			return p;
		}

		void pack(std::vector<int8_t>* buffer, int16_t* iterator) {
			Core::encode<std::string>(buffer, iterator, name);
			Core::encode<int16_t>(buffer, iterator, nameLength);
			Core::encode<int8_t>(buffer, iterator, wrapper);
			Core::encode<int8_t>(buffer, iterator, type);
			Core::encode<int8_t>(buffer, iterator, *data);                //разыменовываем весь вектор
			Core::encode<int32_t>(buffer, iterator, size);

		}
	};

}
