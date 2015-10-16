#ifndef __FLEXUS_SCRIPTHANDLER_HPP__
#define __FLEXUS_SCRIPTHANDLER_HPP__

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "Whatever.hpp"

namespace flx
{
    using Params = std::vector<std::string>;
    using Data = std::map<std::string, flx::Whatever>;

    struct Block
    {
        std::map<std::string, Params> eventParams;
        std::map<std::string, Params> conditionParams;
        std::map<std::string, Params> actionParams;
        Data data;
    };

    class ScriptHandler
    {
    public:
        ScriptHandler();

        void clear();

        void update();

        void loadFile(std::string filename);

        void addEvent(std::string name, std::function<bool(Params&, Data&)> func);

        void addCondition(std::string name, std::function<bool(Params&, Data&)> func);

        void addAction(std::string name, std::function<void(Params&, Data&)> func);

    private:
        std::string& trim(std::string& str);

        std::vector<Block> blocks;
        std::map<std::string, std::function<bool(Params&, Data&)>> eventFuncs;
        std::map<std::string, std::function<bool(Params&, Data&)>> conditionFuncs;
        std::map<std::string, std::function<void(Params&, Data&)>> actionFuncs;
    };
}

#endif // __FLEXUS_SCRIPTHANDLER_HPP__
