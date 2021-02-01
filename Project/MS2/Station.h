// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 11,2020
//

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"

class Station {
    static unsigned int id_generator;
    unsigned int m_id;
    std::string m_station_name;
    std::string m_description;
    unsigned int m_serialNumber;
    unsigned int m_quantity;
    static size_t m_widthField;
public:
    Station(const std::string&);
    const std::string& getItemName() const;
    unsigned int getNextSerialNumber();
    unsigned int getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};

#endif

