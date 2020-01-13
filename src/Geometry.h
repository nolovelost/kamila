#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <math.h>


template <class T> struct Vec2
{
    union
    {
	struct
	{
	    T u, v;
	};
	struct
	{
	    T x, y;
	};
	T raw[2];
    };

    Vec2() : u(0), v(0) {}
    Vec2(T _u, T _v) : u(_u), v(_v) {}

    inline Vec2<T> operator+ (const Vec2<T>& other) const { return Vec2<T>(this.u + other.u, this.v + other.v); }
    inline Vec2<T> operator- (const Vec2<T>& other) const { return Vec2<T>(this.u - other.u, this.v + other.v); }
    inline Vec2<T> operator* (const float other) const { return Vec2<T>(this.x * other, this.y * other); }

    template <class > friend std::ostream& operator<< (std::ostream& o, Vec2& vec);
};

template <class T> struct Vec3
{
    union
    {
	struct
	{
	    T x, y, z;
	};
	struct
	{
	    T ivert, iuv, inorm;
	};
	T raw[3];
    };

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    inline Vec2<T> operator+ (const Vec2<T>& other) const { return Vec2<T>(this.x + other.x, this.y + other.y, this.z + other.z); }
    inline Vec2<T> operator- (const Vec2<T>& other) const { return Vec2<T>(this.x - other.x, this.y - other.y, this.z - other.z); }
    inline Vec2<T> operator* (const float other) const { return Vec2<T>(this.x * other, this.y * other, this.z * other); }
    inline Vec3<T> operator^ (const Vec3<T>& other) const { return Vec3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
    inline T operator* (const Vec3<T>& other) const { return x * other.x + y * other.y + z * other.z; }
    float Norm() const { return sqrt(x * x + y * y + z * z); }
    inline Vec3<T>& Normalize()
    {
	this.x = x / Norm(this);
	this.y = y / Norm(this);
	this.z = z / Norm(this);
	return this;
    }

    template <class > friend std::ostream& operator<< (std::ostream& o, Vec3& vec);
};

template <class T> std::ostream& operator<< (std::ostream& o, Vec2<T>& vec)
{
    o << "(" << vec.x << ", " << vec.y << ")\n";
    return o;
}

template <class T> std::ostream& operator<< (std::ostream& o, Vec3<T>& vec)
{
    o << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
    return o;
}

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec3<int> Vec3i;
typedef Vec3<float>  Vec3f;

#endif
