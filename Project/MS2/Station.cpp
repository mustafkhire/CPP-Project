// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 11,2020
//

#include "Station.h"

using namespace std;

size_t Station::m_widthField = 0;
unsigned int Station::id_generator = 0;

Station::Station(const std::string& str) {
    Utilities m_util;

    size_t next_pos = 0;
    bool evenmore = true;

    m_id = ++id_generator;
    m_station_name = m_util.extractToken(str, next_pos, evenmore);
    m_serialNumber = std::stoul(m_util.extractToken(str, next_pos, evenmore));
    m_quantity = std::stoi(m_util.extractToken(str, next_pos, evenmore));

    if (m_widthField < m_util.getFieldWidth()) 
        m_widthField = m_util.getFieldWidth();

    m_description = m_util.extractToken(str, next_pos, evenmore);

    if (m_widthField > m_util.getFieldWidth())
        m_widthField = m_util.getFieldWidth();

}
const std::string& Station::getItemName() const {
    return m_station_name;
}
unsigned int Station::getNextSerialNumber(){
    return m_serialNumber++;
}
unsigned int Station::getQuantity() const {
    return m_quantity;
}
void Station::updateQuantity() {
    if (m_quantity >= 0)
        m_quantity--;
}
void Station::display(std::ostream& os, bool full) const {

    if (!full)
    {
         os << "[" << std::setw(3) << std::setfill('0') << std::right << m_id << "]" << std::setfill(' ')
            << " Item: " << std::setw(m_widthField) << std::left << m_station_name
            << " [" << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << "]" << std::setfill(' ') << std::endl;
    }
    else
    {
         os << "[" << std::setw(3) << std::setfill('0') << std::right << m_id << "]" << std::setfill(' ')
            <<" Item: " << std::setw(m_widthField) << std::left << m_station_name
            << " [" << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << "]" << std::setfill(' ')
            << " Quantity: " << std::setw(m_widthField) << std::left << m_quantity
            << " Description: " << m_description << std::endl;
    }

}
