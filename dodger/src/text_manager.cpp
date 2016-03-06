#include "../include/text_manager.h"

#include <fstream>
#include <string>
#include <sstream>

void SkipBOM(std::ifstream &in);

TextManager * TextManager::textManager = nullptr;

TextManager &TextManager::Instance() {
	if (!textManager)
		textManager = new TextManager();
	return *textManager;
}

TextManager::~TextManager() {
	EmptyList();
}

void TextManager::ReadFile(const std::string &filename) {
	if (m_strings.size()) {
		EmptyList();
	}

	std::ifstream fileIn(filename);
	SkipBOM(fileIn);
	std::string fileStr, key, value;

	while (std::getline(fileIn, fileStr, ' ')) {
		key = fileStr; //should be text id
		std::getline(fileIn, fileStr);
		value = fileStr; //should be language value
		m_strings.insert(std::pair<std::string, std::string>(key, value));
	}
}

std::string TextManager::GetString(const std::string id) const {
	std::map<std::string, std::string>::const_iterator it = m_strings.begin();
	while (it != m_strings.end()) {
		if (it->first.compare(id) == 0) {
			return it->second;
		}
		++it;
	}

	return nullptr;
}

void TextManager::EmptyList() {
	m_strings.clear();
}

/* need to delete BOM from the beginning of the UTF-8 file.
	NOTE: function taken from StackOverflow (user: Contango) */
void SkipBOM(std::ifstream &in) {
	char test[3] = { 0 };
	in.read(test, 3);
	if ((unsigned char)test[0] == 0xEF &&
		(unsigned char)test[1] == 0xBB &&
		(unsigned char)test[2] == 0xBF) {
		return;
	}
	in.seekg(0);
}