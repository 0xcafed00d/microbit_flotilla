#include <MicroBit.h>
#include "libflotilla/lib_flotilla.h"

MicroBit uBit;
Dock dock(0, 0);

void setup() {
	uBit.init();
}

void loop() {
}

int main() {
	setup();
	while (true) {
		loop();
	}
}
