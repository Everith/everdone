#include "mappa.h"

namespace mappa {
	void FileNames(std::string path, std::stringstream& ss) {
		HANDLE hFind;
		WIN32_FIND_DATA data;
		std::string pathx = path + "\\*";
		int filelowersize = 0;
#ifdef DEBUG
		int meret = 0;
#endif
		hFind = FindFirstFile(pathx.c_str(), &data);
		if (hFind != INVALID_HANDLE_VALUE) {
			while (FindNextFile(hFind, &data)) {
				filelowersize = data.nFileSizeLow;
				ss << data.cFileName << '\n';
#ifdef DEBUG
				meret++;
				//std::cout << "File name: " << data.cFileName << "\t - #" << meret << std::endl;
#endif
			}
#ifdef DEBUG
			//std::cout << "Talált fileok száma: " << path.c_str () << "\t - " << meret << std::endl;
#endif
			FindClose(hFind);
		}
	}
}