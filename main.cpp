#include <iostream>
#include <fstream>
#include <vector>
#include "include/nlohmann/json.hpp"
#include "Repositories/AutoRepo/AutoRepo.h"
#include "Domain/Auto.h"
#include "Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.h"
#include "Controllers/AutoController/AutoController.h"
#include "Domain/Admin/Admin.h"
#include "Repositories/AdminRepo/TestsAdminRepo/TestsAdminRepo.h"
#include "Repositories/AdminRepo/AdminRepo.h"

using namespace std;

int main() {
    // ruleaza testele
    //run_tests_auto_repo();
    // masinile json se afla in "cars.json"
    //AutoRepo cr("cars.json"); // la initializare, se deschide fisierul cars.json in Repo
    //AutoController cc(cr); // AutoController
    run_tests_admin_repo();
    return 0;
}
