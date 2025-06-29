#ifndef UTIL_ARRAY_UTILS_IPP
#define UTIL_ARRAY_UTILS_IPP

#include "../ArrayUtils.hpp"
#include <cstddef>

namespace util {
  template <typename T>
  typename std::enable_if<!std::is_same<T, char>::value, void>::type
  ArrayUtils::copyArrayElements(const T *arrayToCopy, T *destinyArray, size_t destinySize) {
    for(size_t i = 0; i < destinySize; i++) {
      destinyArray[i] = arrayToCopy[i];
    }
  }


  template <typename T>
  typename std::enable_if<std::is_same<T, char>::value, void>::type
  ArrayUtils::copyArrayElements(const T *arrayToCopy, T *destinyArray, size_t destinySize, bool includeNullTerminator) {
    int i = 0;
    int destinySizeAux = includeNullTerminator ? destinySize - 1 : destinySize;
    while (i < destinySizeAux && arrayToCopy[i] != '\0'){
      destinyArray[i] = arrayToCopy[i];
      i++;
    }
    if(includeNullTerminator) {
      destinyArray[i] = '\0';
    }
  }

  template <typename T, typename Compare>
  void ArrayUtils::insertionSort(T* array, size_t size, Compare comp) {
    for (size_t i = 1; i < size; ++i) {
      T key = array[i];
      int j = static_cast<int>(i) - 1;
      while (j >= 0 && comp(key, array[j])) {
        array[j + 1] = array[j];
        --j;
      }
      array[j + 1] = key;
    }
  }

  template <typename T, typename Compare>
  void ArrayUtils::mergeSort(T* array, size_t size, Compare comp) {
    mergeSort(array, size, 0, static_cast<int>(size - 1), comp);
  }

  template <typename T, typename Compare>
  void ArrayUtils::mergeSort(T* array, size_t size, int left, int right, Compare comp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(array, size, left, mid, comp);
    mergeSort(array, size, mid + 1, right, comp);
    merge(array, left, mid, right, comp);
  }

  template <typename T, typename Compare>
  void ArrayUtils::merge(T* array, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* leftArray = new T[n1];
    T* rightArray = new T[n2];

    for (int i = 0; i < n1; ++i) {
      leftArray[i] = array[left + i];
    }

    for (int j = 0; j < n2; ++j) {
      rightArray[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
      if (!comp(rightArray[j], leftArray[i])) {
        array[k++] = leftArray[i++];
      } else {
        array[k++] = rightArray[j++];
      }
    }

    while (i < n1) array[k++] = leftArray[i++];
    while (j < n2) array[k++] = rightArray[j++];

    delete[] leftArray;
    delete[] rightArray;
  }

  template <typename T, typename Compare>
  void ArrayUtils::sort(T* array, size_t size, Compare comp) {
    if (size <= 32) {
      ArrayUtils::insertionSort(array, size, comp);
    } else {
      ArrayUtils::mergeSort(array, size, comp);
    }
  }
}
#endif
