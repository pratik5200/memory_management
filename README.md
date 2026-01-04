
# 📘 Design and Implementation of a Memory Management Simulator


A comprehensive Operating Systems Memory Management Simulator implemented in C++,
demonstrating dynamic memory allocation techniques and realistic CPU cache behavior using a multi-level cache hierarchy.

## 🔍 Overview

- This project simulates core memory management concepts used in operating systems, including:
- Heap memory allocation strategies
- Single-level and multi-level CPU cache simulation
- Cache hit/miss tracking with statistics
- Realistic cache behavior using tag, index, and offset
- Interactive Command Line Interface (CLI)

## 🎯 Objectives

- Understand how operating systems manage memory
- Compare different allocation strategies
- Simulate real CPU cache access logic
- Analyze cache performance using hit/miss statistics
- Provide a CLI-based tool for experimentation

## ✨ Features
### 🧠 Memory Allocation

- First Fit
- Best Fit
- Worst Fit
- Buddy Allocation

### 🧮 Cache Simulation

- Single-level cache
- Multi-level cache (L1 + L2)
- FIFO and LRU replacement policies
- Tag/index based cache lookup
- Per-level hit/miss statistics

### 🖥 Command Line Interface

- Interactive execution
- Clear output showing cache access paths
- Cache dump and statistics commands

## 🗂 Project Structure

memory_management/

├── include/

│   ├── allocator.h

│   ├── buddy_allocator.h

│   ├── cache.h

│   ├── multilevel_cache.h

│   └── statistics.h

│

├── src/

│   ├── allocator/

│   ├── buddy/

│   ├── cache/

│   ├── stats/

│   └── main.cpp

│

├── Makefile

├── README.md

├──tests/

└── docs/

## ⚙️ Build Instructions

### Supported Platforms

- Linux
- macOS
- Windows (using MinGW or WSL)
  
### 🔹 Linux / macOS
**Requirements**
- g++ (C++17 or later)
- make

Build 

     make    
Run

    ./memsim
    
- _I am using linux still i'll tell you how to use it in window_
### ✅ Option 1: Windows Subsystem for Linux (WSL) (Recommended
  
**Steps**

- Install WSL (Ubuntu) from Microsoft Store
- Open Ubuntu terminal
- Install build tools:
  
      sudo apt install build-essential
      sudo apt update
- Navigate to project folder
- Build and run:

      make
      ./memsim
### ✅ Option 2: MinGW (Native Windows)
**Requirements**

- MinGW-w64
- g++ with C++17 support
- make (mingw32-make)

**Build**

    mingw32-make
**Run**

    memsim.exe
**⚠️ Note:**

- Ensure MinGW bin directory is added to PATH
- Some Makefile adjustments may be required for Windows paths
### 🔹 Manual Compilation (Any Platform)

**If make is unavailable, compile manually:**

    g++ -std=c++17 src/main.cpp src/**/*.cpp -Iinclude -o memsim

## 🧑‍💻 CLI Commands
### 🔹 Memory Management
    init memory <size>
    set allocator first_fit
    set allocator best_fit
    set allocator worst_fit
    set allocator buddy
    malloc <size>
    free <id>
    dump
    stats
### 🔹 Single-Level Cache
    cache init <cache_size> <block_size> <fifo|lru>
    cache access <address>
    cache dump
    cache stats
### 🔹 Multi-Level Cache (L1 + L2)
    mlcache init <l1_size> <l1_block> <l2_size> <l2_block> <fifo|lru>
    mlcache access <address>
    mlcache dump
    mlcache stats
### 🔹Exit:

    exit
## 🧠 Design Highlights

- Memory addresses are divided into tag, index, and offset
- Cache lookup is performed by:
  - Selecting the correct cache set using index
  - Comparing tags within the set
- Cache misses propagate from **L1 → L2 → Main Memory**
- Statistics are maintained per cache level
## ⚠️ Common Problems Faced During Implementation
- Mismatch between function declarations in .h files and definitions in .cpp files
- Cache always returning MISS due to missing valid bit updates
- Incorrect tag/index calculation causing unrealistic cache behavior
- FIFO and LRU giving same results for simple access patterns
- Multi-level cache misses not properly propagating from L1 → L2 → Main Memory
- Makefile errors due to using spaces instead of TAB characters
## 🚀 Future Scope (Optional)

- LFU (Least Frequently Used) cache replacement
- L3 cache integration
- Virtual memory simulation (page tables, TLB)
- Access latency and AMAT calculation
- Graphical visualization of cache and memory
## 👤 Author

**_Pratik Jaisal_**

##
## ⭐ Star this repo if you find it useful!

