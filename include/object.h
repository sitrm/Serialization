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
		
		
	public:
		//refactor // std::vector<Root*> entities;     // сущность из разных объектов 
		int16_t primitiveCount = 0, arrayCount = 0, stringCount = 0, objectCount = 0;
		std::vector<Primitive> primitives;
		std::vector<Array> arrays;
		std::vector<Array> strings;
		std::vector<Object> objects;


		Object(std::string name = "default") {
			setName(name);
			wrapper = static_cast<int8_t>(Wrapper::OBJECT);
			size += (sizeof(int16_t)) * 4;
		}

		inline int16_t getPrimitiveCount() const  {return this->primitiveCount;}
		inline int16_t getArrayCount()     const  {return this->arrayCount; }
		inline int16_t getStringCount()    const  {return this->stringCount;}
		inline int16_t getObjectCount()    const  {return this->objectCount;}
		std::string getName()       const  {return this->name;       }


		void addEntity(Root* r) {
			switch (r->wrapper)
			{
			case 1: primitives.push_back(*dynamic_cast<Primitive*>(r)); primitiveCount += 1; break;
			case 2: arrays.push_back(*dynamic_cast<Array*>(r));         arrayCount     += 1; break;
			case 3: strings.push_back(*dynamic_cast<Array*>(r));        stringCount    += 1; break;
			case 4: objects.push_back(*dynamic_cast<Object*>(r));       objectCount    += 1; break;
			}

			size += r->getSize();
		}

		Root* findByName(std::string name) {

			for (Primitive p : primitives)
			{
				if (p.getName() == name)
				{
					return dynamic_cast<Root*>(&p);
				}
			}

			for (Array arr : arrays)
			{
				if (arr.getName() == name)
				{
					return dynamic_cast<Root*>(&arr);
				}
			}

			for (Array str : strings)
			{
				if (str.getName() == name)
				{
					return  dynamic_cast<Root*>(&str);
				}
			}

			for (Object o : objects)
			{
				if (o.getName() == name)
				{
					return  dynamic_cast<Root*>(&o);
				}
			}

			std::cout << "no as such" << std::endl;

			return new Object("SYSTEM:empty");        // рофл - индификатор того, что не найден такой объект 
		}

		void pack(std::vector<int8_t>* buffer, int16_t* it) {

			Core::encode<int8_t>(buffer, it, wrapper);
			Core::encode<int16_t>(buffer, it, nameLength);
			Core::encode<std::string>(buffer, it, name);
			
			Core::encode<int16_t>(buffer, it, primitiveCount);
			for (auto p : primitives)
			{
				p.pack(buffer, it);
			}

			Core::encode<int16_t>(buffer, it, arrayCount);
			for (auto arr : arrays)
			{
				arr.pack(buffer, it);
			}

			Core::encode<int16_t>(buffer, it, stringCount);
			for (auto str : strings)
			{
				str.pack(buffer, it);
			}

			Core::encode<int16_t>(buffer, it, objectCount);
			for (auto o : objects)
			{
				o.pack(buffer, it);
			}

			Core::encode<int32_t>(buffer, it, size);
		}

//deserialization-------------------------------------------------

		static Object unpack(std::vector<int8_t>* buffer, int16_t* it){
			Object obj;
		
			obj.wrapper =    Core::decode<int8_t>(buffer, it);
			obj.nameLength = Core::decode<int16_t>(buffer, it);	
			obj.name =       Core::decode<std::string>(buffer, it);
			

			obj.primitiveCount = Core::decode<int16_t>(buffer, it);
			for (int i = 0; i < obj.primitiveCount; i++)
			{
				obj.primitives.push_back(Primitive::unpack(buffer, it));
			}

			obj.arrayCount = Core::decode<int16_t>(buffer, it);
			for (int i = 0; i < obj.arrayCount; i++)
			{
				obj.arrays.push_back(Array::unpack(buffer, it));
			}

			obj.stringCount = Core::decode<int16_t>(buffer, it);
			for (int i = 0; i < obj.stringCount; i++)
			{
				obj.strings.push_back(Array::unpackS(buffer, it));
			}

			obj.objectCount = Core::decode<int16_t>(buffer, it);
			for (int i = 0; i < obj.objectCount; i++)
			{
				obj.objects.push_back(unpack(buffer, it));
			}
			obj.size =       Core::decode<int32_t>(buffer, it);

		}

	};

}