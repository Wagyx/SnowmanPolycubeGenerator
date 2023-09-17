#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "bitsFormat.h"
#include "network_sort.h"

void bitsformat_write_header(OutputStream *stream, uint8_t compressed)
{
}

size_t bitsformat_pack(Key key, char *buffer)
{
	Point lDims = key_get_dimensions(key);
	buffer[0] = POINT_GET_X(lDims);
	buffer[1] = POINT_GET_Y(lDims);

	size_t lLength = (size_t)buffer[0] * (size_t)buffer[1];
	size_t lBytesLength = 2 + (lLength % 8 == 0 ? lLength / 8 : lLength / 8 + 1);

	for (uint8_t i = 0; i < key.length; ++i)
	{
		size_t x = (size_t)POINT_GET_X(key.data[i]) - 1;
		size_t y = (size_t)POINT_GET_Y(key.data[i]) - 1;
		size_t ind = y + (size_t)buffer[1] * x;
		buffer[(ind / 8) + 2] |= (1 << (ind - 8 * (ind / 8)));
	}
	return lBytesLength;
}

void bitsformat_write_keys(OutputStream *stream, Key *keys, uint64_t count)
{
	for (uint64_t i = 0; i < count; i++)
	{
		bitsformat_write_key(stream, keys[i]);
	}
}

void bitsformat_write_key(OutputStream *stream, Key key)
{
	Point lDims = key_get_dimensions(key);
	uint8_t dim[2];
	dim[0] = POINT_GET_X(lDims);
	dim[1] = POINT_GET_Y(lDims);
	output_stream_write(stream, dim, 2);

	uint16_t offsets[2];
	offsets[0] = dim[1];
	offsets[1] = 1;

	// zero padding on the ceil bytes
	uint16_t bits = dim[0] * dim[1];
	uint8_t bytes = bits >> 3;
	bytes += bits > (bytes << 3);
	uint8_t data[bytes];
	memset(data, 0, bytes);

	// Accounts for the base (1,1,1) base point
	uint16_t base_offset = offsets[0] + offsets[1];

	for (int i = 0; i < key.length; i++)
	{
		Point pt = key.data[i];
		uint16_t position = offsets[0] * POINT_GET_X(pt) + offsets[1] * POINT_GET_Y(pt) - base_offset;
		uint8_t byte = position >> 3;
		uint8_t bit = position - (byte << 3);
		data[byte] |= 1 << bit;
	}

	output_stream_write(stream, data, bytes);
}

int bitsformat_read_header(InputStream *stream)
{
	return 1;
}

// Gets the number of cubes to expect in future shapes
// Must be called in the shape area of the file
uint8_t bitsformat_read_n(InputStream *stream)
{
	long offset = input_stream_get_offset(stream);

	Key test;
	bitsformat_read_key(stream, &test);

	input_stream_rewind(stream, offset);

	return test.length;
}

// Reads a key into the output pointer
// Returns 0 if the file ended
// Otherwise returns 1 on success
int bitsformat_read_key(InputStream *stream, Key *key_output)
{
	Key retval;

	uint8_t dim[2];
	if (!input_stream_read(stream, dim, 2))
	{
		return 0;
	}
	uint16_t bits = dim[0] * dim[1];
	uint8_t bytes = bits >> 3;
	bytes += bits > (bytes << 3);

	uint8_t data[bytes];
	if (!input_stream_read(stream, data, bytes))
	{
		return 0;
	}

	uint16_t position = 0;
	int point_index = 0;
	for (int x = 1; x <= dim[0]; x++)
	{
		for (int y = 1; y <= dim[1]; y++)
		{
			uint8_t byte = position >> 3;
			uint8_t bit = position % 8;

			if (data[byte] & (1 << bit))
			{
				Point p = POINT_SET_X(x) + POINT_SET_Y(y);
				retval.data[point_index] = p;
				point_index++;
			}

			position++;
		}
	}
	network_sort(retval.data, point_index, point_compare);

	retval.length = point_index;
	*key_output = retval;

	return 1;
}

uint64_t bitsformat_read_keys(InputStream *stream, Key *output_keys, uint64_t count)
{
	uint64_t i = 0;
	for (i = 0; i < count; i++)
	{
		int result = bitsformat_read_key(stream, &output_keys[i]);

		if (!result)
			break;
	}

	return i;
}