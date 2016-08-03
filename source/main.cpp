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
MicroBitModuleMatrix matrix(&uBit);

void setup() {
	uBit.init();

	buttons.Init(1);
	motion.Init(2);
	matrix.Init(3);

	dock.AddModule(&buttons);
	dock.AddModule(&motion);
	dock.AddModule(&matrix);
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
