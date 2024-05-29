#include "TestsAdminController.h"

void TestsAdminController::testAdminCreation() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990,"January"}, 5000.0, "Remarks", true, "password");
    assert(mockRepo.search_admin("cosmin.pilca@example.com"));
}

void TestsAdminController::testAdminUpdate() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);


    adminController.updateAdmin("CP", "Position", "Supervisor");

}

void TestsAdminController::testAdminDeletion() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.deleteAdmin("CP");
    assert(!mockRepo.search_admin("cosmin.pilca@example.com"));
}

void TestsAdminController::testAdminActivation() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.activateAdmin("CP");
}

void TestsAdminController::testAdminDeactivation() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.deactivateAdmin("CP");
}

void TestsAdminController::testAdminPasswordReset() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.resetAdminPassword("CP");
}

void TestsAdminController::testAdminSalaryView() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.viewAdminSalary("CP");
}

void TestsAdminController::testAdminSalaryAdjustment() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    adminController.adjustAdminSalary("CP", 6000.0);
}

void TestsAdminController::testAdminSearchByName() {
    AdminRepo mockRepo("test_admins.json");
    AdminController adminController(mockRepo);

    std::vector<Admin> result = adminController.searchAdminsByName("Cosmin");
}

void TestsAdminController::runAllTests() {
    testAdminCreation();
    testAdminUpdate();
    testAdminDeletion();
    testAdminActivation();
    testAdminDeactivation();
    testAdminPasswordReset();
    testAdminSalaryView();
    testAdminSalaryAdjustment();
    testAdminSearchByName();
}
