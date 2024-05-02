//
// Created by student on 2/05/24.
//

#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "DeviceFactory.h"

#include "PrinterBlackWhite.h"
#include "PrinterColor.h"
#include "Scanner.h"

DeviceFactory::DeviceFactory(TiXmlElement *device_node) {
    std::string name;
    std::string emission;
    std::string speed;
    std::string type;
    std::string cost;

    for (TiXmlNode *node = device_node->FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->FirstChild() == nullptr) {
            continue;
        }
        if (std::string(node->Value()) == "name") {
            name = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "emission") {
            emission = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "speed") {
            speed = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "type") {
            type = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "cost") {
            cost = node->FirstChild()->Value();
        } else {
            EXPECT(false, "Unknown attribute for Device: '" + std::string(node->Value()) + "'");
        }
    }

    EXPECT(!name.empty(), "No name is provided");
    EXPECT(!emission.empty(), "No emission is provided");
    EXPECT(is_number(emission), "Emission should be an integer number");
    EXPECT(!speed.empty(), "No speed is provided");
    EXPECT(is_number(speed), "Speed should be an integer number");
    EXPECT(!type.empty(), "No type is provided");
    EXPECT(isValidDeviceType(type), "Type should be a valid device type");
    EXPECT(!cost.empty(), "No cost is provided");
    EXPECT(is_number(cost), "Cost should be an integer number");

    if (type == "bw") {
        device = new PrinterBlackWhite(
                        name, std::stoi(emission), std::stoi(speed), std::stoi(cost));
    } else if (type == "color") {
        device = new PrinterColor(
                        name, std::stoi(emission), std::stoi(speed), std::stoi(cost));
    } else if (type == "scan") {
        device = new Scanner(
                        name, std::stoi(emission), std::stoi(speed), std::stoi(cost));
    }
}

Device *DeviceFactory::getDevice() const {
    return device;
}
