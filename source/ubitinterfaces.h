#ifndef UBIT_FLOTILLA_INTERFACES_H
#define UBIT_FLOTILLA_INTERFACES_H

#include <MicroBit.h>

struct MicroBitSerialStream : public SerialStream {
	MicroBit* m_uBit;

	MicroBitSerialStream(MicroBit* uBit) : m_uBit(uBit) {
	}

	virtual bool available() {
		return (bool)m_uBit->serial.isReadable();
	}

	virtual int read() {
		int c = m_uBit->serial.read(ASYNC);
		if (c == MICROBIT_NO_DATA)
			c = -1;
		return c;
	}

	virtual void write(int c) {
		m_uBit->serial.sendChar((char)c, SYNC_SPINWAIT);
	}

	virtual void print(int v) {
		char buf[8];
		itoa(v, buf);
		print((const char*)buf);
	}

	virtual void print(const char* s) {
		while (*s) {
			write(*s++);
		}
	}
};

struct MicroBitTimerUtil : public TimerUtil {
	MicroBit* m_uBit;

	MicroBitTimerUtil(MicroBit* uBit) : m_uBit(uBit) {
	}

	virtual TimeOut make(uint32_t timeout) {
		return TimeOut{(uint32_t)m_uBit->systemTime() + timeout};
	}
	virtual bool hasTimedOut(TimeOut& t) {
		return m_uBit->systemTime() > t.end;
	}
};

static const char* namesKey = "FlotillaNames";

struct MicroBitPersistantStore : public PersistantStore {
	MicroBit* m_uBit;

	MicroBitPersistantStore(MicroBit* uBit) : m_uBit(uBit) {
	}

	virtual void writeBlock(void* data, int offset, size_t len) {
		KeyValuePair* p = m_uBit->storage.get(namesKey);
		if (!p) {
			p = new KeyValuePair;
			memset(p->value, '*', MICROBIT_STORAGE_VALUE_SIZE);
		}
		memcpy(p->value + offset, data, len);
		m_uBit->storage.put(namesKey, p->value, MICROBIT_STORAGE_VALUE_SIZE);
		delete p;
	}

	virtual void readBlock(void* data, int offset, size_t len) {
		KeyValuePair* p = m_uBit->storage.get(namesKey);
		if (p) {
			memcpy(data, p->value + offset, len);
			delete p;
		} else {
			memset(data, '*', len);
		}
	}
};

#endif
