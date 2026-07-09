High-Performance C++ Chess Engine

A lightning-fast, custom-built chess bitboard written in modern C++. This project utilizes advanced data structures and low-level bitwise arithmetic to achieve highly efficient board representation and generating the attack tables.

🚀 Core Technologies & Algorithms

This engine eschews traditional 2D array board representations in favor of 64-bit integer Bitboards. By representing the board as a series of binary states, complex chess logic is reduced to single-cycle CPU instructions.

Advanced Move Generation

Ray-Casting & Collision Detection: Designed complex ray-casting algorithms to handle sliding pieces (Bishops, Rooks, Queens). Utilizing bitwise shifts and strict edge masks, the engine safely detects blockers and board boundaries without the need for expensive runtime loops or conditional branching.

Pre-Computed Lookup Tables: Generates exhaustive attack permutations during engine initialization. Every possible combination of blockers for every square on the board is calculated and stored in memory.

Magic Bitboards: Implements perfect hashing algorithms ("Magic Numbers") to compress sparse, 64-bit board occupancy states into dense array indices. This guarantees $O(1)$ constant-time move lookups for all sliding pieces during the game.

Performance Optimizations

Zero-branching move generation for sliding pieces.

Hardware-level bit manipulation using compiler intrinsics (e.g., __builtin_ctzll and __builtin_popcountll).


🛠️ Features

[x] Bitboard Representation: In a form of Unsigned Long Long 

[x] Magic Bitboards: Fully integrated with custom magic number tables for bishop rook and queen

Comiplation code: 
g++ -O3 -o chess_engine chess_engine.cpp

Note: The -O3 flag is highly recommended to enable compiler optimizations, which drastically improves node-per-second (NPS) search speeds.

Running the Engine
Execute the compiled binary:
./chess_engine
