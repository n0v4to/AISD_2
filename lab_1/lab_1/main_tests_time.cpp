#include "tests_time.h"

int main() {
	measure_fill_time();
	measure_search_time();
	measure_add_remove_time();
	std::cout << "\n" << std::endl;
	measure_fill_time_vector();
	measure_search_time_vector();
	measure_add_remove_time_vector();
}