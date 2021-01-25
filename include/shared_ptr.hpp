// Copyright 2021 Slava-100 <svat.strel.2001@gmail.com>

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <atomic>

template <typename T>
class shared_ptr {
 public:
  shared_ptr();
  explicit shared_ptr(T* ptr);
  shared_ptr(const shared_ptr& r);

  shared_ptr(shared_ptr&& r) noexcept;
  ~shared_ptr();

  shared_ptr& operator=(const shared_ptr& r);
  shared_ptr& operator=(shared_ptr&& r) noexcept;

  operator bool() const;
  T& operator*() const;
  T* operator->() const;

  T* get();
  void reset();
  void reset(T* ptr);
  void swap(shared_ptr& r);
  std::size_t use_count() const;

 private:
  std::atomic_uint* _counter;
  T* _object;
};

template <typename T>
shared_ptr<T>::shared_ptr() : _counter(nullptr), _object(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : _counter(new std::atomic_uint(1)), _object(ptr) {
  if (!ptr) {
    delete _counter;
    _counter = nullptr;
  }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& r)
    : _counter(r._counter), _object(r._object) {
  ++(*_counter);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& r) noexcept
    : _counter(nullptr), _object(nullptr) {
  std::swap(_counter, r._counter);
  std::swap(_object, r._object);
}


template <typename T>
shared_ptr<T>::~shared_ptr() {
  if (!_counter) return;
  if (--(*_counter) == 0) {
    delete _counter;
    delete _object;
  }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& r) {
  if (r == *this) return *this;
  reset();
  _object = r._object;
  _counter = r._counter;
  ++(*_counter);
  return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& r) noexcept {
  if (r == *this) return *this;
  reset();
  std::swap(_counter, r._counter);
  std::swap(_object, r._object);
  return *this;
}

template <typename T>
shared_ptr<T>::operator bool() const {
  return _object != nullptr;
}

template <typename T>
T& shared_ptr<T>::operator*() const {
  return *_object;
}

template <typename T>
T* shared_ptr<T>::operator->() const {
  return _object;
}

template <typename T>
T* shared_ptr<T>::get() {
  return _object;
}

template <typename T>
void shared_ptr<T>::reset() {
  if (!_counter) return;

  if (--(*_counter) == 0) {
    delete _object;
    delete _counter;
  }

  _object = nullptr;
  _counter = nullptr;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
  reset();
  _object = ptr;
  _counter = new std::atomic_uint(1);
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& r) {
  std::swap(_counter, r._counter);
  std::swap(_object, r._object);
}

template <typename T>
std::size_t shared_ptr<T>::use_count() const {
  if (!_counter) return 0;
  return *_counter;
}

#endif  // INCLUDE_SHARED_PTR_HPP_
