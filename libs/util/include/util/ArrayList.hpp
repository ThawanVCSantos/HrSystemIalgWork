#ifndef UTIL_ARRAY_LIST_HPP
#define UTIL_ARRAY_LIST_HPP

#include <utility>
#include <type_traits>
#include <string>
#include "ArrayUtils.hpp"

namespace util {
  template <typename T>
  class ArrayList {
    private:
      static const int DEFAULT_CAPACITY = 40;
      static const int DEFAULT_RESIZE = 10;

      T *elements;
      int length;
      int capacity;

      void resizeUp();

      void resizeDown();

      void validateIndex(int index);

      template <typename U>
      U toComparable(U value) const;

      template <size_t N>
      std::string toComparable(const char (&value)[N]) const;

      std::string toComparable(const char* value) const;
      std::string toComparable(char* value) const;
      std::string toComparable(std::string value) const;

    public:
      void add(T element);

      void remove(int index);

      void remove(const T* element);

      T get(int index);

      void clear();

      int size();

      bool isEmpty();

      T* data();

      template <typename Func>
      typename std::enable_if<
          std::is_same<
            void,
            decltype(std::declval<Func>()(std::declval<T>(), int{}))
          >::value,
          void
      >::type
      forEach(Func func);

      template <typename Func>
      typename std::enable_if<
        std::is_same<
          void,
          decltype(std::declval<Func>()(std::declval<T>()))
        >::value, void
      >::type
      forEach(Func func);

      template <typename Compare>
      typename std::enable_if<
        std::is_same<bool, decltype(std::declval<Compare>()(std::declval<T>(), std::declval<T>()))>::value,
        ArrayList<T>
      >::type
      sort(Compare comp) const;

      template <typename Predicate>
      typename std::enable_if<
        std::is_same<bool, decltype(std::declval<Predicate>()(std::declval<T>()))>::value,
        ArrayList<T>
      >::type
      filter(Predicate pred) const;

      template <typename FieldType, typename Extractor>
      const T* findBy(FieldType target, Extractor getField) const;

      ArrayList() noexcept;
      ArrayList(const ArrayList& other);
      ArrayList(ArrayList&& other) noexcept;

      ArrayList& operator=(const ArrayList& other);
      ArrayList& operator=(ArrayList&& other) noexcept;

      ~ArrayList();
  };
}

#include "impl/ArrayList.ipp"

#endif
