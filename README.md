
# 📘 Memory Management Simulator

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
    
- I am using linux still i'll tell you how to use it in window
  
