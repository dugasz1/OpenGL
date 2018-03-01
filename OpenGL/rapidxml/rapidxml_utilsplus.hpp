#ifndef RAPIDXML_UTILSPLUS_HPP
#define RAPIDXML_UTILSPLUS_HPP
#include <vector>
#include <map>
#include "rapidxml\rapidxml.hpp"

class rxmlp {
private:

public:
	static std::vector<rapidxml::xml_attribute<>*> GetAllAttributes(const rapidxml::xml_node<>* node) {
		std::vector<rapidxml::xml_attribute<>*> result;
		for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
		{
			//printf("attr: %s\n", attr->name());
			result.push_back(attr);
		}

		return result;
	}

	static std::vector<rapidxml::xml_attribute<>*> GetAttributesByName(const rapidxml::xml_node<>* node, const std::string& name) {
		std::vector<rapidxml::xml_attribute<>*> result;
		for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
		{
			if ( strcmp(attr->name(), name.c_str()) == 0 ) {
				result.push_back(attr);
				//printf("attr: %s\n", attr->name());
			}
		}
		return result;
	}

	static std::vector<rapidxml::xml_node<>*> GetNodesByName(const rapidxml::xml_node<>* search_node, const std::string& name) {
		std::vector<rapidxml::xml_node<>*> result;
		for (rapidxml::xml_node<> *child = search_node->first_node(); child; child = child->next_sibling())
		{
			int compare = strcmp(child->name(), name.c_str());
			//printf("asd: %s | %s | %d\n", child->name(), name.c_str(), compare);
			//GetAllAttributes(child);
			if (compare == 0) {
				result.push_back(child);
				//printf("Name: %s", child->name());
			}
		}

		return result;
	}

};

#endif
