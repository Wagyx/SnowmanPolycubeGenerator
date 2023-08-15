#include "key_generator.h"
#include "key_compression.h"
#include "network_sort.h"
#include "spacemap.h"
#include <string.h>


void write_bit(char* buffer, int bit) {
	int byte = bit >> 3;
	buffer[byte] |= 1 << (bit - (byte << 3));
}

int read_bit(char* buffer, int bit) {
	int byte = bit >> 3;
	return buffer[byte] & (1 << (bit - (byte << 3)));
}

void normalize(Point* points, size_t length) {
	Point min;
	min.data[0] = 100;
	min.data[1] = 100;
	min.data[2] = 100;
	min.data[3] = 0;
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 3; j++) {
			if (points[i].data[j] < min.data[j]) { 
				min.data[j] = points[i].data[j];
			}
		}
	}
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 3; j++) {
			points[i].data[j] += 1 - min.data[j];
		}
	}
}

// Key allocation:
// 6 bits for first point faces
// 5 bits for face bits of each remaining point
// omit last point
size_t raw_key_size(size_t number) {

	if (number < 2) return 1;
	
	size_t bits = 6 + 5 * (number - 2);
	
	// Convert to number of bytes, and round up
	return (bits >> 3) + ((bits % 8) > 0);
	
}

const int opposite_lut[7] = { 3, 4, 5, 0, 1, 2, 8 };

int get_opposite_face(int face) {
	return opposite_lut[face];
}

// This compression algorithm uses a bit scheme to convert points
// into face connections represented as individual bits.
//
// Each bit represents the face offset to get the next point in the list.
// Valid keys must have exactly n-1 bits set
// and the number of set bits before the current point
// must be at least the index of the point in the list
// 
// Currently this reduces space consumption to 8 bytes or less for n=13
// (Note the output contains exactly n-1 set bits with the rest left zero)
size_t compress(Key key, uint8_t length, char* buffer, uint8_t* compression_places) {
	
	uint8_t point_index = 1;
	int point_keys[length]; // place map keys based on order of point discovery
	point_keys[0] = spacemap_get_key(key.data[0]);
	uint8_t faces[length]; // face numbers based on order of point discovery
	faces[0] = 6; // bogus face that will yield a bogus opposite face that we can ignore
	int ptkey = 0;
	
	int bit = 0;
	const int* offsets_lut = spacemap_get_offsets();
		
	for (uint8_t i = 1; i < length; i++) {
		ptkey = spacemap_get_key(key.data[i]);
		compression_places[ptkey] = 1;
	}
	

	for (uint8_t i = 0; i < length - 1; i++) {
		int ptbasekey = point_keys[i];
		uint8_t o = get_opposite_face(faces[i]);
		
		for (uint8_t f = 0; f < 6; f++) {
			// Skip the face which refers to this point (saves a bit)
			if (f == o) continue;
			
			ptkey = ptbasekey + offsets_lut[f];
			
			if (!compression_places[ptkey]) {
				bit++;
				continue;
			}
			
			compression_places[ptkey] = 0;
			
			write_bit(buffer, bit);
			bit++;
			point_keys[point_index] = ptkey;
			faces[point_index] = f;
			point_index++;
		}
		
		if (point_index == length) break;
	}
	
	// With this last set, we have cleared the conversion_places map fully
	// meaning we don't need to set memory
	ptkey = point_keys[point_index-1];
	compression_places[ptkey] = 0;
	
	return bit;
}


// This decompression method assumes the first point is (1,1,1)
// From there we rebuild the point list by iterating through
// all the faces as in the compression method.
// After we have these points, we normalize and sort them
// to conform to the "key" layout used in generation
Key decompress(char* buffer, size_t length) {
	Key retval;	
	Point* points = retval.data;
	points[0].data[0] = 1;
	points[0].data[1] = 1;
	points[0].data[2] = 1;
	points[0].data[3] = 0;
	int points_index = 1;
	int faces[length]; // face numbers based on order of point discovery
	faces[0] = 6; // bogus face that will yield a bogus opposite face that we can ignore
	int bit = 0;
	
	if (length == 1) return retval; 
	
	for (int i = 0; i < length; i++) {
		int o = get_opposite_face(faces[i]);
		for (int f = 0; f < 6; f++) {
			if (f == o) continue;
			
			int result = read_bit(buffer, bit);
			bit++;
			
			if (!result) continue;
			
			points[points_index] = get_point_offset(points[i], f);
			faces[points_index] = f;
			points_index++;
		}
	}
	
	normalize(points, length);
	
	network_sort((int*)points, length, cmp_points);
	
	return retval;
}

