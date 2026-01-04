#include <iostream>
#include "statistics.h"

void printStatistics(const std::vector<Block>& blocks, int totalMemory) {
    int usedMemory = 0;
    int freeMemory = 0;
    int allocatedBlocks = 0;
    int freeBlocks = 0;
    int largestFreeBlock = 0;

    for (const auto& b : blocks) {
        if (b.free) {
            freeMemory += b.size;
            freeBlocks++;
            if (b.size > largestFreeBlock)
                largestFreeBlock = b.size;
        } else {
            usedMemory += b.size;
            allocatedBlocks++;
        }
    }

    int externalFragmentation = freeMemory - largestFreeBlock;

    std::cout << "\nMemory Statistics\n";
    std::cout << "-----------------\n";
    std::cout << "Total Memory:           " << totalMemory << " bytes\n";
    std::cout << "Used Memory:            " << usedMemory << " bytes\n";
    std::cout << "Free Memory:            " << freeMemory << " bytes\n";
    std::cout << "Allocated Blocks:       " << allocatedBlocks << "\n";
    std::cout << "Free Blocks:            " << freeBlocks << "\n";
    std::cout << "Largest Free Block:     " << largestFreeBlock << " bytes\n";
    std::cout << "External Fragmentation: " << externalFragmentation << " bytes\n\n";
}

