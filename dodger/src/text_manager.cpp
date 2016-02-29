#include "../include/text_manager.h"

#include <fstream>
#include <string>
#include <sstream>

TextManager * TextManager::textManager = nullptr;

TextManager &TextManager::Instance() {
	if (!textManager)
		textManager = new TextManager();
	return *textManager;
}

TextManager::TextManager() {}

void TextManager::ReadFile(const std::string &filename) {
	std::ifstream fileIn(filename);
	std::string fileStr, key, value;

	while (std::getline(fileIn, fileStr, ' ')) {
		key = fileStr; //should be text id
		std::getline(fileIn, fileStr);
		value = fileStr; //should be language value
		m_strings.insert(std::pair<std::string, std::string>(key, value));
	}
}

std::string TextManager::GetString(std::string id) {
	std::map<std::string, std::string>::iterator it = m_strings.begin();
	while (it != m_strings.end()) {
		if (it->first.compare(id) == 0) {
			return it->second;
		}
		++it;
	}

	return nullptr;
}