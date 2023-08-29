#include "FreeChanks.cpp"

class block {
public:
    block(size_t size, size_t number, void *start) {
        this->start = start;
        this->end = (void *) ((uint8_t *) start + number * size);
        this->chunksSize = size;
        uint8_t *ptr = (uint8_t *) start;
        while (ptr != end) {
            freeChunks.push((node *) ptr);
            ptr += size;
        }
    }

    void *pop() {
        return freeChunks.pop();
    }

    void push(node *ptr) {
        freeChunks.push((node *) ptr);
    }

    size_t getChunksSize() const {
        return chunksSize;
    }

    bool freeChunksEmpty() {
        return freeChunks.empty();
    }

    bool chunkFromThisBlock(void *ptr, size_t n) {
        if (ptr < end && ptr >= start)
            if (((uint8_t *) ptr - (uint8_t *) start) % chunksSize == 0 && n <= chunksSize)
                return true;
            else
                throw std::exception();
        else
            return false;
    }

private:
    size_t chunksSize;
    freeChunks freeChunks;
    void *start;
    void *end;
};