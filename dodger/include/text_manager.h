#ifndef _TEXT_MANAGER_H
#define _TEXT_MANAGER_H

#include <map>

class TextManager {
public:
	static TextManager &Instance();

	void ReadFile(const std::string &filename);

	std::string GetString(const std::string id) const;
private:
	TextManager::TextManager() {}
	virtual ~TextManager();

	void EmptyList();

	static TextManager * textManager;
	std::map<std::string, std::string> m_strings;
};

#endif //!_TEXT_MANAGER_H