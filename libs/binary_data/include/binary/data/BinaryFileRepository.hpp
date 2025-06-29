#ifndef BINARY_DATA_BINARY_FILE_REPOSITORY_HPP
#define BINARY_DATA_BINARY_FILE_REPOSITORY_HPP

#include <type_traits>
#include <string>
#include "BinaryEntity.hpp"
#include "../../../../util/include/util/ArrayList.hpp"

using util::ArrayList;

namespace binary {
  namespace data {
    template <typename T>
    class BinaryFileRepository {
      static_assert(
        !std::is_base_of<BinaryFileRepository<T>, T>::value,
        "T cannot inherit BinaryFileRepository<T>"
      );
      static_assert(
        std::is_base_of<BinaryEntity<T>, T>::value,
        "T needs to inherit BinaryEntity<T>"
      );
      protected:
        char filename[50];
        std::string path();
        BinaryFileRepository();
      public:
        ArrayList<T> readAll();
        void write(T entity, bool enableTruncate = false);
        void writeAll(ArrayList<T>& entities, bool enableTruncate = false);
    };
  }
}

#include "impl/BinaryFileRepository.ipp"

#endif
