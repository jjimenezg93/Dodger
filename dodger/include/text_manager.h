#ifndef _TEXT_MANAGER_H
#define _TEXT_MANAGER_H

#include <map>

class TextManager {
public:
	TextManager &Instance();

	void ReadFile(const std::string &filename);

	std::string GetString(std::string id);
private:
	TextManager();

	static TextManager * textManager;
	std::map<std::string, std::string> m_strings;
};

#endif //!_TEXT_MANAGER_H