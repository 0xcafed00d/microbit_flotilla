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
MicroBitModuleMatrix matrix(&uBit, true);
MicroBitModuleLight light(&uBit);
MicroBitModuleWeather temp(&uBit);

void setup() {
	uBit.init();

	dock.AddModule(&buttons);
	dock.AddModule(&motion);
	dock.AddModule(&matrix);
	dock.AddModule(&light);
	dock.AddModule(&temp);
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
