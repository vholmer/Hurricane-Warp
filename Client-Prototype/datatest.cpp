#include <iostream>

#include "datahandler.hpp"

int main() {
	DataHandler db("testRoot");
	cout << "1" << endl;
	db.setNode("testNode");
	cout << "2" << endl;
	db.setNode("testChild", "testNode");
	cout << "3" << endl;
	db.setAttribute("testNode", "att", "25");
	cout << "4" << endl;
	db.setAttribute("testChild", "att", "25");
	cout << "5" << endl;
	db.setAttribute("testNode", "att", "29");
	cout << "6" << endl;
	db.setValue("testNode", "Gröt är äckligt.");
	cout << "7" << endl;
	db.printXML();
	return 0;
}