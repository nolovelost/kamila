#include <math.h>
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void Line(int x0, int y0, int x1, int y1, const TGAColor color, TGAImage& image)
{
    bool steep = false;

    // If line is from right to left: swap
    if (x0 > x1)
    {
	std::swap(x0, x1);
	std::swap(y0, y1);
    }
    
    // If line is steep: transpose
    if (abs(x1-x0) < abs(y1-y0))
    {
	std::swap(x0, y0);
	std::swap(x1, y1);
	steep = true;
    }
	
    for (int x = x0; x <= x1; x++)
    {
	int y;
	float t;
	t = (x - x0) / (float)(x1 - x0); // ratio ahead in the x-axis
	y = y0 * (1. - t) + y1 * t; // parametric eq. for step-wise increment of the line's y-axis

	// Transpose the rendering if steep
	if (steep)
	    image.set(y, x, color);
	else
	    image.set(x, y, color);
    }
}

int main(int argc, char** argv)
{
    TGAImage image(100, 100, TGAImage::RGB);
    Line(13, 20, 80, 40, white, image); 
    Line(20, 13, 40, 80, red, image); 
    Line(80, 40, 13, 40, red, image);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

