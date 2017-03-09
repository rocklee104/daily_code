#include <stdio.h>
#include <assert.h>
#include "bitmap.h"
//#include "common.h"

#if 0
#define LONG_BYTES_SHIFT (sizeof(long) >> 3 ? 3 : 2)
#define BYTE_SHIFT_BITS	3
#define LONG_BITS_SHIFT (LONG_BYTES_SHIFT + BYTE_SHIFT_BITS)
#define LONG_ALIGN(x)	((x >> LONG_BYTES_SHIFT) << LONG_BYTES_SHIFT == x)
#endif

#if 0
#define d_line()			printf("func %s, line %d\n", __func__, __LINE__)
#define debug(fmt, ...) 	printf("func %s, line %d "fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define d_line()			do {}while(0)
#define debug(fmt, ...)		do {}while(0)
#endif

static const int nibblemap[] = {4, 3, 3, 2, 3, 2, 2, 1, 3, 2, 2, 1, 2, 1, 1, 0};

void dump_bitmap(unsigned long *bitmap, int size)
{
	int i;
	for (i = 0; i < size; i++)
		debug("bitmap[%d] %lu\n", i, bitmap[i]);
}

int test_bit(unsigned long *bitmap, int size, int bit)
{
	int index;

	if(bit < 0 || bit >= (size << LONG_BITS_SHIFT)) {
		debug("bit out of range[%d,%d].\n", bit, size << LONG_BYTES_SHIFT);
		return -1;
	}

	index = bit >> LONG_BITS_SHIFT;
	bit %= 1 << LONG_BITS_SHIFT;

	if (bitmap[index] & ((unsigned long)1 << bit))
		return 1;
	else
		return 0;
}

int set_bit(unsigned long *bitmap, int size, int bit)
{
	int index;
	int bit_set;

	bit_set = test_bit(bitmap, size, bit);
	assert(bit_set != -1);

	if(bit_set == 1) {
		debug("bit %d has been set.\n", bit);
		return 0;
	}

	index = bit >> LONG_BITS_SHIFT;
	bit %= sizeof(unsigned long) << BYTE_SHIFT_BITS;

	/* be careful to deal with unsigned */
	*(bitmap + index) = bitmap[index] | 1UL << bit;
	//dump_bitmap(bitmap, size);

	return 1;
}

int clear_bit(unsigned long *bitmap, int size, int bit)
{
	int index;
	int bit_set;

	bit_set = test_bit(bitmap, size, bit);
	assert(bit_set != -1);

	if(bit_set == 0) {
		debug("bit %d has been cleared.\n", bit);
		return 0;
	}

	index = bit >> LONG_BITS_SHIFT;
	bit %= sizeof(unsigned long) << BYTE_SHIFT_BITS;

	*(bitmap + index) = bitmap[index] & ~(1UL << bit);
	return 1;
}

int count_free(unsigned long *bitmap, int size)
{
	int i ,j;
	int count = 0;

	for(i = 0; i < size; i++) {
		char *map = (char *)(bitmap + i);

		for (j = 0; j < sizeof(unsigned long); j++) {
			count += nibblemap[map[j] & 0xf];
			count += nibblemap[map[j] >> 4 & 0xf];
		}
	}

	return count;
}
