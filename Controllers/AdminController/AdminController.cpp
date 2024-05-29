#include "AdminController.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>

AdminController::AdminController(AdminRepo& adminRepo) : adminRepo(adminRepo) {}

std::string AdminController::generateRandomPassword() const {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string password;
    for (int i = 0; i < 12; ++i) {
        password += characters[distribution(generator)];
    }
    return password;
}

void AdminController::sendPasswordResetEmail(Admin& admin, const std::string& newPassword) const {
    std::cout << "Sending password reset email to " << admin.getEmail() << ":\n";
    std::cout << "New password: " << newPassword << std::endl;
}

// Admin management functions
void AdminController::createAdmin(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const Date& birthDateString, double salary, const std::string& remarks, bool isActive, const std::string& password) {
    try {
        Admin newAdmin(lastName, firstName, email, position,birthDateString,abbreviation, salary, remarks, password);
        adminRepo.add_admin(newAdmin);
        std::cout << "Admin created successfully!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error creating admin: " << e.what() << std::endl;
    }
}

void AdminController::updateAdmin(const std::string& initials, const std::string& attribute, const std::string& value) {
    try {
        adminRepo.modify_admin(initials, attribute, value);
        std::cout << "Admin updated successfully!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error updating admin: " << e.what() << std::endl;
    }
}

void AdminController::deleteAdmin(const std::string& initials) {
    try {
        adminRepo.remove_admin(initials);
        std::cout << "Admin deleted successfully!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error deleting admin: " << e.what() << std::endl;
    }
}

void AdminController::activateAdmin(const std::string& initials) {
    updateAdmin(initials, "Is Active", "true");
}

void AdminController::deactivateAdmin(const std::string& initials) {
    updateAdmin(initials, "Is Active", "false");
}

void AdminController::resetAdminPassword(const std::string& initials) {
    try {
        json admins = adminRepo.get_admin_json();
        auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
            return adm["Initials"] == initials;
        });

        if (it != admins.end()) {
            Admin admin = jsonToAdmin(*it);
            std::string newPassword = generateRandomPassword();
            admin.setPassword(newPassword);
            (*it)["Password"] = newPassword;
            adminRepo.save();
            sendPasswordResetEmail(admin, newPassword);
            std::cout << "Password reset successfully and emailed!" << std::endl;
        } else {
            throw std::runtime_error("Admin not found");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error resetting password: " << e.what() << std::endl;
    }
}


void AdminController::listAllAdmins() const {
    json admins = adminRepo.get_admin_json();
    if (admins.empty()) {
        std::cout << "Nu există angajați în baza de date." << std::endl;
        return;
    }

    for (const auto& adminJson : admins) {
        Admin admin = jsonToAdmin(adminJson);
        std::cout << admin.getEmail() << std::endl;
    }
}

std::vector<Admin> AdminController::searchAdminsByName(const std::string& name) const {
    std::vector<Admin> admins;
    for (const auto& adminJson : adminRepo.get_admin_json()) {
        Admin admin = jsonToAdmin(adminJson);
        if (admin.getLastName() == name || admin.getFirstName() == name) {
            admins.push_back(admin);
        }
    }
    return admins;
}


void AdminController::viewAdminSalary(const std::string& initials) const {
    try {
        json admins = adminRepo.get_admin_json();
        auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
            return adm["Initials"] == initials;
        });

        if (it != admins.end()) {
            Admin admin = jsonToAdmin(*it);
            std::cout << "Salariul adminului este: " << std::fixed << std::setprecision(2) << admin.getSalary() << " EUR" << std::endl;
        } else {
            throw std::runtime_error("Admin not found");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error viewing salary: " << e.what() << std::endl;
    }
}

void AdminController::adjustAdminSalary(const std::string& initials, double newSalary) {
    try {
        if (newSalary < 100) {
            throw std::runtime_error("Salariul trebuie să fie de cel puțin 100 EUR.");
        }
        adminRepo.modify_admin(initials, "Salary", std::to_string(newSalary));
        std::cout << "Salariul adminului a fost actualizat cu succes!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Eroare la actualizarea salariului: " << e.what() << std::endl;
    }
}


Admin AdminController::jsonToAdmin(const nlohmann::json& adminJson) {
    if (!adminJson.contains("Last Name") || !adminJson.contains("First Name")
        || !adminJson.contains("Email") || !adminJson.contains("Position")
        || !adminJson.contains("Birthday") || !adminJson.contains("Initials")
        || !adminJson.contains("Salary") || !adminJson.contains("Password")) {
        throw std::runtime_error("Incomplete Admin data in JSON");
    }

    std::string lastName = adminJson["Last Name"];
    std::string firstName = adminJson["First Name"];
    std::string email = adminJson["Email"];
    std::string position = adminJson["Position"];
    std::string abbreviation = adminJson["Initials"];

    Date birthDateString = {adminJson["Birthday"]["day"], adminJson["Birthday"]["year"], adminJson["Birthday"]["month"]};

    if (!adminJson["Salary"].is_number()) {
        throw std::runtime_error("Invalid salary in JSON");
    }
    double salary = adminJson["Salary"];
    std::string remarks = adminJson.value("Remarks", "");
    std::string password = adminJson["Password"];

    return Admin(lastName, firstName, email, position, birthDateString, abbreviation,
                 salary, remarks, password);
}