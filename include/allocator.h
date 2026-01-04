#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <vector>
#include "block.h"

enum class Strategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class Allocator {
protected:
    std::vector<Block> blocks;
    int memorySize;
    int nextId;
    Strategy strategy;

public:
    Allocator(int size);

    void setStrategy(Strategy s);

    int allocate(int size);
    void freeBlock(int id);
    void dump();

    // 🔹 PHASE-3 ADDITIONS
    const std::vector<Block>& getBlocks() const;
    int getMemorySize() const;

    ~Allocator() {}
};

#endif


