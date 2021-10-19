#include "Colorizor.h"

#include <iostream>

Colorizor::Colorizor() : hConsole_(GetStdHandle(STD_OUTPUT_HANDLE)) {
  std::cout << "hConsole_ = " << hConsole_ << '\n';
  CONSOLE_SCREEN_BUFFER_INFO buffer;
  GetConsoleScreenBufferInfo(hConsole_, &buffer);
  DefaultAttributes_ = buffer.wAttributes;
  std::cout << "default attr = " << DefaultAttributes_ << '\n';
}

void Colorizor::setColor(int k) {
  SetConsoleTextAttribute(hConsole_, k);
}

void Colorizor::setRedOnBlack() {
  SetConsoleTextAttribute(hConsole_, 12);
}

void Colorizor::setGreenOnBlack() {
  SetConsoleTextAttribute(hConsole_, 10);
}

void Colorizor::setBlueOnBlack() {
  SetConsoleTextAttribute(hConsole_, 11);
}

void Colorizor::setDefault() {
  SetConsoleTextAttribute(hConsole_, DefaultAttributes_);
}
