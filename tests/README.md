# Tests

This directory contains test cases for the Memory Management Simulator.

Planned tests:
- Allocator tests (first-fit, best-fit, worst-fit,buddy allocator)
- Cache hit/miss tests(single level)
- Multilevel cache (L1/L2) behavior tests



## Memory Management Simulator Test CLI Command

Type 'help' to see available commands
> help

Commands:

1.Allocator tests (first-fit, best-fit, worst-fit,buddy allocator)


    init memory <size>
    set allocator first_fit | best_fit | worst_fit | buddy
    malloc <size>
    free <id>
    dump
    stats
2.Cache hit/miss tests(single level)

    cache init <cache_size> <block_size> <fifo|lru>
    cache access <address>
    cache dump
    cache stats
3.Multilevel cache (L1/L2) behavior tests

    mlcache init <l1size> <l1block> <l2size> <l2block> <fifo|lru>
    mlcache access <address>
    mlcache dump
    mlcache stats
4.Exit

    exit

## 🟢 PHASE  — Dynamic Memory Allocation : INPUT 

    init memory 1024 
    set allocator first_fit
    malloc 100
    malloc 200
    malloc 50
    dump 
### OUTPUT 

    Memory initialized: 1024 bytes
    Allocator set to First Fit
    Allocated block id=1 using First Fit at address=0x0000 (size=100)
    Allocated block id=2 using First Fit at address=0x0064 (size=200)
    Allocated block id=3 using First Fit at address=0x012c (size=50)
- Memory Layout:
  
      [0x0000 - 0x0063] USED (id=1)
      [0x0064 - 0x012b] USED (id=2)
      [0x012c - 0x015d] USED (id=3)
      [0x015e - 0x03ff] FREE

### INPUT

    free 2
    dump
    stats
### OUTPUT

    Block id=2 freed successfully 
   - Adjacent free blocks merged
- Memory Layout:
  
      [0x0000 - 0x0063] USED (id=1)
      [0x0064 - 0x012b] FREE
      [0x012c - 0x015d] USED (id=3)
      [0x015e - 0x03ff] FREE
- Memory Statistics:

      Total Memory:           1024 bytes
      Used Memory:            150 bytes
      Free Memory:            874 bytes
      Allocated Blocks:        2
      Free Blocks:             2
      Largest Free Block:      674 bytes
      External Fragmentation:  200 bytes
 
- _you can try same as for best_fit,worst_fit_
## 🟢 PHASE  — Buddy Allocator : INPUT

    init memory 1024
    set allocator buddy
    malloc 100
    malloc 150
    malloc 120
    dump
### OUTPUT

    Memory initialized: 1024 bytes
    Allocator set to Buddy System
    Allocated 128 bytes at address 0x0
    Allocated 256 bytes at address 0x100
    Allocated 128 bytes at address 0x80
- Buddy Memory Layout:

      [0x0200 - 0x03ff] FREE (512)
      [0x0000 - 0x007f] USED (128)
      [0x0080 - 0x00ff] USED (128)
      [0x0100 - 0x01ff] USED (256)
  ###  Input
      free 0
      free 128
      dump
      stats
  ###  Output
      Freed block at address 0x0
      Freed block at address 0x80
  - Buddy Memory Layout:
    
        [0x0000 - 0x00ff] FREE (256)
        [0x0200 - 0x03ff] FREE (512)
        [0x0100 - 0x01ff] USED (256)
- Memory Statistics

      Total Memory:           1024 bytes
      Used Memory:            0 bytes
      Free Memory:            1024 bytes
      Allocated Blocks:       0
      Free Blocks:            1
      Largest Free Block:     1024 bytes
      External Fragmentation: 0 bytes
- 📐 External Fragmentation formula (logical):
  
       External Fragmentation = Total Free Memory − Largest Free Block
   - External fraggmentation is ZERO Because all free memory is coalesced into a single contiguous block by the buddy merging mechanism
- Buddy system has a very important property:

   - It always merges adjacent free buddies of the same size.

  - So fragmentation is automatically eliminated whenever possible.
  - ONE big FREE block of 1024 bytes ->buddy merging happened

## 🟢 PHASE  — Single-Level Cache (Real Cache Logic)
- there is two type of policy(replacemnt LRU,FIFO) but i am using FIFO you can use whatever you want
### INPUT
    cache init 64 16 fifo
    cache access 32
    cache access 32
    cache dump
    cache stats
### OUTPUT
    Cache initialized: 4 lines, Block 16 bytes, Policy fifo
    Access address 32
    Cache MISS
    Access address 32
    Cache HIT
cache dump

    Set 0: [INVALID] 
    Set 1: [INVALID] 
    Set 2: [Tag=0] 
    Set 3: [INVALID]
cache stats

    Hits: 1 Misses: 1 Hit Ratio: 0.5

## 🟢 PHASE  — Multi-Level Cache(L1 → L2 → Main Memory):Using FIFO
### INPUT 
    mlcache init 64 16 128 16 fifo
    mlcache access 32
    mlcache access 32
    mlcache dump
    mlcache stats
### OUTPUT 
    Multi-level cache initialized
    Access address 32
     L1 MISS
     L2 MISS → Main Memory
    Access address 32
      L1 HIT
 mlcache dump:

    --- L1 Cache ---
    Set 0: [INVALID] 
    Set 1: [INVALID] 
    Set 2: [Tag=0] 
    Set 3: [INVALID] 

    --- L2 Cache ---
    Set 0: [INVALID] 
    Set 1: [INVALID] 
    Set 2: [Tag=0] 
    Set 3: [INVALID] 
    Set 4: [INVALID] 
    Set 5: [INVALID] 
    Set 6: [INVALID] 
    Set 7: [INVALID]
mlcache stats:

Multi-Level Cache Stats:

    L1 → Hits: 2 Misses: 1 Hit Ratio: 0.666667
    L2 → Hits: 1 Misses: 1 Hit Ratio: 0.5
    Main Memory Accesses: 1
-----------------
 ⭐ THIS IS MY INPUT AND RESPECTIVE OUTPUT ⭐
