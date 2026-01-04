#include <iostream>
#include <iomanip>
#include <climits>
#include "allocator.h"

/* =========================
   Constructor
   ========================= */
Allocator::Allocator(int size) {
    memorySize = size;
    nextId = 1;
    strategy = Strategy::FIRST_FIT;
    blocks.push_back({0, 0, size, true});   // one big free block
}

/* =========================
   Set allocation strategy
   ========================= */
void Allocator::setStrategy(Strategy s) {
    strategy = s;
}

/* =========================
   Allocate memory
   ========================= */
int Allocator::allocate(int size) {
    int index = -1;

    // -------- First Fit --------
    if (strategy == Strategy::FIRST_FIT) {
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= size) {
                index = i;
                break;
            }
        }
    }
    // -------- Best Fit --------
    else if (strategy == Strategy::BEST_FIT) {
        int bestSize = INT_MAX;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= size &&
                blocks[i].size < bestSize) {
                bestSize = blocks[i].size;
                index = i;
            }
        }
    }
    // -------- Worst Fit --------
    else if (strategy == Strategy::WORST_FIT) {
        int worstSize = -1;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= size &&
                blocks[i].size > worstSize) {
                worstSize = blocks[i].size;
                index = i;
            }
        }
    }

    if (index == -1) {
        std::cout << "Allocation failed: Not enough memory\n";
        return -1;
    }

    int id = nextId++;

    // Split block if needed
    if (blocks[index].size > size) {
        Block remaining;
        remaining.id = 0;
        remaining.start = blocks[index].start + size;
        remaining.size = blocks[index].size - size;
        remaining.free = true;

        blocks.insert(blocks.begin() + index + 1, remaining);
    }

    blocks[index].size = size;
    blocks[index].id = id;
    blocks[index].free = false;

    std::string algo =
        (strategy == Strategy::FIRST_FIT) ? "First Fit" :
        (strategy == Strategy::BEST_FIT)  ? "Best Fit"  :
                                            "Worst Fit";

    std::cout << "Allocated block id=" << id
              << " using " << algo
              << " at address=0x"
              << std::hex << std::setw(4) << std::setfill('0')
              << blocks[index].start << std::dec
              << " (size=" << size << ")\n";

    return id;
}

/* =========================
   Free memory block
   ========================= */
void Allocator::freeBlock(int id) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (!blocks[i].free && blocks[i].id == id) {

            blocks[i].free = true;
            blocks[i].id = 0;

            // Merge with next block
            if (i + 1 < blocks.size() && blocks[i + 1].free) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            // Merge with previous block
            if (i > 0 && blocks[i - 1].free) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }

            std::cout << "Block id=" << id << " freed successfully\n";
            return;
        }
    }

    std::cout << "Error: Invalid block ID\n";
}

/* =========================
   Dump memory layout
   ========================= */
void Allocator::dump() {
    std::cout << "Memory Layout:\n";
    for (auto &b : blocks) {
        std::cout << "[0x"
                  << std::hex << std::setw(4) << std::setfill('0')
                  << b.start << " - 0x"
                  << std::setw(4) << (b.start + b.size - 1)
                  << std::dec << "] ";

        if (b.free)
            std::cout << "FREE\n";
        else
            std::cout << "USED (id=" << b.id << ")\n";
    }
}

/* ==================================================
   PHASE-3 ADDITIONS (READ-ONLY ACCESS FOR STATISTICS)
   ================================================== */

const std::vector<Block>& Allocator::getBlocks() const {
    return blocks;
}

int Allocator::getMemorySize() const {
    return memorySize;
}


