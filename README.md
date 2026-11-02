# College Club Membership Management System

A C++ Data Structures and Algorithms (DSA) project that implements a **College Club Membership Management System** using **Singly Linked Lists** and **Manual Hashing with Separate Chaining**.

## Project Overview

The project manages student membership IDs across multiple college clubs. It allows users to create clubs, manage memberships, search for members, and compare membership lists using fundamental data structures.

The main objective is to demonstrate the practical application of linked lists and hash tables in membership management.

## Features

- Create and manage multiple college clubs.
- Display all available clubs.
- Add members to a club.
- Remove members from a club.
- Search for a member using hashing.
- Display all members of a club.
- Compare two clubs using:
  - Union
  - Intersection
  - Members exclusive to Club A
  - Members exclusive to Club B
- Display membership statistics.
- Prevent duplicate membership IDs within a club.

## Data Structures and Algorithms

### 1. Singly Linked List
- Stores club membership IDs.
- Maintains the order in which members are added.
- Supports insertion, deletion and traversal.
- Uses dynamic memory allocation to create nodes.
- Traverses the list to insert new nodes at the end.

### 2. Hash Table with Separate Chaining
- Uses a manually implemented hash table.
- Hash function: `memberID % 101`
- Handles collisions using separate chaining.
- Supports membership searching and duplicate checking.

### 3. Membership Comparison

Hashing is used to perform:
- Union of two club membership lists.
- Intersection of two club membership lists.
- Finding members exclusive to either club.

## Technologies Used

- **Programming Language:** C++
- **Standard:** C++17
- **Concepts:** Object-Oriented Programming, Singly Linked Lists, Pointers, Dynamic Memory Allocation, Hash Tables and Separate Chaining.

## Time Complexity

| Operation | Time Complexity |
|---|---|
| Hash table search | O(1) average, O(n) worst |
| Hash table insertion | O(1) average, O(n) worst |
| Linked list insertion at end | O(n) |
| Linked list deletion | O(n) |
| Membership comparison | Expected O(n + m), collision-dependent worst case |

Here, `n` and `m` represent the number of members in the two clubs.

## How to Run

1. Clone or download this repository.
2. Open a terminal in the project directory.
3. Compile the C++ source file:

```bash
g++ -std=c++17 ccm_final.cpp -o club_management
```

4. Run the program:

```bash
./club_management
```

On Windows:

```bash
club_management.exe
```

## Project Structure

```text
college-club-membership-management/
│
├── README.md
├── ccm_final.cpp
└── DSA_Club_Membership_Report (1).pdf
```

## Limitations

- Membership data is stored in memory and is lost when the program exits.
- The hash table uses a fixed size of 101 buckets.
- The system stores membership IDs rather than complete student profiles.

## Project Deliverables

- **Source Code:** [ccm_final.cpp](./ccm_final.cpp)
- **Project Report:** [DSA Club Membership Report](./DSA_Club_Membership_Report%20%281%29.pdf)

## Author

**Aniruddha Kaje**

Computer Engineering / Information Technology

[GitHub Profile](https://github.com/aniruddha1127)

---

*Developed as a Data Structures and Algorithms academic project.*
