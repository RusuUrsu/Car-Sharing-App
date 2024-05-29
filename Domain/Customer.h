//
// Created by Home on 5/29/2024.
//

#ifndef JSON_TEST_CUSTOMER_H
#define JSON_TEST_CUSTOMER_H

#include <string>

class Customer {
public:
    long id;
    std::string lastName;
    std::string firstName;
    std::string email;
    std::string mobile;
    std::string address;
    std::string remarks;
    bool gdprDeleted;

    Customer(long id, std::string lastName, std::string firstName, std::string email,
             std::string mobile, std::string address, std::string remarks, bool gdprDeleted);
    void anonymize();
};


#endif //JSON_TEST_CUSTOMER_H
