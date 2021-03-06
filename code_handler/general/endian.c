#include "endian.h"
#include <stdint.h>
#include <netinet/in.h>

// Detect whether the system is using big endian byte order
int isBigEndian() {
	union {
		uint32_t integer;
		char character[4];
	} dummyUnion = {0x01000000};

	return dummyUnion.character[0];
}

unsigned int getBigEndian(unsigned int value) {
	if (!isBigEndian()) {
		return htonl(value);
	}

	return value;
}

/*unsigned long long int swap_int64(unsigned long long int val) {
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}*/

unsigned int readRealInteger(const unsigned char *value) {
	return getBigEndian(*(unsigned int *) value);
}

/*unsigned long long int getLong(const unsigned char *value) {
	unsigned long longValue = *(unsigned long *) value;

	if (!isBigEndian()) {
		longValue = swap_int64(longValue);
	}

	return longValue;
}*/

unsigned short readRealShort(const unsigned char *value) {
	unsigned int read = getBigEndian(*(unsigned int *) (value - (sizeof(int) - sizeof(short))));
	read &= 0x0000FFFF;

	return (unsigned short) read;
}

unsigned char readRealByte(const unsigned char *value) {
	unsigned int read = getBigEndian(*(unsigned int *) (value - sizeof(int) - sizeof(char)));
	read &= 0x000000FF;

	return (unsigned char) read;
}

/* Used to get a big endian character pointer to an arbitrary int, short, char */
unsigned char *getCharacterPointer(unsigned int *value, int valueSize) {
	if (!isBigEndian()) {
		*value = htonl(*value);
	}

	unsigned char *characterPointer = (unsigned char *) value;
	characterPointer += sizeof(int) - valueSize;

	return characterPointer;
}