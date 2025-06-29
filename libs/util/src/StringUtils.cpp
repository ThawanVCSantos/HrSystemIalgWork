#include "../include/util/StringUtils.hpp"
#include <cstddef>

namespace util {
  size_t StringUtils::getStrSize(const char *str) {
    if (!str) {
      return 0;
    }
    size_t strSize = 0;
    while(str[strSize] != '\0') {
      strSize++;
    }
    return strSize;
  }

  char StringUtils::toLowerCase(char c) {
    if(c >= 'A' && c <= 'Z') {
      return c + 32;
    }
    return c;
  }

  void StringUtils::toLowerCase(char* cs) {
    int i = 0;
    while (cs[i] != '\0') {
      cs[i] = toLowerCase(cs[i]);
      i++;
    }
  }

  void StringUtils::toLowerCase(std::string& str) {
    int i = 0;
    while (str[i] != '\0') {
      str[i] = toLowerCase(str[i]);
      i++;
    }
  }

  char StringUtils::toUpperCase(char c) {
    if (c >= 'a' && c <= 'z') {
      return c - 32;
    }
    return c;
  }

  void StringUtils::toUpperCase(char* cs) {
    int i = 0;
    while (cs[i] != '\0') {
      cs[i] = toUpperCase(cs[i]);
      i++;
    }
  }

  void StringUtils::toUpperCase(std::string& str) {
    int i = 0;
    while (str[i] != '\0') {
      str[i] = toUpperCase(str[i]);
      i++;
    }
  }

  std::string StringUtils::centralize(const std::string& str, size_t size) {
    int space = size - str.length();
    if (space <= 0) return str;
    int left = space / 2;
    int rigth = space - left;
    return std::string(left, ' ') + str + std::string(rigth, ' ');
  }

  std::string StringUtils::truncate(const std::string& str, size_t size) {
    if ((size_t) str.length() <= size) {
      return str;
    }
    if (size <= 3) {
      return std::string(size, '.');
    }
    return str.substr(0, size - 3) + "...";
  }
}
