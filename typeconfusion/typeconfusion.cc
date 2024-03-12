#include <iostream>
#include <cstdlib>

class Base {};

class Exec: public Base {
  public:
    virtual void exec(const char *prg) {
      system(prg);
    }
};

class Greeter: public Base {
  public:
    virtual void sayHi(const char *str) {
      std::cout << str << std::endl;
    }
};

int main() {
  Base *b1, *b2;
  Greeter *g;

  b1 = new Greeter();
  b2 = new Exec();

  g = static_cast<Greeter*>(b1);
  g->sayHi("Greeter says hi!");

  g = static_cast<Greeter*>(b2);
  g->sayHi("/usr/bin/xcalc");

  delete b1;
  delete b2;
  return 0;
}
