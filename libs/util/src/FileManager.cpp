#include "../include/util/FileManager.hpp"
#include <fstream>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/stat.h>
  #include <errno.h>
#endif

namespace util {

  bool FileManager::dirExists(const std::string& path) {
    #ifdef _WIN32
      DWORD attributes = GetFileAttributesA(path.c_str());
      return (attributes != INVALID_FILE_ATTRIBUTES &&
        (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
    #else
      struct stat info;
      if (stat(path.c_str(), &info) != 0) {
        return false;
      }
      return S_ISDIR(info.st_mode);
    #endif
  }

  bool FileManager::createDir(const std::string& path) {
    if (dirExists(path)) {
      return true;
    }

    #ifdef _WIN32
      BOOL result = CreateDirectoryA(path.c_str(), NULL);
      return (result != 0 || GetLastError() == ERROR_ALREADY_EXISTS);
    #else
      int result = mkdir(path.c_str(), 0755);
      if (result == 0) {
        return true;
      }
      if (errno == EEXIST) {
        return true;
      }
      return false;
    #endif
  }

  bool FileManager::fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
  }
}
