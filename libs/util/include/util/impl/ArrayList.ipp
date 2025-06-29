#ifndef UTIL_ARRAY_LIST_IPP
#define UTIL_ARRAY_LIST_IPP

#include <stdexcept>
#include <type_traits>
#include <string>
#include "../ArrayList.hpp"
#include "../ArrayUtils.hpp"

namespace util {

  template <typename T>
  void ArrayList<T>::resizeUp() {
    T *elementsAux = new T[capacity + DEFAULT_RESIZE];
    ArrayUtils::copyArrayElements(elements, elementsAux, length);
    delete[] elements;
    elements = elementsAux;
    capacity += DEFAULT_RESIZE;
  }

  template <typename T>
  void ArrayList<T>::resizeDown() {
    capacity = ((length + DEFAULT_RESIZE - 1) / DEFAULT_RESIZE) * DEFAULT_RESIZE;
    T *elementsAux = new T[capacity];
    ArrayUtils::copyArrayElements(elements, elementsAux, length);
    delete[] elements;
    elements = elementsAux;
  }

  template <typename T>
  void ArrayList<T>::validateIndex(int index) {
    if(index < 0 || index >= length) {
      throw std::out_of_range("Index out of bounds");
    }
  }

  template <typename T>
  void ArrayList<T>::add(T element) {
    if(length == capacity) {
      resizeUp();
    }
    elements[length] = element;
    length++;
  }


  template <typename T>
  void ArrayList<T>::remove(int index) {
    validateIndex(index);
    for(int i = index; i < length - 1; i++) {
      elements[i] = elements[i + 1];
    }
    length--;
    if(length <= capacity - DEFAULT_RESIZE) {
      resizeDown();
    }
  }

  template <typename T>
  void ArrayList<T>::remove(const T* element) {
    int indexAux = -1;
    int i = 0;

    do {
      if (elements[i] == *element) {
        indexAux = i;
      }
      i++;
    } while (indexAux == -1 && i < length);

    if (indexAux != -1) {
      remove(indexAux);
    }
  }

  template <typename T>
  T ArrayList<T>::get(int index) {
    validateIndex(index);
    return elements[index];
  }

  template <typename T>
  void ArrayList<T>::clear() {
    length = 0;
    delete[] elements;
    elements = new T[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
  }

  template <typename T>
  int ArrayList<T>::size() {
    return length;
  }

  template <typename T>
  bool ArrayList<T>::isEmpty() {
    return length == 0;
  }

  template <typename T>
  T* ArrayList<T>::data() {
    return elements;
  }

  template <typename T>
  template <typename Func>
  typename std::enable_if<
    std::is_same<
      void,
      decltype(std::declval<Func>()(std::declval<T>(), int{}))
    >::value, void
  >::type
  ArrayList<T>::forEach(Func func) {
    for (int i = 0; i < length; i++) {
        func(elements[i], i);
    }
  }

  template <typename T>
  template <typename Func>
  typename std::enable_if<
    std::is_same<
      void,
      decltype(std::declval<Func>()(std::declval<T>()))
    >::value, void
  >::type
  ArrayList<T>::forEach(Func func) {
    static_assert(
      std::is_same<void, decltype(std::declval<Func>()(std::declval<T>()))>::value,
      "Func needs to be callable with (T) and return void"
    );
    forEach([&func](T element, int) {
      func(element);
    });
  }

  template <typename T>
  template <typename Compare>
  typename std::enable_if<
    std::is_same<
      bool,
      decltype(std::declval<Compare>()(std::declval<T>(), std::declval<T>()))
    >::value, ArrayList<T>
  >::type
  ArrayList<T>::sort(Compare comp) const {
    ArrayList<T> result;
    result.length = length;
    result.capacity = capacity;
    result.elements = new T[capacity];

    for (int i = 0; i < length; ++i) {
      result.elements[i] = elements[i];
    }

    ArrayUtils::sort(result.elements, result.length, comp);

    return result;
  }

  template <typename T>
  template <typename Predicate>
  typename std::enable_if<
    std::is_same<bool, decltype(std::declval<Predicate>()(std::declval<T>()))>::value,
    ArrayList<T>
  >::type
  ArrayList<T>::filter(Predicate pred) const {
    ArrayList<T> result;
    for (int i = 0; i < length; ++i) {
      if (pred(elements[i])) {
        result.add(elements[i]);
      }
    }
    return result;
  }

  template <typename T>
  template <typename U>
  U ArrayList<T>::toComparable(U value) const {
    return value;
  }

  template <typename T>
  template <size_t N>
  std::string ArrayList<T>::toComparable(const char (&value)[N]) const {
    return std::string(value);
  }

  template <typename T>
  std::string ArrayList<T>::toComparable(const char* value) const {
    return std::string(value);
  }

  template <typename T>
  std::string ArrayList<T>::toComparable(char* value) const {
    return std::string(value);
  }

  template <typename T>
  std::string ArrayList<T>::toComparable(std::string value) const {
    return value;
  }

  template <typename T>
  template <typename FieldType, typename Extractor>
  const T* ArrayList<T>::findBy(FieldType target, Extractor getField) const {
    T** arrayAux = new T*[length];
    for (int i = 0; i < length; i++) {
      arrayAux[i] = &elements[i];
    }

    ArrayUtils::sort(arrayAux, length, [=](const T* a, const T* b) {
      return toComparable(getField(*a)) < toComparable(getField(*b));
    });

    int low = 0;
    int high = length - 1;
    std::string targetStr = toComparable(target);
    const T* result = nullptr;

    while (low <= high) {
      int mid = low + (high - low) / 2;
      std::string midVal = toComparable(getField(*arrayAux[mid]));

      if (midVal < targetStr) {
        low = mid + 1;
      } else if (targetStr < midVal) {
        high = mid - 1;
      } else {
        result = arrayAux[mid];
        break;
      }
    }

    delete[] arrayAux;
    return result;
  }

  template <typename T>
  ArrayList<T>::ArrayList() noexcept {
    length = 0;
    elements = new T[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
  }

  template <typename T>
  ArrayList<T>::ArrayList(const ArrayList& other) {
    capacity = other.capacity;
    length = other.length;
    ArrayUtils::copyArrayElements(other.elements, elements, length);
  }

  template <typename T>
  ArrayList<T>::ArrayList(ArrayList&& other) noexcept {
    elements = other.elements;
    capacity = other.capacity;
    length = other.length;

    other.elements = nullptr;
    other.capacity = 0;
    other.length = 0;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
    if (this == &other) return *this;

    delete[] elements;

    capacity = other.capacity;
    length = other.length;
    elements = new T[capacity];

    ArrayUtils::copyArrayElements(other.elements, elements, length);

    return *this;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other) noexcept {
    if (this == &other) return *this;

    delete[] elements;

    elements = other.elements;
    capacity = other.capacity;
    length = other.length;

    other.elements = nullptr;
    other.capacity = 0;
    other.length = 0;

    return *this;
  }

  template <typename T>
  ArrayList<T>::~ArrayList() {
    delete[] elements;
  }

}

#endif
