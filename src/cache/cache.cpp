#include "cache.h"

Cache::Cache(int cSize, int bSize, int assoc, ReplacementPolicy p)
    : cacheSize(cSize), blockSize(bSize), associativity(assoc), policy(p) {

    int numLines = cacheSize / blockSize;
    numSets = numLines / associativity;

    sets.resize(numSets, std::vector<CacheLine>(associativity));
}

bool Cache::access(int address) {
    timer++;

    int blockAddr = address / blockSize;
    int index = blockAddr % numSets;
    int tag = blockAddr / numSets;

    // HIT check
    for (auto &line : sets[index]) {
        if (line.valid && line.tag == tag) {
            hits++;
            line.timestamp = timer; // LRU update
            return true;
        }
    }

    // MISS
    misses++;

    // Select victim
    int victim = 0;
    for (int i = 1; i < associativity; i++) {
        if (!sets[index][i].valid ||
            sets[index][i].timestamp < sets[index][victim].timestamp) {
            victim = i;
        }
    }

    sets[index][victim].valid = true;
    sets[index][victim].tag = tag;
    sets[index][victim].timestamp = timer;

    return false;
}

void Cache::dump() const {
    for (int i = 0; i < numSets; i++) {
        std::cout << "Set " << i << ": ";
        for (auto &line : sets[i]) {
            if (line.valid)
                std::cout << "[Tag=" << line.tag << "] ";
            else
                std::cout << "[INVALID] ";
        }
        std::cout << "\n";
    }
}

void Cache::stats() const {
    int total = hits + misses;
    std::cout << "Hits: " << hits
              << " Misses: " << misses
              << " Hit Ratio: "
              << (total ? (double)hits / total : 0)
              << "\n";
}


