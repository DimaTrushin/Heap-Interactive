#ifndef HEAPPRINTER_H
#define HEAPPRINTER_H

#include "Colorizor.h"
#include "HeapT.h"
#include "Library/Observer/Observer.h"

class HeapPrinter {
  using CHeap = Heap<int64_t>;
  using Container = std::vector<int64_t>;

  using DrawData = CHeap::DrawData;
  using Format = DrawData::Format;
  using InputDrawData = NSLibrary::CHotInput<DrawData>;
  using ObserverDrawData = NSLibrary::CObserver<DrawData>;

public:
  struct Spaces {
    int64_t padding;
    int64_t space;
  };

  ObserverDrawData* view() {
    return &DrawDataView_;
  }

private:
  static int numberOfDigits(int64_t value);
  void printWint(int64_t value);
  int64_t layerwidthw(int64_t layer);
  void printLines(int64_t padding, int64_t space, int64_t layerSize);

  int64_t printLayer(const DrawData& DrawData, int64_t LayerSize,
                     int64_t Position, int64_t padding, int64_t space);
  std::vector<Spaces> getSpaces(const Container& heap);
  void drawData(const DrawData& DrawData);
  void chooseColor(const Format& DrawData, int64_t position);
  void resetColor();

  InputDrawData DrawDataView_ = [this](const DrawData& data) {
    drawData(data);
  };
  std::vector<Spaces> SpaceData_;
  Colorizor Brush_;
  int64_t Word_ = 3;
};

#endif // HEAPPRINTER_H
