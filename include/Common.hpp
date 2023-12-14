#pragma once



namespace CCGAME
{

template<typename T,typename = decltype((std::declval<T>() + std::declval<T>()),(std::declval<T>()-std::declval<T>()))>
struct Vec2 final
{
    T x,y;

    void operator+(const T& other) {
        x += other.x;
        y += other.y;
    }

    Vec2(const T& x_,const T& y_) :x(x_),y(y_) {}
    Vec2() = default;
};


}