#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <map>
#include <vector>

class BuddyAllocator {
private:
    int totalSize;
    std::map<int, std::vector<int>> freeLists;
    std::map<int, int> allocated;  // address → size

    int nextPowerOfTwo(int size);
    int getBuddy(int addr, int size);

public:
    BuddyAllocator(int size);

    int allocate(int size);
    void freeBlock(int address);
    void dump();
};

#endif
