#ifndef UBIT_FLOTILLA_MODULES_H
#define UBIT_FLOTILLA_MODULES_H

#include <MicroBit.h>
#include "libflotilla/lib_flotilla.h"

class MicroBitModuleButtons : public ModuleTouch {
  private:
	MicroBit* m_uBit;

  public:
	MicroBitModuleButtons(MicroBit* uBit) : m_uBit(uBit) {
	}

  protected:
	virtual uint8_t GetState() {
		uint8_t state = 0;

		if (m_uBit->buttonA.isPressed())
			state |= 1;

		if (m_uBit->buttonB.isPressed())
			state |= 2;

		return state;
	}
};

#endif