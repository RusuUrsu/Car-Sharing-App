#ifndef TESTS_ADMIN_CONTROLLER_H
#define TESTS_ADMIN_CONTROLLER_H

#include "../Controllers/AdminController/AdminController.h"
#include "../Repositories/AdminRepo/AdminRepo.h"
#include <cassert>

class TestsAdminController {
public:
    static void testAdminCreation();
    static void testAdminUpdate();
    static void testAdminDeletion();
    static void testAdminActivation();
    static void testAdminDeactivation();
    static void testAdminPasswordReset();
    static void testAdminSalaryView();
    static void testAdminSalaryAdjustment();
    static void testAdminSearchByName();
    static void runAllTests();
};

#endif // TESTS_ADMIN_CONTROLLER_H
