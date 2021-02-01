// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 11,2020
//
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>

class Utilities {
    size_t m_widthField;
    static char m_delimiter;
public:
    Utilities();
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    static void setDelimiter(char newDelimiter);
    static char getDelimiter();
};

#endif
