#pragma once
#include <iostream>
#include <stdint.h>
#include "primitive.h"
#include "array.h"
#include "core.h"
#include "root.h"

namespace ObjectModel {

	class Object : public Root {
	private:
		std::vector<Root*> entities;     // сущность из разных объектов 
		int16_t count = 0;
	public:

		Object(std::string name = "default") {
			setName(name);
			wrapper = static_cast<int8_t>(Wrapper::OBJECT);
			size += sizeof(count);
		}

		void addEntity(Root* r) {
			this->entities.push_back(r);
			count += 1;
			size += r->getSize();
		}

		Root* findByName(std::string name) {
			for (auto r : entities) {
				if (r->getName() == name) {
					return r;
				}
			}
			std::cout << "no as such" << std::endl;
			return new Object("ninja");          // рофл - индификатор того, что не найден такой объект 
		}

		void pack(std::vector<int8_t>* buffer, int16_t* iterator) {
			Core::encode<std::string>(buffer, iterator, name);
			Core::encode<int16_t>(buffer, iterator, nameLength);
			Core::encode<int8_t>(buffer, iterator, wrapper);
			Core::encode<int16_t>(buffer, iterator, count);

			for (Root* r : entities) {
				r->pack(buffer, iterator);
			}
			Core::encode<int32_t>(buffer, iterator, size);
		}
		std::string getName() const { return this->name; }
	};

}