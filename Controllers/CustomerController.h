//
// Created by Home on 5/29/2024.
//

#ifndef JSON_TEST_CUSTOMERCONTROLLER_H
#define JSON_TEST_CUSTOMERCONTROLLER_H

#include <vector>
#include "Customer.h"
#include "../Domain/Customer.h"

class CustomerController {
public:
    std::vector<Customer> customers;

    void addCustomer(const Customer& customer);
    void deleteCustomer(long id);
    Customer* findCustomerByEmail(const std::string& email);
    void anonymizeCustomer(long id);
};

#endif //JSON_TEST_CUSTOMERCONTROLLER_H
