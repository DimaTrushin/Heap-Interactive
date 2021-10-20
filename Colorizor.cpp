#include "Colorizor.h"

#include <iostream>

Colorizor::Colorizor() : hConsole_(GetStdHandle(STD_OUTPUT_HANDLE)) {
  CONSOLE_SCREEN_BUFFER_INFO buffer;
  GetConsoleScreenBufferInfo(hConsole_, &buffer);
  DefaultAttributes_ = buffer.wAttributes;
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

namespace {
void cls(HANDLE hConsole) {
  COORD coordScreen = {0, 0};
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;
  GetConsoleScreenBufferInfo(hConsole, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen,
                             &cCharsWritten);
  GetConsoleScreenBufferInfo(hConsole, &csbi);
  FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen,
                             &cCharsWritten);
  SetConsoleCursorPosition(hConsole, coordScreen);
}

} // namespace

void Colorizor::clear() {
  cls(hConsole_);
}
