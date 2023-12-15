#pragma once

#include<stdint.h>
#include<cmath>
#define ANGTOROT(an) (float(an*M_PI/180))

const int width = 800,height = 600;
inline constexpr float BulletSize = 20.f;
inline constexpr float PlayerSize = 50.f;
bool isQuit = false;

const char* TrianglePath = "../assets/triangle.png";
const char* CirclePath = "../assets/circle.png";
const char* RectPath = "../assets/rect.png";
const char* BulletPath = "../assets/bullet.png";

template<typename T,typename = decltype((std::declval<T>() + std::declval<T>()),(std::declval<T>()-std::declval<T>()))>
struct Vec2 final
{
    T x,y;

    void operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
    }

    Vec2 operator+(const Vec2& other) const {
        return Vec2{ x + other.x,y + other.y };
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2{ x - other.x,y - other.y };
    }

    Vec2 operator+(const T& n) const {
        return Vec2{ x + n,y + n };
    }

    Vec2 operator-(const T& n) const {
        return Vec2{ x - n,y - n };
    }

    Vec2 operator*(const T& n) const {
        return Vec2{ x * n,y * n };
    }

    Vec2 operator/(const T& n) const {
        return Vec2{ x / n,y / n };
    }



    Vec2 normal() const {
        T s = std::sqrt(x * x + y * y);
        return Vec2{ x / s,y / s };
    }




    Vec2(const T& x_,const T& y_) :x(x_),y(y_) {}
    Vec2() = default;
};

struct RGBA final
{
    uint8_t r,g,b,a;

    RGBA(uint8_t r_,uint8_t g_,uint8_t b_,uint8_t a_) :
        r(r_),g(g_),b(b_),a(a_) {}
    RGBA() :RGBA(255,255,255,255) {}
 
};