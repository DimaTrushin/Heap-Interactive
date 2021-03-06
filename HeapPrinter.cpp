#include "HeapPrinter.h"

#include <algorithm>
#include <iostream>
#include <vector>

HeapPrinter::HeapPrinter(int64_t numberSize)
    : Word_(normalizeWord(numberSize)) {
}

int HeapPrinter::numberOfDigits(int64_t value) {
  if (value == 0)
    return 1;
  if (value < 0)
    return std::log10(-value) + 2;
  return std::log10(value) + 1;
}

void HeapPrinter::printWint(int64_t value) {

  int64_t digits = numberOfDigits(value);
  int64_t spaces = Word_ - digits;
  if (spaces < 0) {
    std::cout << value % int64_t(std::pow(2, Word_));
    return;
  }
  std::cout << std::string(spaces / 2, ' ');
  std::cout << value;
  std::cout << std::string(spaces - spaces / 2, ' ');
}

int64_t HeapPrinter::layerwidthw(int64_t layer) {
  return std::pow(2, layer) * (Word_ + 1) - 1;
}

void HeapPrinter::printLines(int64_t padding, int64_t space,
                             int64_t layerSize) {
  std::cout << std::string(padding + Word_ / 2, ' ');
  int64_t size = layerSize / 2;
  for (int64_t index = 0; index < size; ++index) {
    std::cout << char(-38);
    std::cout << std::string(Word_ / 2 + space / 2, char(-60));
    std::cout << char(-63);
    std::cout << std::string(Word_ / 2 + space / 2, char(-60));
    std::cout << char(-65);
    std::cout << std::string(Word_ - 1 + space, ' ');
  }
  std::cout << '\n';
}

std::vector<HeapPrinter::Spaces> HeapPrinter::getSpaces(const Container& data) {
  int64_t height = std::log2(data.size()) + 1;
  int64_t Width = layerwidthw(height - 1);

  std::vector<Spaces> SpaceData(height);
  int64_t k = height - 1;
  SpaceData[k] = {0, 1};
  --k;
  for (; k >= 0; --k) {
    SpaceData[k].padding = SpaceData[k + 1].padding + Word_ +
                           SpaceData[k + 1].space / 2 - Word_ / 2;
    SpaceData[k].space = std::max(
        0., (Width - std::pow(2, k) * Word_ - 2 * SpaceData[k].padding) /
                (std::pow(2, k) - 1));
  }
  return SpaceData;
}

int64_t HeapPrinter::printLayer(const Container& data, int64_t LayerSize,
                                int64_t Position, int64_t padding,
                                int64_t space) {
  std::cout << std::string(padding, ' ');
  int64_t End = Position + std::min<int64_t>(data.size() - Position, LayerSize);
  for (int64_t index = Position; index < End - 1; ++index) {
    printWint(data[index]);
    std::cout << std::string(space, ' ');
  }
  printWint(data[End - 1]);
  std::cout << std::string(padding, ' ') << '\n';
  return End;
}

void HeapPrinter::drawData(const DrawData& DrawData) {
  const Container& data = DrawData.data;
  if (data.empty()) {
    std::cout << "Empty\n";
    return;
  }
  SpaceData_ = getSpaces(data);

  int64_t LayerSize = 1;
  int64_t Position = 0;
  int64_t layer = 0;
  Position = printLayer(data, LayerSize, Position, SpaceData_[layer].padding,
                        SpaceData_[layer].space);
  LayerSize *= 2;
  ++layer;
  while (static_cast<size_t>(Position) < data.size()) {
    printLines(SpaceData_[layer].padding, SpaceData_[layer].space, LayerSize);
    Position = printLayer(data, LayerSize, Position, SpaceData_[layer].padding,
                          SpaceData_[layer].space);
    LayerSize *= 2;
    ++layer;
  }
}

int64_t HeapPrinter::normalizeWord(int64_t word) {
  if (word < 3)
    return 3;
  if (word % 2 == 0)
    ++word;
  return word;
}
