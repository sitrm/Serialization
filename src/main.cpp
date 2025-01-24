#include "../include/serialization.h"

using namespace ObjectModel;

int main(int argc, char** argv)
{
	assert(Core::Util::isLittleEndian());


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
	Test.addEntitie(p);
	Test.addEntitie(arr);
	Test.addEntitie(str);

	Object Test2("Test2");
	Test2.addEntitie(p);
	Core::Util::retrivenNsave(&Test2);

	Test.addEntitie(&Test2);
	Core::Util::retrivenNsave(&Test);
#endif

// Test EventSystem
#if 0
	System Foo("Foo");
	Event* e = new KeybourdEvent('a', true, false);          


	Foo.addEvent(e);
	KeybourdEvent* kb = static_cast<KeybourdEvent*>(Foo.getEvent());         


	(void)argc;
	(void)argv;
#endif
	return 0;
}