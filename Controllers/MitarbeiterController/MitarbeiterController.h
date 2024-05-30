//
// Created by Tudor on 29.05.2024.
//
#ifndef JSON_TEST_MITARBEITERCONTROLLER_H
#define JSON_TEST_MITARBEITERCONTROLLER_H
#include <vector>
#include <string>
#include "../Domain/Mitarbeiter.h"
#include "../Repositories/MitarbeiterRepo/MitarbeiterRepo.h"

class MitarbeiterController {
public:
	explicit MitarbeiterController(const std::string& filename);

	void add_employee(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin);
	void modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value);
	void remove_employee(const std::string& identifier);
	bool search_employee(const std::string& identifier) const;
	void list_all_employees() const;
	void reset_password(const std::string& identifier);
	//void assign_admin(const std::string& identifier, bool isAdmin);

private:
	MitarbeiterRepo repo;
};

#endif //JSON_TEST_MITARBEITERCONTROLLER_H


//#ifndef JSON_TEST_MITARBEITERCONTROLLER_H
//#define JSON_TEST_MITARBEITERCONTROLLER_H
//#include <vector>
//#include <string>
//#include "../Domain/Mitarbeiter.h"
//#include "../Repositories/MitarbeiterRepo/MitarbeiterRepo.h"
//
//class MitarbeiterController {
//private:
//	MitarbeiterRepo &repo;
//
//public:
//	MitarbeiterController(MitarbeiterRepo &repo);
//
//	void createEmployee(const std::string &lastName, const std::string &firstName, const std::string &email,
//	                    const std::string &position,
//	                    const std::string &abbreviation, const std::string &birthDate, double salary,
//	                    const std::string &remarks,
//	                    bool isAdmin);
//
//	void modifyEmployee(const std::string &identifier, const std::string &attribute, const std::string &value);
//
//	void activateEmployee(const std::string &identifier);
//
//	void deactivateEmployee(const std::string &identifier);
//
//	void deleteEmployee(const std::string &identifier);
//
//	void assignAdminRights(const std::string &identifier);
//
//	void removeAdminRights(const std::string &identifier);
//
//	void resetEmployeePassword(const std::string &identifier, const std::string &newPassword);
//
//	std::vector<Mitarbeiter> listAllEmployees() const;
//
//	Mitarbeiter searchEmployeeByAbbreviation(const std::string &abbreviation) const;
//
//	Mitarbeiter searchEmployeeByEmail(const std::string &email) const;
//
//	std::vector<Mitarbeiter> searchEmployeeByName(const std::string &lastName, const std::string &firstName) const;
//
//	std::vector<Mitarbeiter> searchEmployeeByBirthDate(const std::string &startDate, const std::string &endDate) const;
//
//	void changeOwnPassword(const std::string &identifier, const std::string &newPassword);
//
//	void changeOwnRemarks(const std::string &identifier, const std::string &remarks);
//
//	void validateAdminAccess(const std::string &identifier) const;
//
//	Mitarbeiter jsonToMitarbeiter(const json &mitarbeiterJson) const;
//};
//
//#endif //JSON_TEST_MITARBEITERCONTROLLER_H