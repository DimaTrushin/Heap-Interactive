#ifndef APPLICATION_H
#define APPLICATION_H

#include "HeapPrinter.h"
#include "HeapT.h"

class Application {
public:
  Application();

  void run();

private:
  void handle_game_message(const int msg);
  void handle_adding();
  void handle_deletion();
  bool wait_until_number();

  static constexpr const int kEnter = 10;
  static constexpr const int kExit = 96;
  static constexpr const char kMenu[] =
      "a -- add key, d -- delete key, ` -- exit\n";
  static constexpr const char kAddMenu[] =
      "Type a number or ` to abort operation\n";
  static constexpr const char kDeletMenu[] =
      "Type index of an element to delete or ` to abort operator\n";
  static constexpr const char kEmptyDeletionMsg[] =
      "The heap is empty, you cannot delete an element\n";

  Heap<int64_t> Data_;
  HeapPrinter Printer;
  int64_t Word_ = 3;
};

#endif // APPLICATION_H
