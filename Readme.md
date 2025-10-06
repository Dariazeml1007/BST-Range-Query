# BST Range Query

A C++ implementation of a binary search tree with range query functionality, supporting key insertion and counting elements in specified ranges.

## Build and Run

### Build the project with user input:
```c
cmake -B build -D RUN_TESTS=OFF

cmake --build build

./build/binary_tree
```
### Build the project with tests:
```c
cmake -B build -D RUN_TESTS=ON
```
## Input and Output
Enter commands sequentially:

- k  <key> - Insert a key into the tree

- q <low> <high> - Count elements where low < key <= high

- dump - Generate tree visualization file
