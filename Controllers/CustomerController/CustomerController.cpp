#include "CustomerService.h"
#include "CustomerController.h"

void CustomerController::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

void CustomerController::deleteCustomer(long id) {
    // Simplified deletion logic
    customers.erase(std::remove_if(customers.begin(), customers.end(),
                                   [id](const Customer& c) { return c.id == id; }),
                    customers.end());
}

Customer* CustomerController::findCustomerByEmail(const std::string& email) {
    for (auto& customer : customers) {
        if (customer.email == email) {
            return &customer;
        }
    }
    return nullptr;  // Not found
}

void CustomerController::anonymizeCustomer(long id) {
    for (auto& customer : customers) {
        if (customer.id == id) {
            customer.anonymize();
            break;
        }
    }
}
