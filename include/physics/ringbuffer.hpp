#pragma once

#include <raylib.h>
#include <vector>

template <typename T>
class RingBuffer {
public:
    RingBuffer() {}
    RingBuffer(size_t capacity): _capacity(capacity) {
        _data.resize(_capacity);
        _head = _tail = _size = 0;
    }
    ~RingBuffer() = default;

    void record(const T& position) {
        _data[_head] = position;
        _head = (_head + 1) % _capacity;

        if (_size < _capacity) _size++;
        else _tail = (_tail + 1) % _capacity;
    }

    void erase() { _head = _tail = _size = 0; }

    const size_t& capacity() const { return _capacity; }

    const size_t& size() const { return _size; }

    const T& at(const size_t& frame) const {
        size_t idx = frame;
        if (frame >= _size) idx = (_size > 0) ? (_size - 1) : 0;
        idx = _head + _capacity - idx - 1;
        return _data[(idx) % _capacity];
    }

    T& at(const size_t& frame) {
        size_t idx = frame;
        if (frame >= _size) idx = (_size > 0) ? (_size - 1) : 0;
        idx = _head + _capacity - idx - 1;
        return _data[(idx) % _capacity];
    }
private:
    std::vector<T> _data;

    size_t _head;
    size_t _tail;

    size_t _size;
    size_t _capacity;
};

