#pragma once

#ifndef JSON_TEST_MITARBEITERREPO_H
#define JSON_TEST_MITARBEITERREPO_H

#endif //JSON_TEST_MITARBEITERREPO_H
#include "nlohmann/json.hpp"
#include "../../Domain/Mitarbeiter.h"

using json = nlohmann::json;

class MitarbeiterRepo {
private:

    json mitarbeiter;        ///< JSON array containing the employee data
    std::string filename;    ///< Filename for storing the employee data
    void read_from_file(const std::string& filename);
    void write_to_file(const std::string& filename);
    bool verify_employee(const Mitarbeiter& employee) const;
    void save();

    ///  Admin functionalities
    void manage_employee(const std::string& adminIdentifier, const std::string& targetIdentifier, const Mitarbeiter& newDetails);
    double view_salary(const std::string& adminIdentifier, const std::string& targetIdentifier) const;
    void adjust_salary(const std::string& adminIdentifier, const std::string& targetIdentifier, double newSalary);
    void create_employee(const Mitarbeiter& employee);
    void update_employee(const std::string& identifier, const Mitarbeiter& newDetails);
    void activate_employee(const std::string& identifier, bool active);
    void delete_employee(const std::string& identifier);
    void assign_admin_rights(const std::string& identifier, bool isAdmin);
    void reset_password(const std::string& identifier, const std::string& newPassword);

public:

    MitarbeiterRepo(const std::string& filename);
    json& get_mitarbeiter_json();
    void add_employee(const Mitarbeiter& employee);
    void remove_employee(const std::string& identifier);
    void modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value);
    bool search_employee(const std::string& identifier) const;

};