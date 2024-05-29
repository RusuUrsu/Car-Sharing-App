#include "Customer.h"

Customer::Customer(long id, std::string lastName, std::string firstName, std::string email,
                   std::string mobile, std::string address, std::string remarks, bool gdprDeleted)
        : id(id), lastName(lastName), firstName(firstName), email(email),
          mobile(mobile), address(address), remarks(remarks), gdprDeleted(gdprDeleted) {}

void Customer::anonymize() {
    lastName = "Kunde-" + std::to_string(id);
    firstName = "Unbekannt";
    email = "";
    mobile = "";
    address = "";
    remarks = "";
    gdprDeleted = true;
}
