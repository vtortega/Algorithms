#include "myPair.hpp"
template <typename T>
class Vector {
public:
    Vector() : size_(0), capacity_(10), data_(new T[capacity_]) {}

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), data_(new T[capacity_]) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(size_t initialSize, const T& initialValue)
        : size_(initialSize), capacity_(initialSize), data_(new T[initialSize]){
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = initialValue;
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    static bool sortbysec(const Pair<T, T>& a, const Pair<T, T>& b) {
        return a.second < b.second;
    }

    T* begin() {
        return data_;
    }

    const T* begin() const {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* end() const {
        return data_ + size_;
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    ~Vector() {
        delete[] data_;
    }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin_it() {
        return data_;
    }

    const_iterator begin_it() const {
        return data_;
    }

    iterator end_it() {
        return data_ + size_;
    }

    const_iterator end_it() const {
        return data_ + size_;
    }

private:
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    size_t size_;
    size_t capacity_;
    T* data_;
};