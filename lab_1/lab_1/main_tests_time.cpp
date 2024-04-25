#include "tests_time.h"
#include "tree.h"

int main() {
	measure_fill_time();
	measure_search_time();
	measure_add_remove_time();
	std::cout << "\n" << std::endl;
	measure_fill_time_vector();
	measure_search_time_vector();
	measure_add_remove_time_vector();

	/*Set set1;
	set1.insert(1);
	set1.insert(2);
	set1.insert(3);
	set1.insert(4);
	set1.insert(5);
	set1.insert(6);
	set1.insert(7);
	std::cout << "First set:" << "\n";
	set1.print();

	Set set2;
	set2.insert(4);
	set2.insert(5);
	set2.insert(6);
	set2.insert(7);
	set2.insert(8);
	set2.insert(9);
	set2.insert(10);
	std::cout << "Second set:" << "\n";
	set2.print();

	Set dif = set1.difference(set1, set2);
	std::cout << "Difference:" << "\n";
	dif.print();
	
	Set inter = set2.intersection(set1, set2);
	std::cout << "Intersection:" << "\n";
	inter.print();*/
}