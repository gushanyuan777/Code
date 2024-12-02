#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include "HeapSort.h"

template<typename T>
bool check(const std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto& item : vec) {
        item = dis(gen);
    }
    return vec;
}

std::vector<int> generateOrderedSequence(size_t size) {
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = i + 1;
    }
    return vec;
}

std::vector<int> generateReverseSequence(size_t size) {
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = size - i;
    }
    return vec;
}

std::vector<int> generateRepetitiveSequence(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (auto& item : vec) {
        item = dis(gen);
    }
    for (size_t i = 0; i < size / 10; ++i) {
        size_t idx1 = rand() % size;
        size_t idx2 = rand() % size;
        std::swap(vec[idx1], vec[idx2]);
    }
    return vec;
}

int main() {
    size_t size = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec = generateRandomSequence(size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Generate random sequence time: " << diff.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    heapSort(vec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Heap sort time (random sequence): " << diff.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::sort_heap time (random sequence): " << diff.count() << " s" << std::endl;

    vec = generateOrderedSequence(size);

    start = std::chrono::high_resolution_clock::now();
    heapSort(vec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Heap sort time (ordered sequence): " << diff.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::sort_heap time (ordered sequence): " << diff.count() << " s" << std::endl;

    vec = generateReverseSequence(size);

    start = std::chrono::high_resolution_clock::now();
    heapSort(vec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Heap sort time (reverse sequence): " << diff.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::sort_heap time (reverse sequence): " << diff.count() << " s" << std::endl;

    vec = generateRepetitiveSequence(size);

    start = std::chrono::high_resolution_clock::now();
    heapSort(vec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Heap sort time (repetitive sequence): " << diff.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::sort_heap time (repetitive sequence): " << diff.count() << " s" << std::endl;

    return 0;
}