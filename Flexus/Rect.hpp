#ifndef __FLEXUS_RECT_HPP__
#define __FLEXUS_RECT_HPP__

#include "Coord.hpp"

namespace flx
{
    template<typename T>
    class Rect
    {
    public:
        Rect():
            left(),
            top(),
            width(),
            height()
        {

        }

        template<typename U>
        Rect(U left, U top, U width, U height):
            left(static_cast<T>(left)),
            top(static_cast<T>(top)),
            width(static_cast<T>(width)),
            height(static_cast<T>(height))
        {

        }

        Rect(const Rect<T> &rect):
            left(rect.left),
            top(rect.top),
            width(rect.width),
            height(rect.height)
        {

        }

        template<typename U>
        bool contains(U x, U y)
        {
            T minX(std::min(left, static_cast<T>(left+width)));
            T maxX(std::max(left, static_cast<T>(left+width)));
            T minY(std::min(top, static_cast<T>(top+height)));
            T maxY(std::max(top, static_cast<T>(top+height)));
            return (static_cast<T>(x) >= minX) && (static_cast<T>(x) < maxX) &&
                   (static_cast<T>(y) >= minY) && (static_cast<T>(y) < maxY);
        }

        template<typename U>
        bool contains(const Coord<U> &coord)
        {
            return contains(coord.x, coord.y);
        }

        template<typename U>
        bool intersects(const Rect<U> &rect)
        {
            T r1MinX(std::min(left, static_cast<T>(left+width)));
            T r1MaxX(std::max(left, static_cast<T>(left+width)));
            T r1MinY(std::min(top, static_cast<T>(top+height)));
            T r1MaxY(std::max(top, static_cast<T>(top+height)));
            T r2MinX(std::min(rect.left, static_cast<T>(rect.left+rect.width)));
            T r2MaxX(std::max(rect.left, static_cast<T>(rect.left+rect.width)));
            T r2MinY(std::min(rect.top, static_cast<T>(rect.top+rect.height)));
            T r2MaxY(std::max(rect.top, static_cast<T>(rect.top+rect.height)));
            T interLeft(std::max(r1MinX, r2MinX));
            T interTop(std::max(r1MinY, r2MinY));
            T interRight(std::min(r1MaxX, r2MaxX));
            T interBottom(std::min(r1MaxY, r2MaxY));
            return (interLeft < interRight) && (interTop < interBottom);
        }

        Coord<T> getCenter()
        {
            return Coord<T>(left + width/2, top + height/2);
        }

        Coord<T> getTopLeft()
        {
            return Coord<T>(left, top);
        }

        Coord<T> getTopRight()
        {
            return Coord<T>(left+width, top);
        }

        Coord<T> getBottomLeft()
        {
            return Coord<T>(left, top + height);
        }

        Coord<T> getBottomRight()
        {
            return Coord<T>(left + width, top + height);
        }

        Coord<T> getSize()
        {
            return Coord<T>(width, height);
        }

        T getTop()
        {
            return top;
        }

        T getLeft()
        {
            return left;
        }

        T getRight()
        {
            return left + width;
        }

        T getBottom()
        {
            return top + height;
        }

        T getWidth()
        {
            return width;
        }

        T getHeight()
        {
            return height;
        }

        T getCenterX()
        {
            return left + width/2;
        }

        T getCenterY()
        {
            return top + height/2;
        }

        template<typename U>
        void setLeft(U l)
        {
            left = static_cast<T>(l);
        }

        template<typename U>
        void setTop(U t)
        {
            top = static_cast<T>(t);
        }

        template<typename U>
        void setWidth(U w)
        {
            width = static_cast<T>(w);
        }

        template<typename U>
        void setHeight(U h)
        {
            height = static_cast<T>(h);
        }

        template<typename U>
        void setPosition(U px, U py)
        {
            setLeft(px);
            setTop(py);
        }

        template<typename U>
        void setPosition(const Coord<U> &pos)
        {
            setPosition(pos);
        }

        template<typename U>
        void setSize(U sx, U sy)
        {
            setWidth(sx);
            setHeight(sy);
        }

        template<typename U>
        void setSize(const Coord<U> &size)
        {
            setSize(size);
        }

        Rect<T>& operator=(const Rect<T> &other)
        {
            this(other);
            return *this;
        }

        bool operator==(const Rect<T> &other)
        {
            return (left == other.left) && (top == other.top) && (width == other.width) && (height == other.height);
        }

        bool operator!=(const Rect<T> &other)
        {
            return !(this == other);
        }

    private:
        T left, top, width, height;
    };

    typedef Rect<float> fRect;
    typedef Rect<double> dRect;
    typedef Rect<int> iRect;
    typedef Rect<unsigned int> uiRect;
    typedef Rect<long> lRect;
    typedef Rect<unsigned long> ulRect;
}

#endif // __FLEXUS_RECT_HPP__
