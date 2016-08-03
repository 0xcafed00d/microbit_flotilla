#ifndef UBIT_FLOTILLA_MODULES_H
#define UBIT_FLOTILLA_MODULES_H

#include <MicroBit.h>
#include "libflotilla/lib_flotilla.h"

class MicroBitModuleMatrix : public ModuleMatrix {
  private:
	MicroBit* m_uBit;

  public:
	MicroBitModuleMatrix(MicroBit* uBit) : m_uBit(uBit) {
	}

	virtual void OnInit() {
		m_uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
		m_uBit->display.scroll("INVADERS!");
	}

  protected:
	virtual void SetMatrix(uint8_t* data, uint8_t brightness) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (data[y] & (1) << x) {
					m_uBit->display.image.setPixelValue(x, y, brightness);
				}
			}
		}
	}
};

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

class MicroBitModuleMotion : public ModuleMotion {
  private:
	MicroBit* m_uBit;

  public:
	MicroBitModuleMotion(MicroBit* uBit) : m_uBit(uBit) {
	}

  protected:
	virtual void GetState(Vector<int16_t>& accel, Vector<int16_t>& mag) {
		accel = Vector<int16_t>{int16_t(m_uBit->accelerometer.getX()),
		                        int16_t(m_uBit->accelerometer.getY()),
		                        int16_t(m_uBit->accelerometer.getZ())};

		mag = Vector<int16_t>{int16_t(m_uBit->compass.getX()), int16_t(m_uBit->compass.getY()),
		                      int16_t(m_uBit->compass.getZ())};
	}
};

#endif