//
// Created by Tudor on 29.05.2024.
//
#include "MitarbeiterController.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

MitarbeiterController::MitarbeiterController(const std::string& filename) : repo(filename) {}

void MitarbeiterController::add_employee(const string& lastName, const string& firstName, const string& email, const string& position, const string& abbreviation, const string& birthDateString, double salary, const string& remarks, bool isAdmin) {
	Mitarbeiter employee(lastName, firstName, email, position, abbreviation, birthDateString, salary, remarks, isAdmin);
	repo.add_employee(employee);
}

void MitarbeiterController::modify_employee(const string& identifier, const string& attribute, const string& value) {
	repo.modify_employee(identifier, attribute, value);
}

void MitarbeiterController::remove_employee(const string& identifier) {
	repo.remove_employee(identifier);
}

void MitarbeiterController::list_all_employees() const {
	const json& employees = repo.get_mitarbeiter_json();
	for (const auto& emp : employees) {
		std::cout << emp.dump(4) << std::endl;
	}
}

bool MitarbeiterController::search_employee(const string& identifier) const {
	return repo.search_employee(identifier);
}

//void MitarbeiterController::assign_admin(const std::string& identifier, bool isAdmin) {
//	try {
//		repo.modify_employee(identifier, "isAdmin", isAdmin ? "true" : "false");
//	} catch (const std::exception& e) {
//		std::cerr << "Error assigning admin rights: " << e.what() << std::endl;
//	}
//}
