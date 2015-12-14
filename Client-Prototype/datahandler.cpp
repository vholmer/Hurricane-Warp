#include "datahandler.hpp"

DataHandler::DataHandler(const char* name) : rootName(name), fileName(string(name) + extension) {
	xml_node<>* root = this->doc.allocate_node(node_element, this->rootName);
	this->doc.append_node(root);
	this->root = root;
}

xml_node<>* DataHandler::getNode(const char* targetNode) {
	return this->root->first_node(targetNode);
}

xml_attribute<>* DataHandler::getAttribute(const char* targetNode, const char* attName) {
	if(getNode(targetNode) != NULL)
		return getNode(targetNode)->first_attribute(attName);
	return NULL;
}

string DataHandler::getAttributeValue(const char* targetNode, const char* attName) {
	xml_attribute<>* att = getAttribute(targetNode, attName);
	return att->value();
}

bool DataHandler::nodeExists(const char* nodeName) {
	return getNode(nodeName) != NULL;
}

bool DataHandler::attExists(const char* targetNode, const char* attName) {
	return getAttribute(targetNode, attName) != NULL;
}

void DataHandler::setNode(const char* nodeName) {
	if(!nodeExists(nodeName)) {
		xml_node<>* newNode = this->doc.allocate_node(node_element, nodeName);
		this->root->append_node(newNode);
	}
}

void DataHandler::setNode(const char* nodeName, const char* parentNode) {
	if(!nodeExists(nodeName)) {
		xml_node<>* newNode = this->doc.allocate_node(node_element, nodeName);
		getNode(parentNode)->append_node(newNode);
	}
}

void DataHandler::setAttribute(const char* targetNode, const char* attName, const char* attVal) {
	if(!attExists(targetNode, attName)) {
		xml_attribute<>* att = this->doc.allocate_attribute(attName, attVal);
		cout << "Allocated memory for " << targetNode << "'s attribute: " << attName << endl;
		cout << targetNode << " == NULL: " << (getNode(targetNode) == NULL) << endl;
		getNode(targetNode)->append_attribute(att);
	} else if(attVal != getAttributeValue(targetNode, attName)) {
		xml_attribute<>* att = getAttribute(targetNode, attName);
		att->value(attVal);
	}
}

void DataHandler::setValue(const char* targetNode, const char* value) {
	getNode(targetNode)->value(value);
}

void DataHandler::createFile() {
	ofstream file;
	file.open(this->fileName);
	file << this->doc;
	file.close();
}

void DataHandler::printXML() {
	cout << this->doc;
}