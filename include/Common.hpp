#pragma once

#include<stdint.h>


const int width = 800,height = 600;
inline constexpr float BulletSize = 20.f;
inline constexpr float PlayerSize = 50.f;
bool isQuit = false;

template<typename T,typename = decltype((std::declval<T>() + std::declval<T>()),(std::declval<T>()-std::declval<T>()))>
struct Vec2 final
{
    T x,y;

    void operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
    }

    T operator+(const Vec2& other) {
        return Vec2{ x + other.x,y + other.y };
    }

    Vec2(const T& x_,const T& y_) :x(x_),y(y_) {}
    Vec2() = default;
};

struct RGBA final
{
    uint8_t r,g,b,a;
    RGBA(uint8_t r_,uint8_t g_,uint8_t b_,uint8_t a_):
        r(r_),g(g_),b(b_),a(a_) {}
    RGBA() = default;
};