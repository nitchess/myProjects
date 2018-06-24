#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "configurator.h"
#include "reader.h"
#include "parser.h"
#include "config.h"

using namespace std;

int main()
{
	Configurator crtr("./config.INI");

	vector<Config*> * cVec = crtr.GetAgentsConfig();

	for (vector<Config*>::iterator i = cVec->begin(); i != cVec->end(); ++i)
	{
		cout << (*i)->GetID() << endl;
		cout << (*i)->GetType() << endl;
		cout << (*i)->GetBuilding() << endl;
		cout << (*i)->GetFloor() << endl;
		cout << (*i)->GetRoom() << endl;
		cout << (*i)->GetLog() << endl;
		cout << (*i)->GetConfig() << endl << endl;
	}

	return 0;
}
