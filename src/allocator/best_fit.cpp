#include <iostream>
#include <iomanip>
#include "allocator.h"

BestFitAllocator::BestFitAllocator(int size)
    : FirstFitAllocator(size) {}

int BestFitAllocator::allocate(int size) {
    int bestIndex = -1;
    int bestSize = 1e9;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            if (blocks[i].size < bestSize) {
                bestSize = blocks[i].size;
                bestIndex = i;
            }
        }
    }

    if (bestIndex == -1) {
        std::cout << "Allocation failed: Not enough memory\n";
        return -1;
    }

    int id = nextId++;

    if (blocks[bestIndex].size > size) {
        Block remaining;
        remaining.id = 0;
        remaining.start = blocks[bestIndex].start + size;
        remaining.size = blocks[bestIndex].size - size;
        remaining.free = true;

        blocks.insert(blocks.begin() + bestIndex + 1, remaining);
    }

    blocks[bestIndex].size = size;
    blocks[bestIndex].id = id;
    blocks[bestIndex].free = false;

    std::cout << "Allocated block id=" << id
              << " using Best Fit at address=0x"
              << std::hex << blocks[bestIndex].start
              << std::dec << " (size=" << size << ")\n";

    return id;
}
