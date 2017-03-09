#ifndef __BITMAP_H__
#define __BITMAP_H__


#define LONG_BYTES_SHIFT (sizeof(long) >> 3 ? 3 : 2)
#define BYTE_SHIFT_BITS	3
#define LONG_BITS_SHIFT (LONG_BYTES_SHIFT + BYTE_SHIFT_BITS)
#define LONG_ALIGN(x)	((x >> LONG_BYTES_SHIFT) << LONG_BYTES_SHIFT == x)


int test_bit(unsigned long *bitmap, int size, int bit);
int set_bit(unsigned long *bitmap, int size, int bit);
int clear_bit(unsigned long *bitmap, int size, int bit);
int count_free(unsigned long *bitmap, int size);

#endif
