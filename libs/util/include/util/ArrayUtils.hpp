#ifndef UTIL_ARRAY_UTILS_HPP
#define UTIL_ARRAY_UTILS_HPP

#include <cstddef>
#include <type_traits>

namespace util {
  class ArrayUtils {
  private:
    template <typename T, typename Compare>
    static void mergeSort(T* array, size_t size, int left, int right, Compare comp);
    template <typename T, typename Compare>
    static void merge(T* array, int left, int mid, int right, Compare comp);
  public:
    template <typename T>
    typename std::enable_if<!std::is_same<T, char>::value, void>::type
    static copyArrayElements(const T *arrayToCopy, T *destinyArray, size_t destinySize);

    template <typename T>
    typename std::enable_if<std::is_same<T, char>::value, void>::type
    static copyArrayElements(const T *arrayToCopy, T *destinyArray, size_t destinySize, bool includeNullTerminator = true);

    template <typename T, typename Compare>
    static void insertionSort(T* array, size_t size, Compare comp);

    template <typename T, typename Compare>
    static void mergeSort(T* array, size_t size, Compare comp);

    template <typename T, typename Compare>
    static void sort(T* array, size_t size, Compare comp);
  };
}

#include "impl/ArrayUtils.ipp"

#endif
