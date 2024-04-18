//
// Created by Abuha on 18-4-2024.
//

#include "SystemTracker.h"

SystemTracker::SystemTracker(){
    init_ = this;
    CO2_emission = 0;
    total_pages = 0;
}

int SystemTracker::getCo2Emission() const {
    return CO2_emission;
}

void SystemTracker::addCo2Emission(int co2) {
    REQUIRE(co2 >= 0, "CO2 emission cannot be negative");
    CO2_emission += co2;
}

int SystemTracker::getTotalPages() const {
    return total_pages;
}

void SystemTracker::addPages(int pages) {
    REQUIRE(pages >= 0, "Total pages cannot be negative");
    total_pages += pages;
}

double SystemTracker::getAverageCO2Emission() const {
    REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
    REQUIRE(total_pages > 0, "No pages have been printed yet, no average CO2 emission can be calculated");
    return float(CO2_emission) / float(total_pages);
}



