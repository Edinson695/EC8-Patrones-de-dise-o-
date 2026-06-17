#pragma once

struct Expense {
	std::string date; // "2026-06-04"
	std::string category; // "food", "transport", "books"
	std::string detail;
	double amount{};
};
using ExpenseList = std::vector<Expense>;
template<class T>
concept ExpenseExporter =
	requires(T exporter, const ExpenseList & expenses) {
		{ exporter.export_expenses(expenses) } -> std::same_as<std::string>;
};
using ExportFunction = std::function<std::string(const ExpenseList&)>;
template<class R, class Cmp>
concept SortStrategy =
std::ranges::random_access_range<R> &&
std::sortable<std::ranges::iterator_t<R>, Cmp>;
void sort_with(auto& values, auto cmp)
	requires SortStrategy<decltype(values), decltype(cmp)>;

template<ExpenseExporter E, class... Args>
ExportFunction make_exporter(Args&&... args);
struct CsvExporter {
	std::string export_expenses(const ExpenseList& expenses) const;
};
struct JsonExporter {
	std::string export_expenses(const ExpenseList& expenses) const;
};
struct TextExporter {
	std::string export_expenses(const ExpenseList& expenses) const;
};
template<ExpenseExporter Inner>
struct AuditedExporter {
	Inner inner;
	std::string export_expenses(const ExpenseList& expenses) const;
};
template<ExpenseExporter Inner>
struct SummaryExporter {
	Inner inner;
	std::string export_expenses(const ExpenseList& expenses) const;
};