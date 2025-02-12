#include "object.h"
#include "core.h"



namespace ObjectModel {

	void Object::addEntity(Root* r) {
		switch (r->wrapper)
		{
		case 1: primitives.push_back(*dynamic_cast<Primitive*>(r)); primitiveCount += 1; break;
		case 2: arrays.push_back(*dynamic_cast<Array*>(r));         arrayCount += 1; break;
		case 3: strings.push_back(*dynamic_cast<Array*>(r));        stringCount += 1; break;
		case 4: objects.push_back(*dynamic_cast<Object*>(r));       objectCount += 1; break;
		}

		size += r->getSize();
	}
	//----------------------------------------------------------------------------------------------
	Root* Object::findByName(std::string name) {
    
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

		return new Object("SYSTEM:empty");  
	}
	//----------------------------------------------------------------------------------------------
	void Object::pack(std::vector<int8_t>* buffer, int16_t* it) {

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
	
	//----------------------------------------------------------------------------------------------
	Object Object::unpack(std::vector<int8_t>* buffer, int16_t* it) {
		Object obj;

		obj.wrapper = Core::decode<int8_t>(buffer, it);
		obj.nameLength = Core::decode<int16_t>(buffer, it);
		obj.name = Core::decode<std::string>(buffer, it);


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
		obj.size = Core::decode<int32_t>(buffer, it);
		return obj;
	}
	//----------------------------------------------------------------------------------------------
	

} // namespace ObjectModel