#ifndef __FLEXUS_NODE_HPP__
#define __FLEXUS_NODE_HPP__

#include "flexus/Coord.hpp"

namespace flx
{
    template<typename T>
    class Node
    {
    public:
        /* default constructor */
        Node():
            position(),
            parent(-1),
            g(),
            h(),
            f()
        {

        }

        /* constructor */
        Node(Coord<T> position, int parent, T g, Coord<T> endPos):
            position(position),
            parent(parent),
            g(g),
            h((abs(position.x - endPos.x) + abs(position.y - endPos.y))*10),
            f(g+h)
        {

        }

        /* operator overloads */
        bool operator<(const Node<T>& right) const
        {
            return f < right.f;
        }

        bool operator==(const Node<T>& right) const
        {
            return position == right.position;
        }

        bool operator!=(const Node<T>& right) const
        {
            return position != right.position;
        }

        Coord<T> position;
        int parent;
        T g, h, f;
    };
}

#endif // __FLEXUS_NODE_HPP__
