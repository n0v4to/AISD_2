#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <random>

template<typename K, typename V>
class HashTable {
	struct Pair
	{
		K key;
		V value;
		bool not_empty;
		Pair():	 key(0), value(0), not_empty(false) {}
		Pair(const K& key, const V& value) : key(key), value(value), not_empty(true) {}
	};
	std::vector<std::list<Pair>> _data;
	size_t _size;
	size_t hash_function(const K& key) {
		return key % _size;
	}
public:
	HashTable(size_t size): _size(size), _data(size) {}
	HashTable(size_t size, size_t num_elements) : _size(size), _data(size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<K> distrib_key(0, size - 1);
		std::uniform_int_distribution<V> distrib_value(0, 100);

		for (size_t i = 0; i < num_elements; ++i) {
			K key = distrib_key(gen);
			V value = distrib_value(gen);
			insert(key, value);
		}
	}
	HashTable(const HashTable& other): _size(other._size), _data(other._data) {}
	~HashTable() {}
	HashTable& operator=(const HashTable& other) {
		if (this != other) {
			_size = other._size;
			_data = other._data
		}
		return *this;
	}
};