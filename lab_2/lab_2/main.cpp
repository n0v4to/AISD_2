#include "hash_table.h"

int main() {
    const size_t group_size = 20;
    const size_t experiments = 100;

    for (size_t table_size = 25; table_size <= 475; table_size += 50) {
        HashTable<int, int> table(table_size);
        for (size_t i = 0; i < experiments; ++i) {
            table = HashTable<int, int>(table_size);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distrib_key(0, table_size - 1);
            std::uniform_int_distribution<int> distrib_value(0, 100);

            for (size_t j = 0; j < group_size; ++j) {
                int key = distrib_key(gen);
                int value = distrib_value(gen);
                table.insert(key, value);
            }
        }
        std::cout << "Table size: " << table_size << ", Collisions: " << table.get_collisions() << std::endl;
    }

    return 0;
}