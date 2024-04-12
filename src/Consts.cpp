//
// Created by nilerrors on 4/12/24.
//

#include "Consts.h"

PrintingType StringToPrintingType(const std::string &typstr)
{
    if(typstr == "bw") {
        return PrintingType::bw;
    }
    else if(typstr == "scan"){
        return PrintingType::scan;
    }
    else {
        return PrintingType::color;
    }
}

std::string PrintingTypeToDeviceString(PrintingType type)
{
    switch (type) {
        case PrintingType::bw:
            return "Black-and-white printer";
        case PrintingType::color:
            return "Color printer";
        case PrintingType::scan:
            return "Scanner";
    }
    return "unknown";
}

std::string PrintingTypeToJobString(PrintingType type)
{
    switch (type) {
        case PrintingType::bw:
            return "black-and-white job";
        case PrintingType::color:
            return "color-printing job";
        case PrintingType::scan:
            return "scanning job";
    }
    return "unknown";
}
