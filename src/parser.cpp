#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "parser.h"

using namespace std;

bool Parser::try_open_file(string path)
{
	ifstream level_file(path);
	if (!level_file.is_open())
		return false;
	level_file.close();
	return true;
}

bool Parser::parse_mode(string mode)
{
	if (mode != "snake" && mode != "pacman")
		return false;
	return true;
}

bool Parser::parse_level_file(string path)
{
	//TODO
	return false;
}

void Parser::separate_layouts_from_level_file(string path)
{
	ifstream level_file(path);
	if (!try_open_file(path))
		return;
	this->layouts.clear();
	vector<string> layout;
	string line;
	while (getline(level_file, line)) {
		if (line == "END") {
			this->layouts.push_back(layout);
			layout.clear();
			continue;
		}
		layout.push_back(line);
	}
	level_file.close();
}

bool Parser::get_next_layout(vector<string>* buffer)
{
	if (this->layouts.empty())
		return false;
	buffer->clear();
	for (auto& s : this->layouts.front())
		buffer->push_back(s);
	this->layouts.erase(this->layouts.begin());
	return true;
}
