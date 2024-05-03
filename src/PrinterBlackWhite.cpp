//
// Created by student on 2/05/24.
//

#include "PrinterBlackWhite.h"

PrinterBlackWhite::PrinterBlackWhite(
        const std::string &name, int emission, int speed, int cost) : Printer(name, emission, speed, cost) {}

PrinterBlackWhite::~PrinterBlackWhite() {}

std::string PrinterBlackWhite::getType() {
    return "Black-and-white printer";
}

