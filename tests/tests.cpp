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