#include <fstream>
#include <iostream>
#include <map>

std::string stripWhitespace(std::string str) {
	size_t non_space = str.find_first_not_of(' ');
	if(non_space != std::string::npos) str = str.substr(non_space);
	non_space = str.find_last_not_of(' ');
	if(non_space != std::string::npos) str = str.substr(0, non_space + 1);

	non_space = str.find_first_not_of("\t");
	if(non_space != std::string::npos) str = str.substr(non_space);
	non_space = str.find_last_not_of("\t");
	if(non_space != std::string::npos) str = str.substr(0, non_space + 1);
	return str;
}

bool isOnlyWhitespace(std::string str) {
	bool invalid = true;
	for(char c: str) {
		if(c != ' ' && c != '\t'){
			invalid = false;
			break;
		}
	}
	return invalid;
}

std::map<std::string,std::string> readConfig(std::string filename) {
	std::map<std::string,std::string> data;
	std::ifstream in_file(filename);
	if(!in_file) {
		std::cout << "ERROR: reading file: '" << filename << "' failed" << std::endl;
		return data;
	}
	std::string line;
	unsigned int line_idx = 0;
	while(std::getline(in_file, line)) {
		line_idx++;

		// empty line
		if(line == "") continue;

		if(isOnlyWhitespace(line)) continue;
		line = stripWhitespace(line); // maybe overkill to do it multiple times but meh
		// skip if begins with comment
		if(line[0] == '#') continue;

		// remove comments which appear at some point in line
		size_t found = line.find_first_of("#");
		if(found != std::string::npos) line = line.substr(0, found - 1);

		// split on equals sign
		size_t eq_pos = line.find('=');
		if(eq_pos == std::string::npos) {
			std::cout << "ERROR: line " << line_idx << ": no assignment found" << std::endl;
			continue;
		}

	
		std::string name = stripWhitespace(line.substr(0, eq_pos));
		std::string value = stripWhitespace(line.substr(eq_pos + 1));

		data.insert(std::pair<std::string,std::string>(name, value));
	}

	return data;
}

int main(int argc, char* argv[]) {
	auto config = readConfig("config.cfg");
}
