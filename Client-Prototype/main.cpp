#include <iostream>
#include <string>
#include <fstream>

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_print.hpp"


using namespace rapidxml;

using namespace std;

struct XMLTest {

	xml_document<> doc;
	const string fileName = "weapons.xml";

	void createWeaponXML() {
		xml_node<>* weapons = this->doc.allocate_node(node_element, "weapons");
		this->doc.append_node(weapons);

		xml_node<>* wpn_sword = this->doc.allocate_node(node_element, "sword");
		wpn_sword->append_attribute(this->doc.allocate_attribute("damage","12"));
		weapons->append_node(wpn_sword);

		xml_node<>* wpn_axe = this->doc.allocate_node(node_element, "axe");
		wpn_axe->append_attribute(this->doc.allocate_attribute("damage","7"));
		weapons->append_node(wpn_axe);

		wpn_axe->value("An iron axe.");
		wpn_sword->value("An ancient sword.");
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

	XMLTest xml;
	xml.createWeaponXML();
	xml.createFile();

	return 0;
}
