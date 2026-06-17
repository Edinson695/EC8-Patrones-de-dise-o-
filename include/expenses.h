#pragma once
#include <vector>
#include <string>
#include <functional>
#include <concepts>
#include <algorithm>
#include <ranges>

struct Expense {
	std::string date; // "2026-06-04"
	std::string category; // "food", "transport", "books"
	std::string detail;
	double amount{}; //monto
};

using ExpenseList = std::vector<Expense>;

template<class T>
concept ExpenseExporter = //exportador de gastos 
	requires(T exporter, const ExpenseList & expenses) { //como una funcion pide sus parametros 
		{ exporter.export_expenses(expenses) } -> std::same_as<std::string>;
};

using ExportFunction = std::function<std::string(const ExpenseList&)>; //funcion de xportacion

template<class R, class Cmp>
concept SortStrategy =
std::ranges::random_access_range<R> &&
std::sortable<std::ranges::iterator_t<R>, Cmp>;

void sort_with(auto& values, auto cmp)
	requires SortStrategy<decltype(values), decltype(cmp)> {

	std::ranges::sort(values, cmp);
}

template<ExpenseExporter E, class... Args>
ExportFunction make_exporter(Args&&... args) {
	return [exporter = E(std::forward<Args>(args)...)](const ExpenseList& expenses) {
		return exporter.export_expenses(expenses);
		};
}
struct CsvExporter {
	std::string export_expenses(const ExpenseList& expenses) const {
		std::string result = "date, category, detail, amount\n";
	
		for (const auto& exp : expenses) {
			result += exp.date + ", " + exp.category + ", " + exp.detail + ", " + std::to_string(exp.amount) + "\n";
		}
	}
};

struct JsonExporter {
	std::string export_expenses(const ExpenseList& expenses) const {
		std::string result = "[\n";

		for (size_t i = 0; i < expenses.size(); ++i) {
			const auto& exp = expenses[i];

			result += "{\n";
			
			result += "    \"date\": \"" + exp.date + "\",\n";
			result += "    \"category\": \"" + exp.category + "\",\n";
			result += "    \"detail\": \"" + exp.detail + "\",\n";
			result += "    \"amount\": " + std::to_string(exp.amount) + "\n";

			result += " }";

			if (i < expenses.size() - 1) {
				result += ",";
			}
			result += "\n";
		}
		result += "]\n";
		return result;
	}
};

struct TextExporter {
	std::string export_expenses(const ExpenseList& expenses) const {
		return "--- Lista de Gastos ---\n";
	}
};

template<ExpenseExporter Inner>
struct AuditedExporter {
	Inner inner;
	std::string export_expenses(const ExpenseList& expenses) const {
		return inner.export_expenses(expenses) + "\n[Auditado]";
	}
};

template<ExpenseExporter Inner>
struct SummaryExporter {
	Inner inner;
	std::string export_expenses(const ExpenseList& expenses) const {
		std::string result = inner.export_expenses(expenses);

		double total = 0.0;

		for (const auto& exp : expenses) {
			total += exp.amount;
		}

		return result + "\ntotal: " + std::to_string(total) + "\n";
	}
};