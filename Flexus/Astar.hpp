#ifndef __FLEXUS_ASTAR_HPP__
#define __FLEXUS_ASTAR_HPP__

#include <typeinfo>
#include <vector>
#include "flexus/Coord.hpp"


namespace flx
{
    template<typename T>
    std::vector<Coord<T>> astar(const std::vector<int> &map, int mapx, int mapy, Coord<T> startPoint, Coord<T> endPoint, bool diagonal = false)
    {
        std::vector<Node<T>> openNodes;
        std::vector<Node<T>> closedNodes;
        std::vector<Node<T>> nearNodes(4 + diagonal * 4);
        std::vector<Coord<T>> way;
        Node<T> startNode(endPoint, -1, 0, endPoint);
        Node<T> endNode(startPoint, -1, 0, endPoint);
        openNodes.push_back(startNode);

        while(!openNodes.empty())
        {
            auto minF = std::min_element(openNodes.begin(), openNodes.end());

            closedNodes.push_back(*minF);
            openNodes.erase(minF);
            int currentIndex = closedNodes.size()-1;
            auto &currentNode = closedNodes[currentIndex];

            if(currentNode==endNode) break;

            nearNodes.clear();
            nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x-1, currentNode.position.y), currentIndex, currentNode.g + 10, endPoint)); //left
            nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x+1, currentNode.position.y), currentIndex, currentNode.g + 10, endPoint)); //right
            nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x, currentNode.position.y-1), currentIndex, currentNode.g + 10, endPoint)); //top
            nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x, currentNode.position.y+1), currentIndex, currentNode.g + 10, endPoint)); //bottom

            if(diagonal)
            {
                nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x-1, currentNode.position.y-1), currentIndex, currentNode.g + 14, endPoint)); //topleft
                nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x+1, currentNode.position.y-1), currentIndex, currentNode.g + 14, endPoint)); //topright
                nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x-1, currentNode.position.y+1), currentIndex, currentNode.g + 14, endPoint)); //bottomleft
                nearNodes.push_back(Node<T>(Coord<T>(currentNode.position.x+1, currentNode.position.y+1), currentIndex, currentNode.g + 14, endPoint)); //bottomright
            }

            for(auto &node : nearNodes)
            {
                auto &pos = node.position;

                if(pos.x >= 0 && pos.y >= 0 && pos.x < mapx && pos.y < mapy)
                {
                    if (!std::any_of(closedNodes.begin(), closedNodes.end(), [&](const Node<T> &n){return (n.position == pos);}))
                    {
                        auto it = std::find(openNodes.begin(), openNodes.end(), node);
                        if(it == openNodes.end())
                        {
                            if(map[pos.x + pos.y*mapx] == 0)
                            {
                                openNodes.push_back(node);
                            }
                        }
                        else
                        {
                            auto &tNode = *it;
                            if(node.g < tNode.g)
                            {
                                tNode.g = node.g;
                                tNode.f = tNode.g + tNode.h;
                                tNode.parent = node.parent;
                            }
                        }
                    }
                }
            }
        }

        auto it = std::find(closedNodes.begin(), closedNodes.end(), endNode);

        if(it != closedNodes.end())
        {
            auto node = *it;
            way.push_back(node.position);
            while(node != startNode)
            {
                node = closedNodes[node.parent];

                way.push_back(node.position);
            }
        }

        return way;
    }
}

#endif // __FLEXUS_ASTAR_HPP__
