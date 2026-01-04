#include "multilevel_cache.h"
#include <iostream>

MultiLevelCache::MultiLevelCache(
    int l1Size, int l1Block, int l1Assoc,
    int l2Size, int l2Block, int l2Assoc,
    ReplacementPolicy p
) {
    L1 = new Cache(l1Size, l1Block, l1Assoc, p);
    L2 = new Cache(l2Size, l2Block, l2Assoc, p);
}

void MultiLevelCache::access(int address) {
    std::cout << "Access address " << address << "\n";

    if (L1->access(address)) {
        std::cout << "L1 HIT\n";
        return;
    }

    std::cout << "L1 MISS\n";

    if (L2->access(address)) {
        std::cout << "L2 HIT → Promote to L1\n";
        L1->access(address);
        return;
    }

    std::cout << "L2 MISS → Main Memory\n";
    memoryAccesses++;

    // Fill both caches
    L2->access(address);
    L1->access(address);
}

void MultiLevelCache::stats() const {
    std::cout << "\nMulti-Level Cache Stats:\n";
    std::cout << "L1 → "; L1->stats();
    std::cout << "L2 → "; L2->stats();
    std::cout << "Main Memory Accesses: " << memoryAccesses << "\n";
}

void MultiLevelCache::dump() const {
    std::cout << "\n--- L1 Cache ---\n";
    L1->dump();
    std::cout << "\n--- L2 Cache ---\n";
    L2->dump();
}
