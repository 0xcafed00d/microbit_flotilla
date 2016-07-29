#include <MicroBit.h>
#include "libflotilla/lib_flotilla.h"
#include "ubitinterfaces.h"

MicroBit uBit;
MicroBitTimerUtil timerUtil(&uBit);
MicroBitSerialStream serialstream(&uBit);
MicroBitPersistantStore store(&uBit);

Dock dock(&timerUtil, &store);

void setup() {
	uBit.init();
}

void loop() {
	dock.Update(&serialstream);
	dock.ProcessInput(&serialstream);
	uBit.sleep(50);
}

int main() {
	setup();
	while (true) {
		loop();
	}
}
