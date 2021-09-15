#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <zmeya.h>

struct Test
{
  uint32_t someVar;
  zm::String name;
  zm::Pointer<Test> ptr;
  zm::Array<zm::String> arr;
  zm::HashMap<zm::String, float> hashMap;
};


TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("No error in parsing the binary fixture.") {
        /* Example snippet:
         *
         * const Test* test = (const Test*)loadBytesFromDisk("basic.zm"); 
         * printf("%s\n", test->name.c_str());
         * for(const zm::String& str : test->arr) printf("%s\n",str.c_str());
         * printf("key = %3.2f\n", test->hashMap.find("key", 0.0f));
         */
        const Test* test = (const Test*)loadBytesFromDisk("examples/basic.zm");  // TODO(sthagen) - minimize platform and location dependency 
        std::ostringstream os;
        os << test->name.c_str();
        SUBCASE("The loaded name is not empty.") {
            REQUIRE(!os.str().empty());
        }
        SUBCASE("The loaded name is correct.") {
            REQUIRE(os.str().find("some name") != std::string::npos);
        }
    }
}
