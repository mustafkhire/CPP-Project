// Name: Mustaf Khire
// Seneca Student ID: 143040186
// Seneca email: mkhire@myseneca.ca
// Date of completion: Nov 26,2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include "LineManager.h"

using namespace std;

LineManager::LineManager(const std::string& str, std::vector<Workstation*>& workstation, std::vector<CustomerOrder>& order) 
{
	ToBeFilled.resize(order.size());
	AssemblyLine.resize(workstation.size());
	std::move(order.begin(), order.end(), ToBeFilled.begin());
	std::copy(workstation.begin(), workstation.end(), AssemblyLine.begin());
	m_cntCustomerOrder = order.size();

	ifstream file(str);
	if (!file) {
		cerr << "Unable to open file, Try again!";
	}

	while (!file.eof())
	{
		string line;
		getline(file, line);

		Utilities m_util;
		size_t next_pos = 0;
		bool evenmore = true;

		string token1 = m_util.extractToken(line, next_pos, evenmore);
		string token2 = m_util.extractToken(line, next_pos, evenmore);

		for (auto i = 0u; i < AssemblyLine.size(); i++) {

			if (AssemblyLine[i]->getItemName() == token1) {

				for (auto j = 0u; j < AssemblyLine.size(); j++) {

					if (AssemblyLine[j]->getItemName() == token2) {

						AssemblyLine[i]->setNextStation(*AssemblyLine[j]);

					}

				}

			}
		}
	}
}

bool LineManager::run(std::ostream& os)
{
	static unsigned int count = 0;
	os << "Line Manager Iteration: " << ++count << endl;
	
	bool test = true;
	//CustomerOrder holdOrder;

	if (!ToBeFilled.empty()) {
		auto fStation = 0;
		for (auto i = 0u; i < AssemblyLine.size(); i++)
		{
			fStation = i;
			for (auto j = 0u; j < AssemblyLine.size(); j++)
			{
				if (AssemblyLine[j]->getNextStation() != nullptr && AssemblyLine[i]->getItemName().compare(AssemblyLine[j]->getNextStation()->getItemName()) == 0)
				{
					fStation = -1;
				}
			}
			if (fStation != -1) {
				break;
			}
				
		}

		*AssemblyLine[fStation] += (std::move(ToBeFilled.front()));
		ToBeFilled.pop_front();
	}
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}
	
	for (auto i = 0u; i < AssemblyLine.size(); i++) {

			
		if (AssemblyLine[i]->getNextStation() == nullptr)
		{
			CustomerOrder holdOrder;
			if (AssemblyLine[i]->getIfCompleted(holdOrder))
			{
				Completed.push_back(std::move(holdOrder));
			}

		}
		else
		{
			AssemblyLine[i]->moveOrder();
		}
	}
	auto cnt = m_cntCustomerOrder;
	if (Completed.size() == cnt)
		test = true;
	else
		test = false;
	
	return test;
}

void LineManager::displayCompletedOrders(std::ostream& os) const
{
	for (auto i = 0u; i < Completed.size(); i++)
		Completed[i].display(os);
}

void LineManager::displayStations() const
{
	for (auto i = 0u; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->display(cout);
}

void LineManager::displayStationsSorted() const
{
	
	//std::vector<Workstation*> temp(AssemblyLine.size());
	//std::copy(AssemblyLine.begin(), AssemblyLine.end(), temp.begin());
	auto fStation = 0;
	for (size_t i = 0; i < AssemblyLine.size(); i++)
	{
		fStation = i;
		for (size_t k = 0; k < AssemblyLine.size(); k++)
		{
			if (AssemblyLine[k]->getNextStation() != nullptr && AssemblyLine[i]->getItemName().compare(AssemblyLine[k]->getNextStation()->getItemName()) == 0)
			{
				fStation = -1;
			}
		}
		if (fStation != -1)
		{
			break;
		}
	}
	const Workstation* first = AssemblyLine[fStation];
	while (first != nullptr)
	{
		first->display(std::cout);
		first = first->getNextStation();
	}

}