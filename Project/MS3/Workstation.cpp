// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 26,2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

Workstation::Workstation(const std::string& str) : Station(str)
{
	m_pNextStation = nullptr;
}
void Workstation::runProcess(std::ostream& os)
{
	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
	}
}

bool Workstation::moveOrder()
{
	bool check = false;

	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(Station::getItemName()) == true) {
			
				*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				check = true;
			
		}
	}
	return check;
}
void Workstation::setNextStation(Station& station)
{
	if (this != &station) {
		m_pNextStation = (Workstation*)(&station);
	}
}

const Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order)
{
	bool check = false;

	if (!m_orders.empty() && m_orders.front().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();
		check = true;
	}
	return check;
}

void Workstation::display(std::ostream& os)const
{
	if (m_pNextStation == nullptr) {
		os << Station::getItemName() << " --> " << "END OF LINE" << std::endl;
	}
	else {
		os << Station::getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
	}
}

Workstation& Workstation::operator+=(CustomerOrder&& order)
{
	m_orders.push_back(std::move(order));
	return *this;
}