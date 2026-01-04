#ifndef MULTILEVEL_CACHE_H
#define MULTILEVEL_CACHE_H

#include "cache.h"

class MultiLevelCache {
private:
    Cache *L1;
    Cache *L2;

    int memoryAccesses = 0;

public:
    MultiLevelCache(
        int l1Size, int l1Block, int l1Assoc,
        int l2Size, int l2Block, int l2Assoc,
        ReplacementPolicy p
    );

    void access(int address);
    void stats() const;
    void dump() const;
};

#endif
