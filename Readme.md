# BST Range Query

A C++ implementation of a binary search tree with range query functionality, supporting key insertion and counting elements in specified ranges.
## Build and Run

### Build all targets:

```bash
cmake -B build
cmake --build build

Available targets:

./build/binary_tree - Main interactive application

./build/binary_tree_tests - Run unit tests

./build/binary_tree_benchmarks - AVL tree performance benchmarks

./build/set_benchmarks - std::set performance benchmarks
```
Use dump:

```bash
dot -Tpng tree.dot -o tree.png
explorer.exe tree.png
```

## Input and Output
Enter commands sequentially:

- k  <key> - Insert a key into the tree

- q <low> <high> - Count elements where low < key <= high

- dumpc  - Printing format Graphiz on  std::cout

##  Performance Comparison with std::set
During testing on a dataset of 10,000 random elements, a performance comparison of range query operations was conducted between MyTree and the standard std::set. The results demonstrate high implementation efficiency:

MyTree: 26 ms

std::set: 21 ms

Performance ratio: 1.24x
