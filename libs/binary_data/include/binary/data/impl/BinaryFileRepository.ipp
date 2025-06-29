#ifndef BINARY_DATA_BINARY_FILE_REPOSITORY_IPP
#define BINARY_DATA_BINARY_FILE_REPOSITORY_IPP

#include <fstream>
#include <cstddef>
#include <stdexcept>
#include <typeinfo>
#include <string>

#include "../BinaryFileRepository.hpp"
#include "../../../../../util/include/util/ArrayList.hpp"
#include "../../../../../util/include/util/ArrayUtils.hpp"
#include "../../../../../util/include/util/StringUtils.hpp"
#include "../../../../../util/include/util/FileManager.hpp"

using util::ArrayList;
using util::ArrayUtils;
using util::StringUtils;
using util::FileManager;

namespace binary {
  namespace data {

    template <typename T>
    ArrayList<T> BinaryFileRepository<T>::readAll() {
      std::ifstream file(path(), std::ios_base::binary);
      if (!file) {
        throw std::runtime_error("An error occurred while opening the file: [" + std::string(this->filename) + "]");
      }

      ArrayList<T> entities;
      T entity;
      while (file.read(reinterpret_cast<char*>(&entity), sizeof(T))) {
        entities.add(entity);
      }
      file.close();
      return entities;
    }

    template <typename T>
    void BinaryFileRepository<T>::write(T entity, bool enableTruncate) {
      std::ofstream file(path(), std::ios_base::binary | (enableTruncate ? std::ios::trunc : std::ios::app));
      if (!file) {
        throw std::runtime_error("An error occurred while opening the file: [" + std::string(this->filename) + "]");
      }
      file.write(reinterpret_cast<const char*>(&entity), sizeof(T));
      file.close();
    }

    template <typename T>
    void BinaryFileRepository<T>::writeAll(ArrayList<T>& entities, bool enableTruncate) {
      std::ofstream file(path(), std::ios_base::binary | (enableTruncate ? std::ios::trunc : std::ios::app));
      if (!file) {
        throw std::runtime_error("An error occurred while opening the file: [" + std::string(this->filename) + "]");
      }
      if(entities.size() > 0) {
        file.write(reinterpret_cast<const char*>(entities.data()), entities.size() * sizeof(T));
      }
      file.close();
    }

    template <typename T>
    BinaryFileRepository<T>::BinaryFileRepository() {
      size_t entityNameSize = StringUtils::getStrSize(T::entityName());

      if (entityNameSize == 0) {
        throw std::invalid_argument("The method 'static const char* entityName' cannot be return empty string: [" + std::string(typeid(T).name()) + "]");
      }

      if(entityNameSize > 45) {
        entityNameSize = 45;
      }

      ArrayUtils::copyArrayElements(T::entityName(), this->filename, entityNameSize, false);
      ArrayUtils::copyArrayElements(".bin", this->filename + entityNameSize, 5);

      FileManager::createDir("data");
      std::ofstream file("data/" + std::string(this->filename), std::ios::binary | std::ios::app);
      file.close();
    }

    template<typename T>
    std::string BinaryFileRepository<T>::path() {
      return "data/" + std::string(this->filename);
    }
  }
}

#endif
