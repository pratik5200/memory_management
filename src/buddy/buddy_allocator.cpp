#include<bits/stdc++.h>
#include <iostream>
using namespace std;
#include <iomanip>
#include "buddy_allocator.h"

BuddyAllocator::BuddyAllocator(int size) {
    totalSize = size;
    freeLists[size].push_back(0);
}

int BuddyAllocator::nextPowerOfTwo(int size) {
    int p = 1;
    while (p < size) p <<= 1;
    return p;
}

int BuddyAllocator::getBuddy(int addr, int size) {
    return addr ^ size;
}

int BuddyAllocator::allocate(int size) {
    int req = nextPowerOfTwo(size);

    int blockSize = req;
    while (blockSize <= totalSize && freeLists[blockSize].empty()) {
        blockSize <<= 1;
    }

    if (blockSize > totalSize) {
        std::cout << "Buddy allocation failed\n";
        return -1;
    }

    int addr = freeLists[blockSize].back();
    freeLists[blockSize].pop_back();

    while (blockSize > req) {
        blockSize >>= 1;
        freeLists[blockSize].push_back(addr + blockSize);
    }

    allocated[addr] = req;

    std::cout << "Allocated " << req
              << " bytes at address 0x"
              << std::hex << addr << std::dec << "\n";

    return addr;
}

void BuddyAllocator::freeBlock(int address) {
    if (!allocated.count(address)) {
        std::cout << "Invalid buddy free\n";
        return;
    }

    int size = allocated[address];
    allocated.erase(address);

    int currAddr = address;
    int currSize = size;

    while (currSize < totalSize) {
        int buddy = getBuddy(currAddr, currSize);
        auto &list = freeLists[currSize];

        auto it = std::find(list.begin(), list.end(), buddy);
        if (it == list.end())
            break;

        list.erase(it);
        currAddr = std::min(currAddr, buddy);
        currSize <<= 1;
    }

    freeLists[currSize].push_back(currAddr);

    std::cout << "Freed block at address 0x"
              << std::hex << address << std::dec << "\n";
}

void BuddyAllocator::dump() {
    std::cout << "\nBuddy Memory Layout:\n";

    for (auto &pair : freeLists) {
        int size = pair.first;
        for (int addr : pair.second) {
            std::cout << "[0x"
                      << std::hex << std::setw(4) << std::setfill('0')
                      << addr << " - 0x"
                      << std::setw(4) << (addr + size - 1)
                      << std::dec
                      << "] FREE (" << size << ")\n";
        }
    }

    for (auto &pair : allocated) {
        int addr = pair.first;
        int size = pair.second;
        std::cout << "[0x"
                  << std::hex << std::setw(4) << std::setfill('0')
                  << addr << " - 0x"
                  << std::setw(4) << (addr + size - 1)
                  << std::dec
                  << "] USED (" << size << ")\n";
    }
}
