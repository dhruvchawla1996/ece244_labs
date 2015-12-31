/*
 * File: DBentry.cpp
 */

#include "DBentry.h"

using namespace std;

DBentry::DBentry() {
	// for debugging purposes only
	name = "no_name";
	IPaddress = 0;
	active = false;
}

DBentry::DBentry( string _name, unsigned int _IPaddress, bool _active ) {
	name = _name;
	IPaddress = _IPaddress;
	active = _active;
}

DBentry::~DBentry() {
	// for debugging purposes only
	name = "deactivated";
	IPaddress = 0;
	active = false;
}

void DBentry::setName( string _name ) {
	name = _name;
}

void DBentry::setIPaddress( unsigned int _IPaddress ) {
	IPaddress = _IPaddress;
}

void DBentry::setActive( bool _active ) {
	active = _active;
}

string DBentry::getName() const {
	return name;
}

unsigned int DBentry::getIPaddress() const {
	return IPaddress;
}

bool DBentry::getActive() const {
	return active;
}

ostream& operator<<( ostream& out, const DBentry& rhs ) {
	// assign output based on active/incative state
	string active_text = (rhs.active) ? "active":"inactive";
	out << rhs.name << " : " << rhs.IPaddress << " : " << active_text << "\n";
	return out;
}