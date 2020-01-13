#include <math.h>
#include "tgaimage.h"
#include "Line.h"
#include "Model.h"
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

void drawline(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x=x0; x<=x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

int main(int argc, char** argv)
{
    TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
    // Fill image with a color
    ScanFill(0, 0, WIDTH, HEIGHT, skin, image);

    // Initialize the Line Drawer and the Model
    Model* model = NULL;
    if (argc == 2)
	    model = new Model(argv[1]);
    else
	    model = new Model("./obj/african_head.obj");
    Liner liner;

    // Screen Diagonal Lines
    Line screenDiag1(0, 0, WIDTH, HEIGHT);
    Line screenDiag2(0, HEIGHT, WIDTH, 0);
    liner.Draw(&screenDiag1, red, image);
    liner.Draw(&screenDiag2, red, image);

    for (int i = 0; i < model->GetFaceCount(); i++)
    {
	std::vector<int> face = model->GetFace(i);
	Line* wire;
	for (int j = 0; j < 3; j++)
	{
	    Vec3f vert0 = model->GetVertex(face[j]);
	    Vec3f vert1 = model->GetVertex(face[(j + 1) % 3]);
	    wire = new Line(
		(vert0.x + 1.) * WIDTH/2.,
		(vert0.y + 1.) * HEIGHT/2.,
		(vert1.x + 1.) * WIDTH/2.,
		(vert1.y + 1.) * HEIGHT/2.);
	    liner.FastDraw(wire, white, image);
//	    drawline(wire->src.x, wire->src.y, wire->dest.x, wire->dest.y, image, white);	    
	    delete wire;
	}
    }

    image.flip_vertically(); // To have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}
