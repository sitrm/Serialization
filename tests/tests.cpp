#include "../include/serialization.h"
#include <gtest/gtest.h>
#include "gmock/gmock.h"


using ::testing::StartsWith;

//  тест с именем primitive, который принадлежит тестовому набору Core
TEST(Core, primitive)
{
    using namespace ObjectModel;

    uint8_t a = 5;
    int32_t foo = 150;
    Primitive* p = Primitive::create("int32", Type::I32, foo);

    int16_t it = 0;
    std::vector<int8_t> buffer(p->getSize());
    p->pack(&buffer, &it);
    std::string str(buffer.begin(), buffer.end());


    EXPECT_TRUE(Core::Util::isLittleEndian(a)) << "Something bad with endianess";
    // не nullptr
    EXPECT_NE(p->getPtrData(), nullptr);

   // EXPECT_THAT(str, StartsWith("\0\x5\x1"));
    // макрос првоеряет совпадают ли имена 
    EXPECT_STREQ("int32", p->getName().c_str());
    // проверка размеры 
    EXPECT_EQ(17, p->getSize());
}


TEST(Core, object)
{
    using namespace ObjectModel;

    int32_t foo = 231;
    Primitive* p = Primitive::create("int32", Type::I32, foo);
    int64_t bar = 1;
    Primitive* p2 = Primitive::create("int64", Type::I64, bar);

    std::vector<int16_t> data{5,10,15,20};
    Array* arr = Array::createArray("ArrayOfInt16", Type::I16, data);

    std::string name = "wndtn";
    Array* str = Array::createString("String", Type::I8, name);

    Object obj("Foo");

    obj.addEntity(p);
    obj.addEntity(p2);
    obj.addEntity(arr);
    obj.addEntity(str);
    
    Object obj2("Bar");
    obj2.addEntity(&obj);

    Core::Util::retrivenNsave(&obj2);

    EXPECT_STREQ("Foo",  obj.getName().c_str());
    EXPECT_STREQ("Bar",  obj2.getName().c_str());
    // можно ещё тестов навалить
}


TEST(Core, primitiveDecode)
{
    using namespace ObjectModel;

    int16_t f = 23;
    Primitive* p = Primitive::create("int16", Type::I16, f);
    Core::Util::retrivenNsave(p);

    std::vector<int8_t> result = Core::Util::load("int16.ttc");

    std::cout << "Unpacking data..." << std::endl;
    Primitive pp = Primitive::unpack(&result);

    // Check that the pointer is not nullptr
    std::cout << "Checking pointer..." << std::endl;
    EXPECT_NE(pp.getPtrData(), nullptr) << "Pointer pp.getPtrData() is nullptr!";

    // Check that the name matches "int16"
    std::cout << "Checking name..." << std::endl;
    EXPECT_STREQ("int16", pp.getName().c_str()) << "Name does not match expected value 'int16'. Actual name: " << pp.getName();

    // Check the size
    std::cout << "Checking size..." << std::endl;
    EXPECT_EQ(15, pp.getSize()) << "Size does not match expected value 15. Actual size: " << pp.getSize();
}


TEST(Core, ArrayDecode)
{
    using namespace ObjectModel;

    std::vector<int32_t> data{ 1, 2, 3, 4 };
    Array* arr = Array::createArray("array32", Type::I32, data);
    Core::Util::retrivenNsave(arr);

    std::vector<int8_t> result = Core::Util::load("array32.ttc");

    int16_t it = 0;
    Array ar = Array::unpack(&result, &it);

    EXPECT_STREQ("array32", ar.getName().c_str()) << "Name does not match expected value 'int16'. Actual name: " << ar.getName();

    EXPECT_EQ(35, ar.getSize()) << "Size does not match expected value 15. Actual size: " << ar.getSize();
}

TEST(Core, StringDecode)
{
    using namespace ObjectModel;

    std::string name = "name";
	Array* str = Array::createString("string8", Type::I8, name);
	Core::Util::retrivenNsave(str);

    std::vector<int8_t> result = Core::Util::load("string8.ttc");

    int16_t it = 0;
    Array ar = Array::unpackS(&result, &it);

   
    EXPECT_STREQ("string8", ar.getName().c_str()) << "Name does not match expected value 'int16'. Actual name: " << ar.getName();

    EXPECT_EQ(23, ar.getSize()) << "Size does not match expected value 15. Actual size: " << ar.getSize();
}
