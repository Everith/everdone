#include "file.h"

namespace file {
	std::vector<char>  readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file!");
		}
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}

	void printFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			//            Error ("Failed to open file! EROOR! ERROR! ERROR!");
			return;
		}
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		for (size_t i = 0; i < fileSize; i++) {
			std::cout << buffer[i];
		}
		std::cout << std::endl;
		std::cout << "A File mérete: " << fileSize << "\n";
	}

	//TODO átalakitani hogy értelme legyen és kiadja a legjób 20 ajánlatot
	void read_CSV_File(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			//            Error("Failed to open file!");
			return;
		}
		rsize_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		for (size_t i = 0; i < fileSize; i++) {
			if (buffer[i] == ',') {
				std::cout << "\t";
			}
			else {
				std::cout << buffer[i];
			}
		}
		std::cout << std::endl;
	}

	//void replace_line (std::string oldLine, std::string newLine, std::string filename) {
	//    using namespace std;
	//    ifstream filein (filename.c_str ()); //File to read from
	//    if (!filein) {
	//        cout << "Error opening files!" << endl;
	//    }

	//    string line;
	//    stringstream ss;

	//    while (getline (filein, line)) {
	//        if (line.find (oldLine) != std::string::npos) {
	//            line = newLine;
	//        }
	//        ss << line + "\n";
	//    }
	//    filein.close ();

	//    ofstream fileout (filename.c_str ()); //Temporary file
	//    while (getline (ss, line)) {
	//        fileout << line << "\n";
	//    }
	//    fileout.close ();
	//}
}