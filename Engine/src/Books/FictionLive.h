#pragma once
#include <string>
#include <sstream>

namespace Everith {
	class FictionLive
	{
	public:
		FictionLive();
		~FictionLive();
		std::stringstream book;

		void ConvertFile(std::string fname, std::string id);

	private:
		void skipMenu(std::string& line, std::ifstream& file, std::string& cim);
		void skipRewievs(std::string& line, std::ifstream& file);
		void skipChoises(std::ifstream& file, std::string& line);
		void skipReaderPost(std::string& line, std::ifstream& file);
		void skipDiceRolls(std::string& line, std::ifstream& file);
		void skipComments(std::string& line, std::ifstream& file);
		void saveNovel(std::string& line);
		void checkFileNameForSymbols(std::string& cim);
		void saveNovelToFile(std::string& cim, std::string& id, std::string& line);
	};
}