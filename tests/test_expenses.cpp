#include "expenses.h"
#include <iostream>
#include <cassert>
#include <tuple> // Necesario para std::tie

void test_strategy_sort_by_amount_descending() {
    ExpenseList expenses{
        {"2026-06-01", "food", "lunch", 18.50},
        {"2026-06-02", "transport", "bus", 3.20},
        {"2026-06-03", "books", "cpp", 45.00}
    };

    auto by_amount = [](const Expense& a, const Expense& b) {
        return (a.amount > b.amount) ? true : false;
        };

    sort_with(expenses, by_amount);

    assert(expenses.front().amount == 45.00);
    assert(expenses.back().amount == 3.20);
    std::cout << "test_strategy_sort_by_amount_descending PASO\n";
}

void test_strategy_sort_by_category_then_date() {
    ExpenseList expenses{
        {"2026-06-03", "transport", "bus", 3.20},
        {"2026-06-01", "books", "cpp", 45.00},
        {"2026-06-02", "books", "algorithms", 38.00}
    };

    auto by_category_then_date = [](const Expense& a, const Expense& b) {
        if (std::tie(a.category, a.date) < std::tie(b.category, b.date)) {

        }
        return (std::tie(a.category, a.date) < std::tie(b.category, b.date));
        };

    sort_with(expenses, by_category_then_date);

    assert(expenses[0].category == "books");
    assert(expenses[0].date == "2026-06-01");
    assert(expenses[2].category == "transport");
    std::cout << "test_strategy_sort_by_category_then_date PASO\n";
}

int main() {
    test_strategy_sort_by_amount_descending();
    test_strategy_sort_by_category_then_date();

    std::cout << "¡Todas las estrategias funcionan perfectamente!" << std::endl;
    return 0;
}