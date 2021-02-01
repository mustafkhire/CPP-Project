// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 20,2020
//

#include <algorithm>
#include "CustomerOrder.h"
size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(): m_name(""),m_product("")
{
	m_lstItem = nullptr;
	m_cntItem = 0;
}

CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder()
{
	Utilities m_util;
	size_t next_pos = 0;
	bool evenmore = true;

	m_name = m_util.extractToken(str, next_pos, evenmore);
	m_product = m_util.extractToken(str, next_pos, evenmore);
	m_cntItem = std::count(str.begin(), str.end(), m_util.getDelimiter()) - 1;

	m_lstItem = new Item * [m_cntItem];

	for (auto i = 0u; i < m_cntItem; ++i) {
		m_lstItem[i] = new Item(m_util.extractToken(str, next_pos, evenmore));
	}

	if (m_widthField < m_util.getFieldWidth())
		m_widthField = m_util.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder& copy) 
{
	throw "Exception has been thrown! BEWARE";
}

CustomerOrder::CustomerOrder(CustomerOrder&& copy) noexcept 
{
	m_lstItem = nullptr;
	*this = std::move(copy);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& copy) noexcept 
{
	if (this != &copy)
	{
		if (m_lstItem != nullptr) {
			for (auto i = 0u; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
		}

		m_name = copy.m_name;
		m_product = copy.m_product;

		m_cntItem = copy.m_cntItem;
		m_lstItem = copy.m_lstItem;

		copy.m_cntItem = 0;
		copy.m_lstItem = nullptr;
		copy.m_name = "";
		copy.m_product = "";

	}
	return *this;
}
CustomerOrder::~CustomerOrder() 
{
	for (auto i = 0u; i < m_cntItem; ++i)
		delete m_lstItem[i];
	delete[] m_lstItem;
	m_lstItem = nullptr;
}

bool CustomerOrder::isOrderFilled() const 
{
	for (auto i = 0u; i < m_cntItem; ++i)
		if (!m_lstItem[i]->m_isFilled)
			return false;
	return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const 
{
	bool check = false;
	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) {
			if (m_lstItem[i]->m_isFilled)
				check = true;
		}
	}
	return check;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	bool check = false;
	size_t count = 0;
	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == station.getItemName()) {
			check = true;
			count = i;
		}
	}
	if (check) {
		station.updateQuantity();
		m_lstItem[count]->m_serialNumber = station.getNextSerialNumber();
		m_lstItem[count]->m_isFilled = true;
		os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
		if (station.getQuantity() < 0) { os << "Unable to fill " << m_name << ", " << m_product << "[" << station.getItemName() << "]" << std::endl; }
	}
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << std::endl;
	for (auto i = 0u; i < m_cntItem; ++i)
	{
		os << "[" << std::setw(6) << std::setfill('0') << std::left << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		(m_lstItem[i]->m_isFilled == false) ? os << "MISSING" : os << "FILLED";
		os << std::endl;
	}
}