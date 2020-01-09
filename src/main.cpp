#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void Line(int x0, int y0, int x1, int y1, float step, const TGAColor color, TGAImage& image)
{
    for (int x = x0; x <= x1; x++)
    {
	int y;
	float t;
	t = (x - x0) / (float)(x1 - x0);
	y = y0 * (1. - t) + y1 * t;
	image.set(x, y, color);
    }
}

int main(int argc, char** argv)
{
    TGAImage image(100, 100, TGAImage::RGB);
    Line(13, 20, 80, 40, 0.1, white, image); 
    Line(20, 13, 40, 80, 0.1, red, image); 
    Line(80, 40, 13, 20, 0.1, red, image);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

