#include "FictionLive.h"
#include <string>
#include <fstream>

#include <iostream>

#include "..\File\File.h"

namespace Everith {
	FictionLive::FictionLive()
	{
	}

	FictionLive::~FictionLive()
	{
	}
	void FictionLive::ConvertFile(std::string fname, std::string id)
	{
		std::string line;
		std::ifstream file(fname);
		std::string cim;

		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file!");
		}

		while (std::getline(file, line))
		{
			EVE_INFO(line);
			//Skip Menu and Tags
			skipMenu(line, file, cim);
			//skip reviewes
			skipRewievs(line, file);
			//skip choices and voting
			if (line.find("Choices") != std::string::npos)
			{
				skipChoises(file, line);
				continue;
			}
			//Skip Player Posts
			if (line.find("Reader Posts") != std::string::npos)
			{
				skipReaderPost(line, file);
				continue;
			}
			//Skip Dice Rolls
			if (line.find("Dice:") != std::string::npos)
			{
				skipDiceRolls(line, file);
				continue;
			}
			//trim the end
			skipComments(line, file);
			//save novell to buffer string
			saveNovel(line);
		}
		file.close();
		checkFileNameForSymbols(cim);
		saveNovelToFile(cim, id, line);
	}
	void FictionLive::checkFileNameForSymbols(std::string& cim)
	{
		for (int i = 0; i < cim.length(); i++)
		{
			if (cim.at(i) == '\\')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '/')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '*')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '?')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '\"')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '<')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '>')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == '|')
			{
				cim.at(i) = ' ';
			}
			else if (cim.at(i) == ':')
			{
				cim.at(i) = ' ';
			}
		}
	}
	void FictionLive::saveNovelToFile(std::string& cim, std::string& id, std::string& line)
	{
		std::ofstream output;
		output.open("Data\\Books\\" + cim + "_" + id + ".txt");
		while (std::getline(book, line))
		{
			//std::cout << line << std::endl;
			output << line << "\n";
		}
		output.close();
	}
	void FictionLive::saveNovel(std::string& line)
	{
		if (line.length() > 1)
		{
#ifdef EVE_DEBUG
			EVE_PASS(line);
#endif // DEBUG
			book << line << "\n";
		}
	}
	void FictionLive::skipComments(std::string& line, std::ifstream& file)
	{
		if (line.find("Next: ") != std::string::npos || line.find("Live Stories") != std::string::npos /*line == "Next: "*/)
		{
#ifdef EVE_DEBUG
			EVE_ERROR(line);
#endif // DEBUG
			while (std::getline(file, line))
			{
#ifdef EVE_DEBUG
				EVE_ERROR(line);
#endif // DEBUG
			}
		}
	}
	void FictionLive::skipReaderPost(std::string& line, std::ifstream& file)
	{
#ifdef EVE_DEBUG
		EVE_ERROR(line);
#endif // DEBUG
		//		std::getline(file, line);
		//#ifdef EVE_DEBUG
		//		EVE_ERROR(line);
		//#endif // DEBUG
	}
	void FictionLive::skipRewievs(std::string& line, std::ifstream& file)
	{
		bool going = true;
		if (line == "Reviews")
		{
			while (going)
			{
				if (line.find("Like") != std::string::npos)
				{
					going = false;
				}
				if (line == "WRITE A REVIEW")
				{
					going = false;
				}
#ifdef EVE_DEBUG
				EVE_ERROR(line);
#endif // DEBUG
				std::getline(file, line);
			}
		}
	}
	void FictionLive::skipMenu(std::string& line, std::ifstream& file, std::string& cim)
	{
		if (line == "All Stories")
		{
			for (int i = 0; i < 12; i++)
			{
#ifdef EVE_DEBUG
				EVE_ERROR(line);
#endif // DEBUG
				std::getline(file, line);
			}
			cim = line;
#ifdef EVE_DEBUG
			EVE_INFO("cime:");
			EVE_PASS(cim);
#endif // DEBUG
			for (int i = 0; i < 2; i++)
			{
#ifdef EVE_DEBUG
				EVE_ERROR(line);
#endif // DEBUG
				std::getline(file, line);
			}
		}
	}
	void FictionLive::skipDiceRolls(std::string& line, std::ifstream& file)
	{
#ifdef EVE_DEBUG
		EVE_ERROR(line);
#endif // DEBUG
		std::getline(file, line);
		bool isnumber = false;
		if (line.size() > 0)
		{
			char c = line.at(0);
			if (c == '0') { isnumber = true; }
			if (c == '1') { isnumber = true; }
			if (c == '2') { isnumber = true; }
			if (c == '3') { isnumber = true; }
			if (c == '4') { isnumber = true; }
			if (c == '5') { isnumber = true; }
			if (c == '6') { isnumber = true; }
			if (c == '7') { isnumber = true; }
			if (c == '8') { isnumber = true; }
			if (c == '9') { isnumber = true; }
		}
		if (!isnumber && line.size() > 0)
		{
#ifdef EVE_DEBUG
			EVE_ERROR(line); //line lost when main loop starts
#endif // DEBUG
			std::getline(file, line);
		}
#ifdef EVE_DEBUG
		EVE_ERROR(line); //line lost when main loop starts
#endif // DEBUG
	}
	void FictionLive::skipChoises(std::ifstream& file, std::string& line)
	{
#ifdef EVE_DEBUG
		EVE_ERROR(line);
#endif // DEBUG
		std::getline(file, line);

		bool notfound = true;
		bool isnumber = false;
		std::string choice;
		int votes = 0;
		std::string choicebuff;
		std::string votesbuff;
		while (notfound)
		{
#ifdef EVE_DEBUG
			EVE_ERROR(line);
#endif // DEBUG
			std::getline(file, line); // choice
			choicebuff = line;

#ifdef EVE_DEBUG
			EVE_ERROR(line);
#endif // DEBUG
			std::getline(file, line); // votes
			votesbuff = line;

			isnumber = false;
			if (line.length() > 1)
			{
				//WARN wrong number check
				char c = line.at(0);
				if (c == '0') { isnumber = true; }
				if (c == '1') { isnumber = true; }
				if (c == '2') { isnumber = true; }
				if (c == '3') { isnumber = true; }
				if (c == '4') { isnumber = true; }
				if (c == '5') { isnumber = true; }
				if (c == '6') { isnumber = true; }
				if (c == '7') { isnumber = true; }
				if (c == '8') { isnumber = true; }
				if (c == '9') { isnumber = true; }
			}
			if (isnumber)
			{
				if (votes < std::stoi(line))
				{
					//record  most voted choice and votes
					votes = std::stoi(line);
					choice = choicebuff;
				}
			}
			else
			{
				//SAVE most voted choice
				if (choicebuff.length() > 1)
				{
#ifdef EVE_DEBUG
					EVE_PASS(choice);
#endif // DEBUG
					book << choice << "\n";
					notfound = false;
				}
				//Save pending line
				if (votesbuff == "VOTES")
				{
					EVE_FATAL("VOTES not implemented");
				}
				else if (line.length() > 1)
				{
					if (choicebuff.find("Next: ") != std::string::npos || line.find("Live Stories") != std::string::npos /*line == "Next: "*/)
					{
						skipComments(choicebuff, file); //if a chois the last thing, buffer eats the end line
					}
					else if (votesbuff.find("Next: ") != std::string::npos || line.find("Live Stories") != std::string::npos /*line == "Next: "*/)
					{
						skipComments(votesbuff, file); //if a chois the last thing, buffer eats the end line
					}
					else if (line.find("Next: ") != std::string::npos || line.find("Live Stories") != std::string::npos  /*line == "Next: "*/)
					{
						skipComments(line, file); //if a chois the last thing, buffer eats the end line
					}
					else {
#ifdef EVE_DEBUG
						EVE_PASS(line);
#endif // DEBUG
						book << line << "\n"; //WARN  possible thras data
					}
					notfound = false;
				}
			}
		}
	}
}