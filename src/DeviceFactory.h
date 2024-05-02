//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_DEVICEFACTORY_H
#define PRINTSYSTEM_DEVICEFACTORY_H

#include "Device.h"

class DeviceFactory {
public:
    explicit DeviceFactory(TiXmlElement *device_element);

    Device *getDevice() const;

private:
    Device *device = nullptr;
};


#endif //PRINTSYSTEM_DEVICEFACTORY_H
