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
		Primitive() {         // ���� ������ ������ ������ ������, ����� ��������� ����������� ������� ������� ������
			size += sizeof(type);
		}
	public:

		template<typename T>
		static Primitive* create(std::string name, Type type, T value) {
			// ��������� ����� �� ������ create ��� ������� ���� 
			Primitive* p = new Primitive();
			p->setName(name);
			p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);     //������ -  �������� � �������� ���� int8_t
			p->type = static_cast<int8_t>(type);
			p->data = new std::vector<int8_t>(sizeof(value));   // ���������� ����� ���� � ������ - ������ � ������
			p->size += p->data->size();
			//������������
			// ������ ���� � ������ � ������� ������ int8_t
			int16_t iterator = 0;
			Core::template encode(p->data, &iterator, value);  //��������� ��� encode ���� template

			return p;
		}

		void pack(std::vector<int8_t>* buffer, int16_t* iterator) {
			Core::encode<std::string>(buffer, iterator, name);
			Core::encode<int16_t>(buffer, iterator, nameLength);
			Core::encode<int8_t>(buffer, iterator, wrapper);
			Core::encode<int8_t>(buffer, iterator, type);
			Core::encode<int8_t>(buffer, iterator, *data); //�������������� ���� ������
			Core::encode<int32_t>(buffer, iterator, size);

		}
	};

}
