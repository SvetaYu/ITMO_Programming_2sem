#pragma once

#include <iostream>

template<typename T>
class iterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
    explicit iterator(T *value) {
        this->value = value;
    }

    iterator(const iterator &other) {
        this->value = other.value;
    }

    iterator &operator=(const iterator &other) {
        this->value = other.value;
        return *this;
    }

    ~iterator() = default;

    bool operator==(iterator &other) const {
        return this->value == other.value;
    }

    bool operator!=(iterator &other) const {
        return this->value != other.value;
    }

    bool operator<(iterator &other) const {
        return this->value < other.value;
    }

    bool operator<=(iterator &other) const {
        return this->value <= other.value;
    }

    bool operator>(iterator &other) const {
        return this->value > other.value;
    }

    bool operator>=(iterator &other) const {
        return this->value >= other.value;
    }

    iterator &operator++() {
        value++;
        return *this;
    }

    iterator &operator--() {
        value--;
        return *this;
    }

    iterator &operator+=(int n) {
        value = value + n;
        return *this;
    }

    iterator &operator-=(int n) {
        value = value - n;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        value++;
        return temp;
    }

    iterator operator--(int) {
        iterator temp = *this;
        value--;
        return temp;
    }

    T &operator*() const {
        return *value;
    }

    T *operator->() const {
        return value;
    }

    T &operator[](int index) const {
        return value[index];
    }

    int operator-(iterator other) const {
        return this->value - other.value;
    }

    iterator operator+(int value) const {
        return iterator(this->value + value);
    }

    iterator operator-(int value) const {
        return iterator(this->value - value);
    }

    void advance(int n) {
        value += n;
    }

private:
    T *value;
};

template<typename T>
class circular_buffer {
public:
    typedef iterator<T> it;

    explicit circular_buffer(size_t capacity) {
        arr_ = new T[2 * capacity];
        capacity_ = capacity;
        head_ = tail_ = capacity;
    }

    circular_buffer(const circular_buffer &other) {
        this->arr_ = new T[2 * other.capacity_];
        memcpy(this->arr_, other.arr_, other.capacity_);
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->head_ = other.head_;
        this->tail_ = other.tail_;
    }

    ~circular_buffer() {
        delete[] arr_;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void resize(size_t const &newSize) {
        T *temp = new T[2 * newSize];
        size_t newStart = newSize - size_ / 2;
        if (newSize < capacity_) {
            for (size_t i = 0; i < newSize; ++i) {
                temp[newStart + i] = arr_[head_ + i];
            }
        } else {
            for (size_t i = 0; i < capacity_; ++i) {
                temp[newStart + i] = arr_[head_ + i];
            }
        }
        if (newSize < size_) {
            size_ = newSize;
        }
        delete[] arr_;
        arr_ = temp;
        head_ = newStart;
        tail_ = head_ + size_ - 1;
        capacity_ = newSize;
    }

    T &back() const {
        if (size_ == 0) {
            throw std::exception();
        }
        return arr_[tail_];
    }

    T &front() const {
        if (size_ == 0) {
            throw std::exception();
        }
        return arr_[head_];
    }

    void push_back(T value) {
        if (size_ == 0) {
            head_ = tail_ = capacity_;
            size_++;
        } else if (size_ == capacity_ && tail_ == 2 * capacity_ - 1) {
            head_ = left(capacity_ - 1 - size_ / 2) + 1;
        } else if (size_ == capacity_) {
            ++head_;
        } else if (tail_ == 2 * capacity_ - 1) {
            head_ = left(capacity_ - (size_ + 1) / 2);
            ++size_;
        } else {
            ++size_;
        }
        tail_ = head_ + size_ - 1;
        arr_[tail_] = value;
    }

    void push_front(T value) {
        if (size_ == 0) {
            head_ = tail_ = capacity_;
            ++size_;
        } else if (size_ == capacity_ && head_ == 0) {
            head_ = right(capacity_ + 1 - size_ / 2) - 1;
        } else if (size_ == capacity_) {
            --head_;
        } else if (head_ == 0) {
            head_ = right(capacity_ - (size_ - 1) / 2);
            ++size_;
        } else {
            --head_;
            ++size_;
        }
        arr_[head_] = value;
        tail_ = head_ + size_ - 1;
    }

    void pop_back() {
        if (!empty()) {
            --tail_;
            --size_;
        }
    }

    void pop_front() {
        if (!empty()) {
            ++head_;
            --size_;
        }
    }

    void clear() {
        size_ = 0;
        head_ = tail_ = capacity_;
    }

    const T &operator[](int index) const {
        if (index >= size_ || index < 0) {
            throw std::exception();
        }
        return arr_[head_ + index];
    }

    it begin() {
        it temp(arr_ + head_);
        return temp;
    }

    it end() {
        it temp(arr_ + tail_ + 1);
        return temp;
    }

private:
    T *arr_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
    size_t capacity_ = 0;

    size_t left(size_t start) {
        for (size_t i = 0; i < size_; ++i) {
            arr_[start + i] = arr_[head_ + i];
        }
        return start;
    }

    size_t right(size_t start) {
        for (size_t i = size_ - 1; i >= 0; ++i) {
            arr_[start + i] = arr_[head_ + i];
        }
        return start;
    }
};