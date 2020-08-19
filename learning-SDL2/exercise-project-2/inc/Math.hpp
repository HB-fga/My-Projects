#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f( float x, float y )
    :x(x), y(y)
    {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;

};

#endif