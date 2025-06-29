#ifndef UTIL_STRING_UTILS_HPP
#define UTIL_STRING_UTILS_HPP

#include <cstddef>
#include <string>

namespace util {
  class StringUtils {
  public:

    static size_t getStrSize(const char* str);

    static char toLowerCase(char c);
    static void toLowerCase(char* cs);

    static char toUpperCase(char c);
    static void toUpperCase(char* cs);

    static std::string truncate(const std::string& str, size_t size);
    static std::string centralize(const std::string&, size_t size);
  };
}

#endif
