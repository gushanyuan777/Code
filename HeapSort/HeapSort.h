#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <vector>
#include <algorithm>
#include <iterator>

template<typename T>
void _heapify(std::vector<T>& vec, size_t i, size_t n) {
    size_t smallest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && vec[left] < vec[smallest]) {
        smallest = left;
    }

    if (right < n && vec[right] < vec[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        std::swap(vec[i], vec[smallest]);
        _heapify(vec, smallest, n);
    }
}
template<typename T>
void heapSort(std::vector<T>& vec) {
    size_t n = vec.size();

    for (size_t i = n / 2 - 1; i >= 0; --i) {
        _heapify(vec, i, n);
    }

    for (size_t i = n - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]);
        _heapify(vec, 0, i);
    }
}

#endif // HEAPSORT_H