#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template<typename T>
class vec {
public:
    T x;
    T y;
    T z;

    vec() {}

    vec(T _x, T _y, T _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void operator+=(vec<T> rhand)
    {
        x += rhand.x;
        y += rhand.y;
        z += rhand.z;
    }

    void operator-=(vec<T> rhand)
    {
        x -= rhand.x;
        y -= rhand.y;
        z -= rhand.z;
    }

    vec<T> operator+(vec<T> rhand)
    {
        return vec<T>(x + rhand.x,
                      y + rhand.y,
                      z + rhand.z);
    }

    vec<T> operator-(vec<T> rhand)
    {
        return vec<T>(x - rhand.x,
                      y - rhand.y,
                      z - rhand.z);
    }

    T dot_product(vec<T> rhand)
    {
        return (x*rhand.x) + (y*rhand.y) + (z*rhand.z);
    }

    vec<T> cross_product(vec<T> rhand)
    {
        return vec<T>(((y * rhand.z) - (z * rhand.y)),
                      ((z * rhand.x) - (x * rhand.z)),
                      ((x * rhand.y) - (y * rhand.x)));
    }

    T magnitude()
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    void normalize()
    {
        T mag = magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
    }

    T angle_between(vec<T> v)
    {
        return acos((*this * v) / (*this->magnitude() * v.magnitude()));
    }

    void orthoganlize_from(vec<T>& v1, vec<T>& v2)
    {
        normalize();
        v2 = this->cross_product(v1).normalize();
        v1 = v2.cross_product(*this);
    }

    string to_string()
    {
        string vstr;
        vstr += std::to_string(x) + ", ";
        vstr += std::to_string(y) + ", ";
        vstr += std::to_string(z);
        return vstr;
    }

    void console_log()
    {
        cout << this->to_string() << endl;
    }
};

int main()
{
    cout << "Geometry stuff" << endl;
    vec<int> v(1, 2, 3);
    v.console_log();
    return 0;
}