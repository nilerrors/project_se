//
// Created by Abuha on 18-4-2024.
//

#ifndef PRINTSYSTEM_SYSTEMTRACKER_H
#define PRINTSYSTEM_SYSTEMTRACKER_H
#include "lib/DesignByContract.h"

class SystemTracker {
public:
    SystemTracker();

    double getAverageCO2Emission() const;

    int getCo2Emission() const;

    void addCo2Emission(int co2);

    int getTotalPages() const;

    void addPages(int pages);

private:
    bool properlyInitialized() const { return init_ == this; }
    SystemTracker* init_;
    int CO2_emission;
    int total_pages;


};


#endif //PRINTSYSTEM_SYSTEMTRACKER_H
