#include <zmeya.h>

struct Test
{
  uint32_t someVar;
  zm::String name;
  zm::Pointer<Test> ptr;
  zm::Array<zm::String> arr;
  zm::HashMap<zm::String, float> hashMap;
};

int main()
{
   // load binary file to memory (using fread, mmap, etc)
   // no parsing/decoding needed
   const Test* test = (const Test*)loadBytesFromDisk("basic.zm");  
   
   // use your loaded data
   printf("%s\n", test->name.c_str());
   for(const zm::String& str : test->arr)
   {
     printf("%s\n",str.c_str());
   }
   printf("key = %3.2f\n", test->hashMap.find("key", 0.0f));
   return 0;
}
