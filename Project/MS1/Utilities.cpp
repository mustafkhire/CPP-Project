// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 11,2020
//

#include "Utilities.h"

using namespace std;

char Utilities::m_delimiter = '\0';

Utilities::Utilities() {
    m_widthField = 1;
}

void Utilities::setFieldWidth(size_t newWidth) {
    this->m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const {
    return this->m_widthField;
}

void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
}
char Utilities::getDelimiter()  {
    return m_delimiter;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    size_t dempos;
    dempos = str.find(m_delimiter, next_pos + 1);
    size_t length;
    length = (dempos - next_pos);
    string grabtoken;
    grabtoken = str.substr(next_pos, length);
    next_pos = dempos + 1;

    if (m_widthField < grabtoken.length()) {
        m_widthField = grabtoken.length();
    }

    if (grabtoken == "") {
        more = false;
        string str = "No token between delimeters!";
        throw str;
    }
    else {
        more = true;
        return grabtoken;
    }

}