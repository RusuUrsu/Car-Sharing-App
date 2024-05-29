#include "testOrderController.h"

void OrderControllerTests::runTests() {
    testCreateOrder();
    testModifyOrder();
    testRemoveOrder();
    testListOrders();
    testCalculateTotalSum();
}

void OrderControllerTests::testCreateOrder() {
    OrderController controller("test_orders.json");

    try {
        // Try to create an order with invalid user type
        controller.createOrder(1, "2024-05-30", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-05", "Customer1", "Employee1", 100.0, "", "invalid");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Only employees or admins can create orders.");
    }

    // Create a valid order
    controller.createOrder(1, "2024-05-30", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-05", "Customer1", "Employee1", 100.0, "", "employee");

    // Try to create another order with the same order number
    try {
        controller.createOrder(1, "2024-05-30", OrderStatus::Reservation, "Car2", "2024-06-01", "2024-06-05", "Customer2", "Employee2", 200.0, "", "employee");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Order number must be unique.");
    }
}

void OrderControllerTests::testModifyOrder() {
    OrderController controller("test_orders.json");

    try {
        // Try to modify an order with invalid user type
        controller.modifyOrder(1, "start", "2024-06-02", "Employee1", "invalid");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Only employees or admins can modify orders.");
    }

    // Modify an order with valid inputs
    controller.modifyOrder(1, "start", "2024-06-02", "Employee1", "employee");

    // Try to modify a completed order
    try {
        controller.modifyOrder(1, "start", "2024-06-03", "Employee1", "employee");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Completed orders cannot be modified.");
    }
}

void OrderControllerTests::testRemoveOrder() {
    OrderController controller("test_orders.json");

    // Try to remove an order with invalid user type
    try {
        controller.removeOrder(1, "invalid", "Customer1");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Only employees or admins can delete orders.");
    }

    // Try to remove an order not belonging to the customer
    try {
        controller.removeOrder(1, "customer", "Customer2");
        assert(false); // Exception should have been thrown
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Customers can only delete their own orders.");
    }

    // Remove an order
    controller.removeOrder(1, "customer", "Customer1");
}

void OrderControllerTests::testListOrders() {
    OrderController controller("test_orders.json");

    // List orders within a specific period
    std::vector<Order> orders = controller.listOrders("2024-06-01", "2024-06-10");
    assert(orders.size() == 1); // Only one order falls within this period
}

void OrderControllerTests::testCalculateTotalSum() {
    OrderController controller("test_orders.json");

    // Calculate total sum for a specific period
    double totalSum = controller.calculateTotalSum("2024-06", "2024-06");
    assert(totalSum == 100.0); // Only one order falls within this period
}
