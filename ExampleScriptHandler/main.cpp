#include <cstdlib>
#include <iostream>
#include <ctime>
#include "ScriptHandler.hpp"

//example for the FLX ScriptHandler
//-define some commands (Events, Conditions, Actions)
//-add them to the ScriptHandler
//-load the Script(s) from File
//-update ScriptHandler

//the ScriptHandler is based on WC3 WorldEditor (Trigger Editor)

//every time a event return true, all conditions will be proofed.
//if all conditions are true, all actions will be executed.


int main(int argc, char** argv)
{
	std::srand(std::time(0));
	int value = 0;

	// create ScriptHandler
	flx::ScriptHandler scriptHandler;

	// define a simple Event
	auto Ever = [&](flx::Params &p, flx::Data &d)
	{
		return true;
	};

	// define a simple Condition
	auto ValueLimit = [&](flx::Params &p, flx::Data &d)
	{
		if(p.size() != 1)
		{
			std::cout <<"ValueLimit() ERROR: requires exactly 1 argument." << std::endl;
			return false;
		}
		else
		{
			try
			{
				if(value > std::stoi(p[0]))
				{
					return true;
				}
			}
			catch(std::invalid_argument&)
			{
				std::cout << "ValueLimit() ERROR: argument '" << p[0] << "' is not a valid number." << std::endl;
				return false;
			}
		}
	};

	// define a simple Action
	auto Print = [&](flx::Params &p, flx::Data &d)
	{
		for(auto &s : p)
		{
			std::cout << s << std::endl;
		}
	};

	// add to ScriptHandler
	scriptHandler.addEvent("Ever", Ever);
	scriptHandler.addCondition("ValueLimit", ValueLimit);
	scriptHandler.addAction("Print", Print);

	// load script
	scriptHandler.loadFile("example.flx");

	while(1)
	{
		value = std::rand()%10000;
		std::cout << value << std::endl;
		scriptHandler.update();
		std::cin.get();
	}

	return 0;
}
