#include <loki/SmartPtr.h>

class Foo
{
public:
   friend class Loki::DefaultSPStorage<Foo>;
   static Foo* create();
private:

   Foo()
      : f1(0), f2(1), f3(2)
   {}
   unsigned int f1;
   unsigned int f2;
   unsigned int f3;
};

Foo*
Foo::create()
{
   return new Foo();
}

typedef Loki::SmartPtrDef<Foo>::type FooPtr;

int main(int argc, char* argv[])
{
   FooPtr fp = Foo::create();
   FooPtr fpp;
   fpp = fp;
   return 0;
}
