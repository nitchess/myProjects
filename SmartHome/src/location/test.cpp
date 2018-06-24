#include "location.h"
#include <iostream>

using namespace std;

typedef shared_ptr<Location> s_ptr;

int main()
{
	s_ptr aLocation = s_ptr(new Room("A1", (s_ptr(new Floor("Gallery", s_ptr(new Building("15")))))));
	
	cout << aLocation->GetDescription() << endl;

	return 0;
}
