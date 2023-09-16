#include "point.h"

// Note the first component ("X") matches the relevant flipped component
// This means we can snap to a given dimension by using the dimension index * 4
const uint8_t point_rotations_lut[][2] = {
	{0,1},
	{0,3},
	{2,3},
	{2,1}
	// {1,0},
	// {3,0},
	// {3,2},
	// {1,2}
};

// This "PointData" includes the original point
// plus the additional 3 components dependent on the dimensions
// that would appear when reflected in rotations
PointData point_get_data(Point point, Point dimensions) {
	PointData retval;
	
	retval.data[0] = POINT_GET_X(point);
	retval.data[1] = POINT_GET_Y(point);
	
	retval.data[2] = POINT_GET_X(dimensions) - retval.data[0] + 1;
	retval.data[3] = POINT_GET_Y(dimensions) - retval.data[1] + 1;
	
	return retval;
}

const int point_offsets_lut[4] = { 1, 128, -1, -128};

const int* point_get_offsets_lut() {
	return point_offsets_lut;
}

// Offsets the point toward the relevant face ID
Point point_get_offset(Point point, int face) {
	return point + point_offsets_lut[face];
}

// Use the lookup table to build the relevant rotation components
// Components 3 to 5 are reflections of components 0 to 2
Point point_rotate(PointData point_data, uint8_t rot_num) {
	uint8_t* p = point_data.data;
	const uint8_t* r = point_rotations_lut[rot_num];
	
	return POINT_SET_X(p[r[0]]) + POINT_SET_Y(p[r[1]]);
}

const uint8_t* point_get_rotation_data(uint8_t rot_num) {
	return point_rotations_lut[rot_num];
}

int point_compare(const void* a, const void* b) {
	Point* ap = (Point*) a;
	Point* bp = (Point*) b;
	
	return *ap - *bp;
}

Point point_from_coords(uint8_t x, uint8_t y) {
	return POINT_SET_X(x) + POINT_SET_Y(y);
}
