#ifndef UTIL_FILE_MANAGER_HPP
#define UTIL_FILE_MANAGER_HPP

#include <string>

namespace util {
  class FileManager {
    public:
      static bool dirExists(const std::string& path);

      static bool createDir(const std::string& path);

      static bool fileExists(const std::string& path);
  };
}
#endif
