#include <iostream>

#include "datahandler.hpp"

int main() {
	DataHandler db("testRoot");
	db.setNode("testNode");
	db.setNode("testNode");
	db.setAttribute("testNode", "att", "25");
	db.setAttribute("testNode", "att", "25");
	db.setAttribute("testNode", "att", "29");
	db.setValue("testNode", "Gröt är äckligt.");
	db.printXML();
	return 0;
}