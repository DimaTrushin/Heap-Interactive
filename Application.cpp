#include "Application.h"
#include <iostream>

Application::Application() {
  Data_.subscribe(Printer.view());
}

void Application::run() {

  int msg;
  std::cout << kMenu;
  msg = std::cin.get();
  while (msg != kExit) {
    if (msg != kEnter) {
      handle_game_message(msg);
      std::cout << kMenu;
    }
    msg = std::cin.get();
  }
}

void Application::handle_game_message(const int msg) {
  // 48 -- 57 -- number keys
  static constexpr const int kA = 97;
  static constexpr const int kD = 100;
  switch (msg) {
  case kA:
    handle_adding();
    break;
  case kD:
    handle_deletion();
    break;
  default:
    break;
  }
  //  Printer.print(Data_);
}

void Application::handle_adding() {
  int msg;
  std::cout << kAddMenu;
  if (!wait_until_number())
    return;
  std::cin >> msg;
  Data_.add(msg);
}

void Application::handle_deletion() {
  int msg;
  if (Data_.isEmpty()) {
    std::cout << kEmptyDeletionMsg;
    return;
  }
  std::cout << kDeletMenu;
  std::cout << "range = 0 to " << Data_.size() - 1 << '\n';
  if (!wait_until_number())
    return;
  std::cin >> msg;
  while (msg < 0 || msg > int(Data_.size() - 1)) {
    if (!wait_until_number())
      return;
    std::cin >> msg;
  }
  Data_.remove(msg);
}

bool Application::wait_until_number() {
  int msg = std::cin.peek();
  while (msg < 48 || msg > 57) {
    std::cin.ignore();
    if (msg == kExit)
      return false;
    msg = std::cin.peek();
  }
  return true;
}
