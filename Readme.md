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
### Use dump :
```c
dot -Tpng tree.dot -o tree.png

explorer.exe tree.png
```

## Input and Output
Enter commands sequentially:

- k  <key> - Insert a key into the tree

- q <low> <high> - Count elements where low < key <= high

- dumpf filename - Generate tree visualization file

- dumpc  - Printing format Graphiz on  std::cout

##  Performance Comparison with std::set
During testing on a dataset of 10,000 random elements, a performance comparison of range query operations was conducted between MyTree and the standard std::set. The results demonstrate high implementation efficiency:

MyTree: 26 ms

std::set: 21 ms

Performance ratio: 1.24x
