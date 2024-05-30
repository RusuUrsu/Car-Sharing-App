//
// Created by Kathrin Bercea Engels on 29.05.2024.
//

#ifndef JSON_TEST_ORDERUI_H
#define JSON_TEST_ORDERUI_H

#include <iostream>

class OrderUI {
private:
    OrderUI& orderUI;
    //void validateOrder;

public:
    void displayMenu();
    void handleUserInput(int userType);
    void createOrder();
    void modifyOrder(int userType);
    void removeOrder();
    void listOrders();
    void searchOrder();
    void calculateTotalSum();
    int removeOrder();
};

#endif //JSON_TEST_ORDERUI_H
