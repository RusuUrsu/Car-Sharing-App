#include "MitarbeiterRepo.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <typeinfo>


MitarbeiterRepo::MitarbeiterRepo(const std::string& filename) {
    this->filename = filename;
    this->read_from_file(this->filename);
}

void MitarbeiterRepo::write_to_file(const string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << this->mitarbeiter.dump(4); // Pretty print with an indent of 4 spaces
        file.close();
        return;
    }
    throw runtime_error("Unable to open file: " + filename);

}


void MitarbeiterRepo::read_from_file(const string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    json j;
    file >> j; // se citeste tot array-ul din fisier

    if (j.is_array())
        for (const auto& carJson : j)
            this->mitarbeiter.push_back(carJson); // fiecare obiect json din array este
    file.close();                              // introdus in array
}


///

bool MitarbeiterRepo::verify_employee(const Mitarbeiter &employee) const {
    for (const auto& emp : mitarbeiter) {
        if (emp["email"] == employee.getEmail()) {
            return false;
        }
    }
    return true;
}

void MitarbeiterRepo::save() {
    write_to_file(filename);

}

json& MitarbeiterRepo::get_mitarbeiter_json() {
    return mitarbeiter;
}

void MitarbeiterRepo::remove_employee(const std::string& identifier) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        if ((*it)["isActive"]) {
            throw std::runtime_error("Cannot remove an active employee.");
        }
        mitarbeiter.erase(it);
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}


void MitarbeiterRepo::add_employee(const Mitarbeiter& employee) {
    this->verify_employee(employee);
    json j;
    j["lastName"] = employee.getLastName();
    j["firstName"] = employee.getFirstName();
    j["email"] = employee.getEmail();
    j["position"] = employee.getPosition();
    j["abbreviation"] = employee.getAbbreviation();
    j["remarks"] = employee.getRemarks();
    j["birthDate"] = employee.getBirthDate();
    j["salary"] = employee.getSalary();
    j["isActive"] = employee.getIsActive();
    j["isAdmin"] = employee.getIsAdmin();
    this->mitarbeiter.push_back(j);
    this->write_to_file(this->filename);
}

void MitarbeiterRepo::modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        if (attribute == "lastName") {
            (*it)["lastName"] = value;
        } else if (attribute == "firstName") {
            (*it)["firstName"] = value;
        } else if (attribute == "email") {
            Mitarbeiter::validateEmail(value);
            (*it)["email"] = value;
        } else if (attribute == "position") {
            (*it)["position"] = value;
        } else if (attribute == "abbreviation") {
            (*it)["abbreviation"] = value;
        } else if (attribute == "remarks") {
            (*it)["remarks"] = value;
        } else if (attribute == "birthDate") {
            (*it)["birthDate"] = value; // This should be converted to the correct format
        } else if (attribute == "salary") {
            double salary = std::stod(value);
            Mitarbeiter::validateSalary(salary);
            (*it)["salary"] = salary;
        } else if (attribute == "isActive") {
            (*it)["isActive"] = (value == "true");
        } else if (attribute == "isAdmin") {
            (*it)["isAdmin"] = (value == "true");
        } else {
            throw std::runtime_error("Invalid attribute.");
        }
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}

bool MitarbeiterRepo::search_employee(const std::string& identifier) const {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });
    return it != mitarbeiter.end();
}

