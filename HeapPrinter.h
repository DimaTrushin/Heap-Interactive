#ifndef HEAPPRINTER_H
#define HEAPPRINTER_H

#include "HeapT.h"

class HeapPrinter {
  using CHeap = Heap<int64_t>;
public:
  struct Spaces {
    int64_t padding;
    int64_t space;
  };
    void print(const CHeap& heap);
private:
  static int numberOfDigits(int64_t value);
  void printWint(int64_t value);
  int64_t layerwidthw(int64_t layer);
  void printPaddings(const std::vector<Spaces>& Container);
  int64_t printHeapLayerNice(const CHeap& heap, int64_t LayerSize,
                             int64_t Position, int64_t padding, int64_t space);
  void printLines(int64_t padding, int64_t space, int64_t layerSize);
  std::vector<Spaces> getSpaces(const CHeap& heap);

  std::vector<Spaces> SpaceData_;
  int64_t Word_ = 3;
};

#endif // HEAPPRINTER_H
