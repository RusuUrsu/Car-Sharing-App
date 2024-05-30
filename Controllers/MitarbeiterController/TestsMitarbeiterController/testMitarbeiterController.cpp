//
// Created by Tudor on 29.05.2024.
//
#include "testMitarbeiterController.h"
#include <cassert>
#include "../MitarbeiterController.h"
#include "../../../Domain/Mitarbeiter.h"
#include "../../../include/nlohmann/json.hpp"
#include <string>
#include <iostream>
using namespace std;

void test_add_employeee() {
	MitarbeiterController controller("controller.json");
	controller.add_employee("Doe", "John", "john.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", false);
	assert(controller.search_employee("JD"));
}

void test_modify_employeee() {
	MitarbeiterController controller("controller.json");
	controller.modify_employee("JD", "lastName", "Smith");
	assert(controller.search_employee("JD"));
}

void test_remove_employeee() {
	MitarbeiterController controller("controller.json");
	controller.remove_employee("JD");
	assert(!controller.search_employee("JD"));
}

void test_list_all_employeees() {
	MitarbeiterController controller("controller.json");
	controller.list_all_employees();
}


void run_tests_mitarbeiter_controller() {
	test_add_employeee();
	test_modify_employeee();
	test_remove_employeee();
	test_list_all_employeees();
	cout << "All MitarbeiterController tests finished successfully." << endl;
}

