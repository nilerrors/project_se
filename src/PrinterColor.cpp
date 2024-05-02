//
// Created by student on 2/05/24.
//

#include "PrinterColor.h"

PrinterColor::PrinterColor(TiXmlElement *device_element) : Printer(device_element) {}

PrinterColor::PrinterColor(const std::string &name, int emission, int speed, int cost) : Printer(name, emission, speed, cost) {}

PrinterColor::~PrinterColor() {}

std::string PrinterColor::getType() {
    return "Color printer";
}
