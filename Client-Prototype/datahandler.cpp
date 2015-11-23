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
	return getNode(targetNode)->first_attribute(attName);
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
	
}

void DataHandler::setAttribute(const char* targetNode, const char* attName, const char* attVal) {
	if(!attExists(targetNode, attName)) {
		xml_attribute<>* att = this->doc.allocate_attribute(attName, attVal);
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