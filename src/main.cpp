#include <math.h>
#include "tgaimage.h"
#include "Line.h"
#include "Geometry.h"

#define WIDTH 800
#define HEIGHT 600

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor skin  = TGAColor(216, 129, 68,  255);

void ScanFill(int x0, int y0, int x1, int y1, const TGAColor color, TGAImage& image)
{
    for (int x = x0; x <= x1; x++)
    {
	for (int y = y0; y <= y1; y++)
	{
	    image.set(x, y, color);
	}
    }
}

int main(int argc, char** argv)
{
    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
    // Fill image with a color
    ScanFill(0, 0, WIDTH, HEIGHT, skin, image);

    // Line Drawer
    Liner liner;

    // Screen Diagonal Lines
    Line screenDiag1(0, 0, WIDTH, HEIGHT);
    Line screenDiag2(0, HEIGHT, WIDTH, 0);
    liner.Draw(&screenDiag1, red, image);
    liner.Draw(&screenDiag2, red, image);

    // Other Lines
    Line l0(13, 20, 80, 40);
    Line l1(13, 20, 40, 80);
    Line l2(80, 40, 40, 80);
    liner.FastDraw(&l0, white, image); 
    liner.FastDraw(&l1, white, image); 
    liner.FastDraw(&l2, white, image);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

