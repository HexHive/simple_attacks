#include <iostream>
#include <cstdlib>

class Base {
  public:
    int i;
    virtual void sayHi(const char *str) {
      std::cout << "Boring Base:" << str << std::endl;
    }

    virtual ~Base() {}
};

class Greeter: public Base {
  public:
    virtual void sayHi(const char *str) {
      std::cout << "Exciting Greeter: " << str << std::endl;
    }
};

int main() {
  Base *b;
  Greeter *g;

  b = new Greeter();

  asm("nop; nop; nop; nop;");
  g = static_cast<Greeter*>(b);
  asm("nop; nop; nop; nop;");
  g = dynamic_cast<Greeter*>(b);
  asm("nop; nop; nop; nop;");

  b->sayHi("Super!");
  g->sayHi("Super!");

  delete b;
  return 0;
}