void MitarbeiterRepo::manage_employee(const std::string& adminIdentifier, const std::string& targetIdentifier, const Mitarbeiter& newDetails) {
    // Găsește angajatul admin
    auto adminIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == adminIdentifier;
    });

    // Verifică dacă angajatul este admin
    if (adminIt == mitarbeiter.end() || !(*adminIt)["isAdmin"]) {
        throw std::runtime_error("Unauthorized: Only admins can manage employees.");
    }

    // Găsește angajatul țintă
    auto targetIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == targetIdentifier;
    });

    // Dacă angajatul țintă există, actualizează detaliile
    if (targetIt != mitarbeiter.end()) {
        (*targetIt)["lastName"] = newDetails.getLastName();
        (*targetIt)["firstName"] = newDetails.getFirstName();
        (*targetIt)["email"] = newDetails.getEmail();
        (*targetIt)["position"] = newDetails.getPosition();
        (*targetIt)["abbreviation"] = newDetails.getAbbreviation();
        (*targetIt)["remarks"] = newDetails.getRemarks();

        // Convertire și actualizare birthDate la format string
        std::tm birthDate = newDetails.getBirthDate();
        std::ostringstream oss;
        oss << std::put_time(&birthDate, "%d.%m.%Y");
        (*targetIt)["birthDate"] = oss.str();

        (*targetIt)["salary"] = newDetails.getSalary();
        (*targetIt)["isActive"] = newDetails.getIsActive();
        (*targetIt)["isAdmin"] = newDetails.getIsAdmin();

        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
double MitarbeiterRepo::view_salary(const std::string& adminIdentifier, const std::string& targetIdentifier) const {
    // Găsește angajatul admin
    auto adminIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == adminIdentifier;
    });

    // Verifică dacă angajatul este admin
    if (adminIt == mitarbeiter.end() || !(*adminIt)["isAdmin"]) {
        throw std::runtime_error("Unauthorized: Only admins can view salaries.");
    }

    // Găsește angajatul țintă
    auto targetIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == targetIdentifier;
    });

    // Dacă angajatul țintă există, returnează salariul
    if (targetIt != mitarbeiter.end()) {
        return (*targetIt)["salary"];
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
void MitarbeiterRepo::adjust_salary(const std::string& adminIdentifier, const std::string& targetIdentifier, double newSalary) {
    // Găsește angajatul admin
    auto adminIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == adminIdentifier;
    });

    // Verifică dacă angajatul este admin
    if (adminIt == mitarbeiter.end() || !(*adminIt)["isAdmin"]) {
        throw std::runtime_error("Unauthorized: Only admins can adjust salaries.");
    }

    // Găsește angajatul țintă
    auto targetIt = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == targetIdentifier;
    });

    // Dacă angajatul țintă există, ajustează salariul
    if (targetIt != mitarbeiter.end()) {
        Mitarbeiter::validateSalary(newSalary); // Validează noul salariu
        (*targetIt)["salary"] = newSalary;
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
///function to create a new employee
void MitarbeiterRepo::create_employee(const Mitarbeiter& employee) {
    add_employee(employee);
}
//function to update an existent employee
void MitarbeiterRepo::update_employee(const std::string& identifier, const Mitarbeiter& newDetails) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        (*it)["lastName"] = newDetails.getLastName();
        (*it)["firstName"] = newDetails.getFirstName();
        (*it)["email"] = newDetails.getEmail();
        (*it)["position"] = newDetails.getPosition();
        (*it)["abbreviation"] = newDetails.getAbbreviation();
        (*it)["remarks"] = newDetails.getRemarks();

        std::tm birthDate = newDetails.getBirthDate();
        std::ostringstream oss;
        oss << std::put_time(&birthDate, "%d.%m.%Y");
        (*it)["birthDate"] = oss.str();

        (*it)["salary"] = newDetails.getSalary();
        (*it)["isActive"] = newDetails.getIsActive();
        (*it)["isAdmin"] = newDetails.getIsAdmin();

        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
///function to activate an employee
void MitarbeiterRepo::activate_employee(const std::string& identifier, bool active) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        (*it)["isActive"] = active;
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
///function to delete an employee
void MitarbeiterRepo::delete_employee(const std::string& identifier) {
    remove_employee(identifier);
}

void MitarbeiterRepo::assign_admin_rights(const std::string& identifier, bool isAdmin) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        (*it)["isAdmin"] = isAdmin;
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}

void MitarbeiterRepo::reset_password(const std::string& identifier, const std::string& newPassword) {
    // Aceasta este o implementare simplă. În practică, parolele ar trebui să fie hash-uite și gestionate corespunzător.
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        (*it)["password"] = newPassword; // Asumând că structura JSON conține un câmp pentru parola.
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}