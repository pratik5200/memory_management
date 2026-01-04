#include <iostream>
#include <sstream>
#include <string>

#include "allocator.h"
#include "buddy_allocator.h"
#include "statistics.h"
#include "cache.h"
#include "multilevel_cache.h"

int main() {
    std::cout << "Memory Management Simulator\n";
    std::cout << "Type 'help' to see available commands\n";

    Allocator* allocator = nullptr;
    BuddyAllocator* buddy = nullptr;

    Cache* cache = nullptr;
    MultiLevelCache* mlcache = nullptr;

    bool useBuddy = false;

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        /* ---------------- HELP ---------------- */
        if (cmd == "help") {
            std::cout <<
                "Commands:\n"
                "init memory <size>\n"
                "set allocator first_fit | best_fit | worst_fit | buddy\n"
                "malloc <size>\n"
                "free <id>\n"
                "dump\n"
                "stats\n\n"

                "cache init <cache_size> <block_size> <fifo|lru>\n"
                "cache access <address>\n"
                "cache dump\n"
                "cache stats\n\n"

                "mlcache init <l1size> <l1block> <l2size> <l2block> <fifo|lru>\n"
                "mlcache access <address>\n"
                "mlcache dump\n"
                "mlcache stats\n\n"

                "exit\n";
        }

        /* ---------------- INIT MEMORY ---------------- */
        else if (cmd == "init") {
            std::string what;
            ss >> what;

            if (what == "memory") {
                int size;
                ss >> size;

                delete allocator;
                allocator = new Allocator(size);

                std::cout << "Memory initialized: " << size << " bytes\n";
            }
        }

        /* ---------------- SET ALLOCATOR ---------------- */
        else if (cmd == "set") {
            std::string what, type;
            ss >> what >> type;

            if (what == "allocator") {
                if (type == "buddy") {
                    delete buddy;
                    buddy = new BuddyAllocator(allocator->getMemorySize());
                    useBuddy = true;
                    std::cout << "Allocator set to Buddy System\n";
                } else {
                    useBuddy = false;
                    if (type == "first_fit")
                        allocator->setStrategy(Strategy::FIRST_FIT);
                    else if (type == "best_fit")
                        allocator->setStrategy(Strategy::BEST_FIT);
                    else if (type == "worst_fit")
                        allocator->setStrategy(Strategy::WORST_FIT);
                }
            }
        }

        /* ---------------- MALLOC ---------------- */
        else if (cmd == "malloc") {
            int size;
            ss >> size;

            if (useBuddy)
                buddy->allocate(size);
            else
                allocator->allocate(size);
        }

        /* ---------------- FREE ---------------- */
        else if (cmd == "free") {
            int id;
            ss >> id;

            if (useBuddy)
                buddy->freeBlock(id);
            else
                allocator->freeBlock(id);
        }

        /* ---------------- DUMP ---------------- */
        else if (cmd == "dump") {
            if (useBuddy)
                buddy->dump();
            else
                allocator->dump();
        }

        /* ---------------- STATS ---------------- */
        else if (cmd == "stats") {
            printStatistics(
                allocator->getBlocks(),
                allocator->getMemorySize()
            );
        }

        /* ---------------- SINGLE CACHE ---------------- */
        else if (cmd == "cache") {
            std::string sub;
            ss >> sub;

            if (sub == "init") {
                int cSize, bSize;
                std::string pol;
                ss >> cSize >> bSize >> pol;

                ReplacementPolicy policy =
                    (pol == "lru") ? ReplacementPolicy::LRU
                                   : ReplacementPolicy::FIFO;

                delete cache;
                cache = new Cache(cSize, bSize, 1, policy);

                std::cout << "Cache initialized: "
                          << (cSize / bSize)
                          << " lines, Block "
                          << bSize
                          << " bytes, Policy "
                          << pol << "\n";
            }

            else if (sub == "access") {
                int addr;
                ss >> addr;

                if (cache) {
                    std::cout << "Access address " << addr << "\n";
                    bool hit = cache->access(addr);
                    std::cout << (hit ? "Cache HIT\n" : "Cache MISS\n");
                }
            }

            else if (sub == "dump") {
                if (cache) cache->dump();
            }

            else if (sub == "stats") {
                if (cache) cache->stats();
            }
        }

        /* ---------------- MULTI-LEVEL CACHE ---------------- */
        else if (cmd == "mlcache") {
            std::string sub;
            ss >> sub;

            if (sub == "init") {
                int l1s, l1b, l2s, l2b;
                std::string pol;
                ss >> l1s >> l1b >> l2s >> l2b >> pol;

                ReplacementPolicy policy =
                    (pol == "lru") ? ReplacementPolicy::LRU
                                   : ReplacementPolicy::FIFO;

                delete mlcache;
                mlcache = new MultiLevelCache(
                    l1s, l1b, 1,
                    l2s, l2b, 1,
                    policy
                );

                std::cout << "Multi-level cache initialized\n";
            }

            else if (sub == "access") {
                int addr;
                ss >> addr;
                if (mlcache) mlcache->access(addr);
            }

            else if (sub == "stats") {
                if (mlcache) mlcache->stats();
            }

            else if (sub == "dump") {
                if (mlcache) mlcache->dump();
            }
        }

        /* ---------------- EXIT ---------------- */
        else if (cmd == "exit") {
            break;
        }

        else {
            std::cout << "Unknown command. Type 'help'\n";
        }
    }

    return 0;
}




