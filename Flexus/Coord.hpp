#ifndef __FLEXUS_COORD_HPP__
#define __FLEXUS_COORD_HPP__

namespace flx
{
    template<typename T>
    class Coord
    {
    public:
        /* default constructor */
        Coord():
            x(),
            y()
        {

        }

        /* constructor */
        template<typename U>
        Coord(U x, U y):
            x(static_cast<T>(x)),
            y(static_cast<T>(y))
        {

        }

        /* copy constructor */
        template<typename U>
        Coord(const Coord<U> &other):
            x(static_cast<T>(other.x)),
            y(static_cast<T>(other.y))
        {

        }

        /* copy assignment operator */
        template<typename U>
        Coord<T> operator=(const Coord<U> &right)
        {
            this(right);
            return *this;
        }

        /* operator overloads */
        bool operator==(const Coord<T> &right)
        {
            return (x == right.x) && (y == right.y);
        }

        bool operator!=(const Coord<T> &right)
        {
            return !(this == right);
        }

        bool operator<(const Coord<T> &right) const
        {
            if(y < right.y)
                return true;
            else if(y == right.y)
                return x < right.x;
            else
                return false;
        }

        template<typename U>
        Coord<T> operator*(const U &right)
        {
            return Coord<T>(x*static_cast<T>(right), y*static_cast<T>(right));
        }

        template<typename U>
        Coord<T> operator*(const Coord<U> &right)
        {
            return Coord<T>(x*static_cast<T>(right.x), y*static_cast<T>(right.y));
        }

        template<typename U>
        Coord<T>& operator*=(const U &right)
        {
            x *= static_cast<T>(right);
            y *= static_cast<T>(right);
            return *this;
        }

        template<typename U>
        Coord<T>& operator*=(const Coord<U> &right)
        {
            x *= static_cast<T>(right.x);
            y *= static_cast<T>(right.y);
            return *this;
        }

        template<typename U>
        Coord<T> operator/(const U &right)
        {
            return Coord<T>(x/static_cast<T>(right), y/static_cast<T>(right));
        }

        template<typename U>
        Coord<T> operator/(const Coord<U> &right)
        {
            return Coord<T>(x/static_cast<T>(right.x), y/static_cast<T>(right.y));
        }

        template<typename U>
        Coord<T>& operator/=(const U &right)
        {
            x /= static_cast<T>(right);
            y /= static_cast<T>(right);
            return *this;
        }

        template<typename U>
        Coord<T>& operator/=(const Coord<U> &right)
        {
            x /= static_cast<T>(right.x);
            y /= static_cast<T>(right.y);
            return *this;
        }

        template<typename U>
        Coord<T> operator+(const U &right)
        {
            return Coord<T>(x+static_cast<T>(right), y+static_cast<T>(right));
        }

        template<typename U>
        Coord<T> operator+(const Coord<U> &right)
        {
            return Coord<T>(x+static_cast<T>(right.x), y+static_cast<T>(right.y));
        }

        template<typename U>
        Coord<T>& operator+=(const U &right)
        {
            x += static_cast<T>(right);
            y += static_cast<T>(right);
            return *this;
        }

        template<typename U>
        Coord<T>& operator+=(const Coord<U> &right)
        {
            x += static_cast<T>(right.x);
            y += static_cast<T>(right.y);
            return *this;
        }

        template<typename U>
        Coord<T> operator-(const U &right)
        {
            return Coord<T>(x-static_cast<T>(right), y-static_cast<T>(right));
        }

        template<typename U>
        Coord<T> operator-(const Coord<U> &right)
        {
            return Coord<T>(x-static_cast<T>(right.x), y-static_cast<T>(right.y));
        }

        template<typename U>
        Coord<T>& operator-=(const U &right)
        {
            x -= static_cast<T>(right);
            y -= static_cast<T>(right);
            return *this;
        }

        template<typename U>
        Coord<T>& operator-=(const Coord<U> &right)
        {
            x -= static_cast<T>(right.x);
            y -= static_cast<T>(right.y);
            return *this;
        }

        T x;
        T y;
    };

    typedef Coord<float> fCoord;
    typedef Coord<double> dCoord;
    typedef Coord<int> iCoord;
    typedef Coord<unsigned int> uiCoord;
    typedef Coord<long> lCoord;
    typedef Coord<unsigned long> ulCoord;
}

#endif // __FLEXUS_COORD_HPP__
