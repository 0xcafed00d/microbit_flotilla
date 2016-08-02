#include <MicroBit.h>
#include "libflotilla/lib_flotilla.h"
#include "ubitinterfaces.h"
#include "ubitmodules.h"

MicroBit uBit;
MicroBitTimerUtil timerUtil(&uBit);
MicroBitSerialStream serialstream(&uBit);
MicroBitPersistantStore store(&uBit);

Dock dock(&timerUtil, &store);

MicroBitModuleButtons buttons(&uBit);
MicroBitModuleMotion motion(&uBit);

void setup() {
	uBit.init();

	buttons.Init(1);
	motion.Init(2);

	dock.AddModule(&buttons);
	//	dock.AddModule(&motion);
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
