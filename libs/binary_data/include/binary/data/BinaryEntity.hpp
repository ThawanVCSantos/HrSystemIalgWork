#ifndef BINARY_DATA_BINARY_ENTITY_HPP
#define BINARY_DATA_BINARY_ENTITY_HPP

#include <type_traits>

namespace binary {
  namespace data {
    template <typename T>
    class BinaryEntity {
      public:
        static const char* entityName();
      private:
        BinaryEntity();
        friend T;
    };
  }
}

#include "impl/BinaryEntity.ipp"

#endif
