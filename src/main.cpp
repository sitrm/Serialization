#include "../include/serialization.h"
#include <iostream>
using namespace ObjectModel;

int main(int argc, char** argv)
{	uint8_t a = 5;
	assert(Core::Util::isLittleEndian(a));  // провекра на LittleEndian


#if 1
	// test PRIMITIVE data type 
	int32_t foo = 5;
	//std::cout << (foo >> 24) << std::endl;
	//std::cout << (foo >> 16) << std::endl;
	//std::cout << (foo >> 8) << std::endl;
	//std::cout << (foo) << std::endl; 
	//std::cout << std::bitset<8>((foo >> 24)).to_string() << std::endl;
	//std::cout << std::bitset<8>((foo >> 16)).to_string() << std::endl;
	//std::cout << std::bitset<8>((foo >> 8)).to_string() << std::endl;
	//std::cout << std::bitset<8>(foo).to_string() << std::endl;
	Primitive* p = Primitive::create("int32", Type::I32, foo);
	Core::Util::retrivenNsave(p);

	//test ARRAY
	std::vector<int64_t> data{ 1, 2, 3, 4 };
	Array* arr = Array::createArray("array", Type::I64, data);
	Core::Util::retrivenNsave(arr);

	//test STRING
	std::string name = "name";
	Array* str = Array::createString("string", Type::I8, name);
	Core::Util::retrivenNsave(str);

	// test OBJECT
	Object Test("Test");
	Test.addEntity(p);
	Test.addEntity(arr);
	Test.addEntity(str);

	Object Test2("Test2");
	Test2.addEntity(p);
	Core::Util::retrivenNsave(&Test2);

	Test.addEntity(&Test2);
	Core::Util::retrivenNsave(&Test);
	//-----------------------------------------

#endif

//deserialization 
#if 1
	int16_t f = 23;
	Primitive* p = Primitive::create("int16", Type::I16, f);
	Core::Util::retrivenNsave(p);

	std::vector<int8_t> result = Core::Util::load("D:/studies/VScode_project/Serialization/build/Debug/int16.ttc");

	Primitive pp = Primitive::unpack(&result);
	std::cout <<"------" <<pp.getName() << std::endl;
	std::cout << pp.getSize() << std::endl;
	


#endif

	(void)argc;
	(void)argv;

	return 0;
}