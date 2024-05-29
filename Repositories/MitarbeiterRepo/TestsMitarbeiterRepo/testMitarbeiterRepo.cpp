#include <cassert>
#include "../MitarbeiterRepo.h"
#include "../../../Domain/Mitarbeiter.h"
//#include "../../../include/nlohmann/json.hpp"
#include <string>

void test_add_employee() {
    MitarbeiterRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Mitarbeiter employee("Mustermann", "Max", "max.mustermann@test.de", "Verkäufer", "03.07.1990", "MM", 2100,"bla","yes");
    Mitarbeiter employee1("Herz", "Kathrin", "herz.kathrin@test.de", "Verkäufer", "01.05.2004", "HK",3800,"da","nein");
    Mitarbeiter employee3("Korn", "Max", "max.korn@test.de", "Verkäufer", "22.02.2000", "KM", 2000, "blabla","yes");

    repo.add_employee(employee);
    repo.add_employee(employee);
    repo.add_employee(employee1);

    assert(repo.search_employee("Mustermann"));
    assert(repo.search_employee("Kathrin"));
    assert(repo.search_employee("Korn"));


    repo.remove_employee("Mustermann");
    repo.remove_employee("Kathrin");
    repo.remove_employee("Korn");
    assert(!repo.search_employee("Mustermann"));
    assert(!repo.search_employee("Kathrin"));
    assert(!repo.search_employee("Korn"));
}
void test_remove_employee() {
    MitarbeiterRepo repo("MitarbeiterRepo/TestsMitarbeiterRepo/tests.json");
    Mitarbeiter employee("Mustermann", "Max", "max.mustermann@test.de", "Verkäufer", "03.07.1990", "MM", 2100,"bla","yes");
    repo.add_employee(employee);

    repo.remove_employee("Mustermann");
    assert(!repo.search_employee("Mustermann"));

    try {
        repo.remove_employee("Tanzer");
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "employee with job tanzer does not exist");
    }

    Mitarbeiter employee1("Herz", "Kathrin", "herz.kathrin@test.de", "Verkäufer", "01.05.2004", "HK",3800,"da","nein");
    Mitarbeiter employee3("Korn", "Max", "max.korn@test.de", "Verkäufer", "22.02.2000", "KM", 2000, "blabla","yes");
    repo.add_employee(employee1);
    repo.add_employee(employee3);

    repo.remove_employee("Herz");
    assert(!repo.search_employee("Herz"));

    try {
        repo.remove_employee("Ale");
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Employee with firstname Ale does not exist.");
    }

    repo.remove_employee("Korn");
    assert(!repo.search_employee("Korn"));
}
