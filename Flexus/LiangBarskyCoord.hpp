#ifndef __FLEXUS_LIANGBARSKYCOORD_HPP__
#define __FLEXUS_LIANGBARSKYCOORD_HPP__

#include "Coord.hpp"
#include "Rect.hpp"
#include <array>

namespace flx
{
    template<typename T>
    bool liangBarskyVec(flx::Rect<T> rect, Coord<T> vec1, Coord<T> vec2)
    {
        auto delta = vec2 - vec1;
        std::array<std::pair<T, T>, 4> checks = {
            std::make_pair(-delta.x, vec1.x - rect.left),
            std::make_pair(delta.x, rect.left + rect.width - vec1.x),
            std::make_pair(-delta.y, vec1.y - rect.top),
            std::make_pair(delta.y, rect.top + rect.height - vec1.y)
        };

        for(const auto &p : checks)
        {
            if(p.first == T(0))
            {
                return false;
            }

            float dt = p.second / float(p.first);
            if(p.first < T(0))
            {
                if(dt > 1.0f)
                {
                    return false;
                }
            }
            else if(dt < 0.0f)
            {
                return false;
            }
        }

        return true;
    }
}
#endif // __FLEXUS_LIANGBARSKYCOORD_HPP__
