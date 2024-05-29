//
// Created by Cosmin Pilca on 29.05.2024.
//

#ifndef JSON_TEST_ADMINCONTROLLER_H
#define JSON_TEST_ADMINCONTROLLER_H
#include <string>

using namespace std;

class AdminController {
public:
    void authentificateAdmin(string email, string password);
    void createMitarbeiter(MitarbeiterData data);
    void updateMitarbeiter(int MitarbeiterID, MitarbeiterData data);
    void deleteMitarbeiter(int MitarbeiterID);

};


#endif //JSON_TEST_ADMINCONTROLLER_H
