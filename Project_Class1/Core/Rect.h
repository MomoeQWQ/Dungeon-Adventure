#pragma once
//simple rect struct for collision detection
struct Rect
{
	float x;
	float y;
	float w;
	float h;

	bool intersects(const Rect& rec2) const 
	{
		//split in 4 cases(B to A):up,down,left,right
		return (!(rec2.y - y >= h ||
			y - rec2.y >= rec2.h ||
			rec2.x - x >= w ||
			x - rec2.x >= rec2.w));
	}
};