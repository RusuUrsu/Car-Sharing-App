#pragma once

#include "../OrderController.h"
#include <cassert>

class OrderControllerTests {
public:
    static void runTests();
private:
    static void testCreateOrder();
    static void testModifyOrder();
    static void testRemoveOrder();
    static void testListOrders();
    static void testCalculateTotalSum();
};