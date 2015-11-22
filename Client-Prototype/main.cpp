#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

using namespace std;

struct DataBaseHandler {

	xml_node<>* root;
	xml_document<> doc;
	
	const char* rootName;
	
       	const string extension = ".xml";

	const string fileName;

	DataBaseHandler(const char* name) : rootName(name), fileName(string(name) + extension) {
		xml_node<>* weapons = this->doc.allocate_node(node_element, this->rootName);
		this->doc.append_node(weapons);
		this->root = this->doc.first_node();
	}

	xml_node<>* getNode(const char* targetNode) {
		return this->root->first_node(targetNode);
	}

	void setNode(const char* nodeName) {
		xml_node<>* newNode = this->doc.allocate_node(node_element, nodeName);
		this->root->append_node(newNode);
	}

	void setAttribute(const char* targetNode, const char* attName, const char* attVal) {
		xml_attribute<>* att = this->doc.allocate_attribute(attName, attVal);
		getNode(targetNode)->append_attribute(att);
	}

	void setValue(const char* targetNode, const char* value) {
		getNode(targetNode)->value(value);
	}

	void createFile() {
		ofstream wpnFile;
		wpnFile.open(this->fileName);
		wpnFile << this->doc;
		wpnFile.close();
	}
};

int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	
	DataBaseHandler wpn("weapons");
	wpn.setNode("sword");
	wpn.setAttribute("sword", "damage", "15");
	wpn.setNode("axe");
	wpn.setAttribute("axe", "damage", "7");
	wpn.setValue("axe", "A sharp iron axe.");
	wpn.setValue("sword", "An ancient bronze sword.");
	wpn.createFile();

	DataBaseHandler items("items");
	items.setNode("apple");
	items.setAttribute("apple", "heals", "20");
	items.setNode("chainsword");
	items.setAttribute("chainsword", "damage", "63");
	items.setValue("apple", "A shiny red apple. Looks tasty.");
	items.setValue("chainsword", "A mighty chain sword, forged on Holy Terra itself.");
	items.createFile();

	return 0;
}
