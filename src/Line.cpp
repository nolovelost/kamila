#include <math.h>
#include "Line.h"

void Liner::Draw(Line line, const TGAColor color, TGAImage& image)
{
    bool steep = false;
    
    int x0 = line.src.x;
    int y0 = line.src.y;
    int x1 = line.dest.x;
    int y1 = line.dest.y;

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

	PutPixel(x, y, color, image, steep);
    }
}

void Liner::FastDraw(Line line, const TGAColor color, TGAImage& image)
{
    bool steep = false;

    int x0 = line.src.x;
    int y0 = line.src.y;
    int x1 = line.dest.x;
    int y1 = line.dest.y;
    
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
    
    int dx = x0 - x1;
    int dy = y0 - y1;
    int derr = abs(dy) * 2;
    int err = 0;
    float slope = abs(dy / (float)dx);
    float serror = 0.;
    
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {	
	// Transpose the rendering if steep
	PutPixel(x, y, color, image, steep);
/*
	// Increment error by deltaY for every x-wise interation
	err += derr;
	// If error exceeds dx: increment Y | decrement error
	if (err > dx)
	{
	    y += (y0 > y1) ? -1 : 1;
	    err -= dx * 2;
	}
*/
	
	// Increment error by the slope value every iteration
	serror += slope;
	// If error exceeds one pixel width: increment Y | decrement error
	if (serror > .5) // One if statement is sufficient?
	{
	    y += (y0 > y1) ? -1 : 1;
	    serror -= 1.;
	}
    }
}

inline void Liner::PutPixel(int x, int y, const TGAColor color, TGAImage& image, bool transpose)
{
    image.set(!transpose ? x : y, !transpose ? y : x, color);
}
