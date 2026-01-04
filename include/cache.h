#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <iostream>

enum class ReplacementPolicy {
    FIFO,
    LRU
};

struct CacheLine {
    bool valid = false;
    int tag = -1;
    int timestamp = 0;   // for FIFO/LRU
};

class Cache {
private:
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;

    int timer = 0;

    ReplacementPolicy policy;
    std::vector<std::vector<CacheLine>> sets;

    int hits = 0;
    int misses = 0;

public:
    Cache(int cSize, int bSize, int assoc, ReplacementPolicy p);

    bool access(int address);
    void dump() const;
    void stats() const;

    int getHits() const { return hits; }
    int getMisses() const { return misses; }
};

#endif
