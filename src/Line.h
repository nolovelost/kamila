#ifndef __LINE_H__
#define __LINE_H__

#include "tgaimage.h"

struct Line
{
    struct Source
    {
	int x;
	int y;
    } src;
    struct Dest
    {
	int x;
	int y;
    } dest;

    Line(int x0, int y0, int x1, int y1)
    {
	src.x = x0;
	src.y = y0;
	dest.x = x1;
	dest.y = y1;
    }
};

class Liner
{
public:
    void Draw(Line* line, const TGAColor& color, TGAImage& image);
    void FastDraw(Line* line, const TGAColor& color, TGAImage& image);

private:
    inline void PutPixel(int x, int y, const TGAColor color, TGAImage& image, bool transpose = false);
};

#endif
