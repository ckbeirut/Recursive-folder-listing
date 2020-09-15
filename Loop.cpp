#include <iostream>
#include <string>
#include <windows.h>

void findFiles(std::string const spath) {
    size_t i = 1;
    WIN32_FIND_DATA FindFileData;
    std::string sourcepath = spath + std::string("\\*.*");

    struct HandleWrapper {
        HANDLE hFind = INVALID_HANDLE_VALUE;
        ~HandleWrapper() { if (hFind != INVALID_HANDLE_VALUE) ::FindClose(hFind); }
    } wrapper;

    wrapper.hFind = FindFirstFile(sourcepath.c_str(), &FindFileData);
    if (wrapper.hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string fullpath = std::string(spath) + std::string("\\") + std::string(FindFileData.cFileName);
            if (*(fullpath.rbegin()) == '.')
                continue;
            else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                findFiles(fullpath);
            else
                std::cout << i++ << "-" << FindFileData.cFileName << " "
                    << (FindFileData.nFileSizeHigh * (MAXWORD + 1)) + FindFileData.nFileSizeLow << std::endl;
        } while (FindNextFile(wrapper.hFind, &FindFileData));
    }

}
int main(int argc, char ** argv) {

  std::string spath(argv[1]);

  findFiles(spath);

}
