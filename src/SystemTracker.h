//
// Created by Abuha on 18-4-2024.
//

#ifndef PRINTSYSTEM_SYSTEMTRACKER_H
#define PRINTSYSTEM_SYSTEMTRACKER_H

#include "lib/DesignByContract.h"

class SystemTracker {
public:
    /**
     * \brief Constructor of SystemTracker
     */
    SystemTracker();

    /**
     * \brief calculates the average CO2 emission
     * @return

     * @require
           - REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
           - REQUIRE(total_pages > 0, "No pages have been printed yet, no average CO2 emission can be calculated");
     */
    double getAverageCO2Emission() const;

    /**
     * \brief gets the CO2 emission
     * @return

     * @require
           - REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
     */
    int getCo2Emission() const;

    /**
     * \brief adds the CO2 emission
     * @param co2

     * @require
           - REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
           - REQUIRE(co2 >= 0, "CO2 emission cannot be negative");
     */
    void addCo2Emission(int co2);

    /**
     * \brief gets the total pages
     * @return

     * @require
           - REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
           - REQUIRE(co2 >= 0, "CO2 emission cannot be negative");
     */
    int getTotalPages() const;

    /**
     * \brief adds the total pages
     * @param pages

     * @require
           - REQUIRE(properlyInitialized(), "SystemTracker object was not properly initialized");
           - REQUIRE(pages >= 0, "Total pages cannot be negative");

     */
    void addPages(int pages);

    bool properlyInitialized() const { return init_ == this; }

private:
    SystemTracker* init_;
    int CO2_emission;
    int total_pages;
};


#endif //PRINTSYSTEM_SYSTEMTRACKER_H
