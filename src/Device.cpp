//
// Created by student on 29/02/24.
//

#include "Device.h"

Device::Device(const std::string &name, int emission, int speed) : name(name), emission(emission), speed(speed) {}

Device::Device(TiXmlElement device_node) {

}
