#include <iostream>
#include <iomanip>
#include "allocator.h"

WorstFitAllocator::WorstFitAllocator(int size)
    : FirstFitAllocator(size) {}

int WorstFitAllocator::allocate(int size) {
    int worstIndex = -1;
    int worstSize = -1;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            if (blocks[i].size > worstSize) {
                worstSize = blocks[i].size;
                worstIndex = i;
            }
        }
    }

    if (worstIndex == -1) {
        std::cout << "Allocation failed: Not enough memory\n";
        return -1;
    }

    int id = nextId++;

    if (blocks[worstIndex].size > size) {
        Block remaining;
        remaining.id = 0;
        remaining.start = blocks[worstIndex].start + size;
        remaining.size = blocks[worstIndex].size - size;
        remaining.free = true;

        blocks.insert(blocks.begin() + worstIndex + 1, remaining);
    }

    blocks[worstIndex].size = size;
    blocks[worstIndex].id = id;
    blocks[worstIndex].free = false;

    std::cout << "Allocated block id=" << id
              << " using Worst Fit at address=0x"
              << std::hex << blocks[worstIndex].start
              << std::dec << " (size=" << size << ")\n";

    return id;
}
