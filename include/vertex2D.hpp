#pragma once

#include <glm/glm.hpp>

template <typename T, typename U>
class Vertex2D
{
public:
    Vertex2D(T x = 0.0f, T y = 0.0f,
             U r = 0.0f, U g = 0.0f, U b = 0.0f, U a = 0.0f);
    T x, y;
    U r, g, b, a;
};

template <typename T, typename U>
Vertex2D<T, U>::Vertex2D(T x, T y , U r, U g, U b, U a) 
    : x{x}, y{y}, r{r}, g{g}, b{b}, a{a}
{

}