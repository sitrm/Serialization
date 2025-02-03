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

		static Object unpack(std::vector<int8_t>* buffer, int16_t* it){
			Object obj;

			
			
			obj.name = Core::decode<std::string>(buffer, it);
			obj.nameLength = Core::decode<int16_t>(buffer, it);	
			obj.wrapper = Core::decode<int8_t>(buffer, it);
			obj.count = Core::decode<int16_t>(buffer, it);

			// for(auto e : entities){
			// 	e.entities.push_back(e.unpack(buffer, it))
			// }
			obj.size = Core::decode<int32_t>(buffer, it);

		}


		std::string getName() const { return this->name; }
	};

}