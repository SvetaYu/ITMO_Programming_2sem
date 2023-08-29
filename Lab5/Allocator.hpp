#pragma once

#include <cstdlib>
#include <vector>
#include "Block.cpp"


template<typename T=void>
class allocator {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;

    allocator(size_t number, std::vector<size_t> sizes, std::vector<size_t> numbers) {
        size_t maxSize = 0;
        for (size_t i = 0; i < number; ++i) {
            maxSize += sizes[i] * numbers[i];
        }
        pool = malloc(maxSize);
        blocks = new std::vector<block>;
        uint8_t *ptr = (uint8_t *) pool;
        for (size_t i = 0; i < number; ++i) {
            blocks->emplace_back(block(sizes[i], numbers[i], (node *) ptr));
            ptr += sizes[i] * numbers[i];
        }
        numberOfCopies = new size_t;
        *numberOfCopies = 1;
    }

    ~allocator() {
        if (*numberOfCopies == 1) {
            free(pool);
            delete (blocks);
            delete (numberOfCopies);
        }
        --(*numberOfCopies);
    }

    template<typename Tp>
    allocator(const allocator<Tp> &other) {
        this->pool = other.pool;
        this->blocks = other.blocks;
        this->numberOfCopies = other.numberOfCopies;
        ++(*numberOfCopies);
    }

    template<typename Tp>
    allocator &operator=(const allocator<T> &other) {
        if (*(this->numberOfCopies) != 1)
            --(*(this->numberOfCopies));
        else {
            free(this->pool);
            delete (this->blocks);
            delete (this->numberOfCopies);
        }
        *this(other);
        return *this;
    }


    pointer allocate(size_t n) {
        size_t size = n * sizeof(T);
//        std::cout << "ALLOCATE  " << size << std::endl;
        size_t minBlock = UINT64_MAX;
        block *suitableBlock;
        for (auto &block: *blocks) {
            size_t blocksSize = block.getChunksSize();
            if (blocksSize >= size && blocksSize < minBlock && !block.freeChunksEmpty()) {
                minBlock = blocksSize;
                suitableBlock = &block;
            }
        }
        if (minBlock == UINT64_MAX)
            throw std::exception();
        return (pointer) suitableBlock->pop();
    }

    void deallocate(void *ptr, size_t n) {
//        std::cout << "DEALLOCATE  " << n * sizeof(T) << std::endl;
        for (auto &block: *blocks) {
            try {
                if (block.chunkFromThisBlock(ptr, n * sizeof(T))) {
                    block.push((node *) ptr);
                    break;
                }
            }
            catch (std::exception &ex) {
                break;
            }
        }
    }

    template<class Tp>
    struct rebind {
        typedef allocator<Tp> other;
    };

    void *pool = nullptr;
    std::vector<block> *blocks{};
    size_t *numberOfCopies{};
};

template<class Tp, class U>
bool operator==(const allocator<Tp> &, const allocator<U> &) { return true; }

template<class Tp, class U>
bool operator!=(const allocator<Tp> &, const allocator<U> &) { return false; }