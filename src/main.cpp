#include <MicroBit.h>

MicroBit uBit;

int main() {
  uBit.init();

  uBit.display.scroll("HELLO WORLD!");

  release_fiber();
}
