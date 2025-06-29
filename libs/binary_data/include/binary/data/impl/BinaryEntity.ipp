#ifndef BINARY_DATA_BINARY_ENTITY_IPP
#define BINARY_DATA_BINARY_ENTITY_IPP

#include <type_traits>

#include "../BinaryEntity.hpp"

namespace binary {
  namespace data {

    template <typename T>
    const char* BinaryEntity<T>::entityName() {
      static_assert(
        std::is_same<decltype(T::entityName()), const char*()>::value,
        "The derivated class T needs to implement 'static const char* entityName()'"
      );
      return T::entityName();
    }

    template <typename T>
    BinaryEntity<T>::BinaryEntity() {
      static_assert(
        std::is_trivially_copyable<T>::value, "T must be trivially copyable"
      );
    };
  }
}

#endif
