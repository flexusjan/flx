#include "ScriptHandler.hpp"

namespace flx
{
    ScriptHandler::ScriptHandler()
    {
    }

    void ScriptHandler::clear()
    {
        for(auto &b : blocks)
        {
            b.eventParams.clear();
            b.conditionParams.clear();
            b.actionParams.clear();
        }
        blocks.clear();
        eventFuncs.clear();
        conditionFuncs.clear();
        actionFuncs.clear();
    }

    void ScriptHandler::update()
    {
        for(auto &block : blocks)
        {
            bool event = false;
            bool condition = true;

            for(auto &ep : block.eventParams)
            {
                if(eventFuncs[ep.first](ep.second, block.data))
                {
                    event = true;
                    break;
                }
            }

            if(event)
            {
                for(auto &cp : block.conditionParams)
                {
                    if(!conditionFuncs[cp.first](cp.second, block.data))
                    {
                        condition = false;
                        break;
                    }
                }
            }

            if(condition && event)
            {
                for(auto &ap : block.actionParams)
                {
                    actionFuncs[ap.first](ap.second, block.data);
                }
            }
        }
    }

    void ScriptHandler::loadFile(std::string filename)
    {
        std::stringstream buffer;
        std::ifstream file(filename);
        buffer << file.rdbuf();
        std::string script = buffer.str();

        script.erase(std::remove(script.begin(), script.end(), '\n'), script.end());
        trim(script);

        size_t start = script.find('{');
        size_t stop = script.find('}', start);
        while(start != script.npos && stop != script.npos)
        {
            Block b;
            std::stringstream ssblock(script.substr(start+1, stop-start));
            std::string command;
            while(std::getline(ssblock, command, ';'))
            {
                if(!command.empty() && command.find("}") == command.npos)
                {
                    trim(command);
                    int bracket = command.find("(");
                    std::string func = command.substr(0,bracket);
                    trim(func);

                    std::string params = command.substr(bracket+1);
                    trim(params);
                    params.pop_back();

                    std::stringstream ssParams(params);
                    std::string param;
                    Params vec;
                    while(std::getline(ssParams, param, ','))
                    {
                        if(!param.empty())
                        {
                            vec.push_back(trim(param));
                        }
                    }

                    char sym = func.at(0);
                    func = func.substr(1);
                    trim(func);
                    if(sym == '!' && eventFuncs.find(func) != eventFuncs.end())
                    {
                        b.eventParams[func] = vec;
                    }
                    else if(sym == '?' && conditionFuncs.find(func) != conditionFuncs.end())
                    {
                        b.conditionParams[func] = vec;
                    }
                    else if(sym == '>' && actionFuncs.find(func) != actionFuncs.end())
                    {
                        b.actionParams[func] = vec;
                    }
                    else
                    {
                        std::cout<<"ScriptHandler::loadFile() ERRROR: "<<sym<<func<<" is not valid!"<<std::endl;
                    }
                }
            }
            blocks.push_back(b);
            start = script.find('{', stop);
            stop = script.find('}', start);
        }
    }

    void ScriptHandler::addEvent(std::string name, std::function<bool(Params&, Data&)> func)
    {
        eventFuncs[name] = func;
    }

    void ScriptHandler::addCondition(std::string name, std::function<bool(Params&, Data&)> func)
    {
        conditionFuncs[name] = func;
    }

    void ScriptHandler::addAction(std::string name, std::function<void(Params&, Data&)> func)
    {
        actionFuncs[name] = func;
    }

    std::string& ScriptHandler::trim(std::string& str)
    {
      str.erase(str.begin(), std::find_if(str.begin(), str.end(),
        [](char& ch)->bool { return !isspace(ch); }));
      str.erase(std::find_if(str.rbegin(), str.rend(),
        [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
      return str;
    }
}
