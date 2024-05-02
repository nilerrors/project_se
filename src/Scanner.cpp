//
// Created by student on 2/05/24.
//

#include "Scanner.h"

Scanner::Scanner(TiXmlElement *scanner_element) : Device(scanner_element) {}

Scanner::Scanner(const std::string &name, int emission, int speed, int cost) : Device(name, emission, speed, cost) {}

Scanner::~Scanner() {}

std::string Scanner::getType() {
    return "Scanner";
}
