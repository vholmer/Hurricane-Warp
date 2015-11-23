#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

struct DataHandler {

	xml_node<>* root;
	xml_document<> doc;

	const char* rootName;

	const string extension = ".xml";

	const string fileName;

	DataHandler(const char* name);

	xml_node<>* getNode(const char* targetNode);

	xml_attribute<>* getAttribute(const char* targetNode, const char* attName);

	string getAttributeValue(const char* targetNode, const char* attName);

	bool nodeExists(const char* nodeName);

	bool attExists(const char* targetNode, const char* attName);

	void setNode(const char* nodeName);

	void setNode(const char* nodeName, const char* parentNode);

	void setAttribute(const char* targetNode, const char* attName, const char* attVal);

	void setValue(const char* targetNode, const char* value);

	void createFile();

	void printXML();
};

#endif