#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <string>
#include <vector>
#include "../Repositories/AdminRepo/AdminRepo.h"
#include "../Domain/Admin/Admin.h"



class AdminController {
public:
    AdminController(AdminRepo& adminRepo);

    void createAdmin(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const Date& birthDateString, double salary, const std::string& remarks, bool isActive, const std::string& password);
    void updateAdmin(const std::string& initials, const std::string& attribute, const std::string& value);
    void deleteAdmin(const std::string& initials);
    void activateAdmin(const std::string& initials);
    void deactivateAdmin(const std::string& initials);
    void resetAdminPassword(const std::string& initials);

    void listAllAdmins() const;
    std::vector<Admin> searchAdminsByName(const std::string& name) const;
    std::vector<Admin> searchAdminsByInitials(const std::string& initials) const;
    std::vector<Admin> searchAdminsByEmail(const std::string& email) const;
    std::vector<Admin> searchAdminsByBirthDate(const std::string& startDate, const std::string& endDate) const;

    void viewAdminSalary(const std::string& initials) const;
    void adjustAdminSalary(const std::string& initials, double newSalary);

private:
    AdminRepo& adminRepo;
    std::string generateRandomPassword() const;
    void sendPasswordResetEmail(Admin& admin, const std::string& newPassword) const;
    static Admin jsonToAdmin(const nlohmann::json& adminJson);
};

#endif // ADMINCONTROLLER_H
