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
			_data = other._data;
		}
		return *this;
	}
	void print() {
		for (size_t i = 0; i < _size; ++i) {
			std::cout << "Bucket " << i << ": ";
			for (const auto& pair : _data[i]) {
				std::cout << pair.key << " -> " << pair.value << "; ";
			}
			std::cout << std::endl;
		}
	}
	void insert(K key, V value) {
		size_t index = hash_function(key);
		_data[index].push_back(Pair(key, value));
	}
	void insert_or_assign(K key, V value) {
		size_t index = hash_function(key);
		for (auto& pair : _data[index]) {
			if (pair.key == key) {
				pair.value = value;
				return;
			}
		}
		_data[index].push_back(Pair(key, value));
	}
	bool contains(V value) {
		for (const auto& bucket : _data) {
			for (const auto& pair : bucket) {
				if (pair.value == value) {
					return true;
				}
			}
		}
		return false;
	}
	V* search(K key) {
		size_t index = hash_function(key);
		for (auto& pair : _data[index]) {
			if (pair.key == key) {
				return &pair.value;
			}
		}
		return nullptr;
	}
	bool erase(K key) {
		size_t index = hash_function(key);
		for (auto it = _data[index].begin(); it != _data[index].end(); ++it) {
			if (it->key == key) {
				_data[index].erase(it);
				return true;
			}
		}
		return false;
	}
	int count(K key) {
		size_t index = hash_function(key);
		int count = 0;
		for (const auto& pair : _data[index]) {
			if (pair.key == key) {
				count++;
			}
		}
		return count;
	}
};