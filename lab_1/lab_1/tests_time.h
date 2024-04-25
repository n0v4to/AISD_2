#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "tree.h"
#include "pseudorandom.h"

void measure_fill_time() {
    for (int n : {1000, 10000, 100000}) {
        double total_duration = 0.0;
        for (int i = 0; i < 100; ++i) {
            Set set;
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < n; ++j) {
                set.insert(lcg());
            }
            auto end = std::chrono::high_resolution_clock::now();
            total_duration += std::chrono::duration<double, std::milli>(end - start).count();
        }
        double avg_fill_time = total_duration / 100;
        std::cout << "Average fill time for " << n << " elements: " << avg_fill_time << " ms" << std::endl;
    }
}

void measure_search_time() {
    for (int n : {1000, 10000, 100000}) {
        Set set;
        for (int i = 0; i < n; ++i) {
            set.insert(lcg());
        }
        double total_duration = 0.0;
        for (int i = 0; i < 1000; ++i) {
            int key_to_find = lcg();
            auto start = std::chrono::high_resolution_clock::now();
            set.contains(key_to_find);
            auto end = std::chrono::high_resolution_clock::now();
            total_duration += std::chrono::duration<double, std::milli>(end - start).count();
        }
        double avg_search_time = total_duration / 1000;
        std::cout << "Average search time in container with " << n << " elements: " << avg_search_time << " ms" << std::endl;
    }
}

void measure_add_remove_time() {
    for (int n : {1000, 10000, 100000}) {
        Set set;
        for (int i = 0; i < n; ++i) {
            set.insert(lcg());
        }
        double total_add_duration = 0.0;
        double total_remove_duration = 0.0;
        for (int i = 0; i < 1000; ++i) {
            int key_to_add = lcg();
            auto add_start = std::chrono::high_resolution_clock::now();
            set.insert(key_to_add);
            auto add_end = std::chrono::high_resolution_clock::now();
            total_add_duration += std::chrono::duration<double, std::milli>(add_end - add_start).count();
            int key_to_remove = lcg();
            auto remove_start = std::chrono::high_resolution_clock::now();
            set.erase(key_to_remove);
            auto remove_end = std::chrono::high_resolution_clock::now();
            total_remove_duration += std::chrono::duration<double, std::milli>(remove_end - remove_start).count();
        }
        double avg_add_time = total_add_duration / 1000;
        double avg_remove_time = total_remove_duration / 1000;
        std::cout << "Average add time in container with " << n << " elements: " << avg_add_time << " ms" << std::endl;
        std::cout << "Average remove time in container with " << n << " elements: " << avg_remove_time << " ms" << std::endl;
    }
}

void measure_fill_time_vector() {
    for (int n : {1000, 10000, 100000}) {
        double total_duration = 0.0;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> vec;
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < n; ++j) {
                vec.push_back(lcg());
            }
            auto end = std::chrono::high_resolution_clock::now();
            total_duration += std::chrono::duration<double, std::milli>(end - start).count();
        }
        double avg_fill_time = total_duration / 100;
        std::cout << "Average fill time for " << n << " elements in vector: " << avg_fill_time << " ms" << std::endl;
    }
}

void measure_search_time_vector() {
    for (int n : {1000, 10000, 100000}) {
        std::vector<int> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(lcg());
        }
        double total_duration = 0.0;
        for (int i = 0; i < 1000; ++i) {
            int key_to_find = lcg();
            auto start = std::chrono::high_resolution_clock::now();
            std::find(vec.begin(), vec.end(), key_to_find);
            auto end = std::chrono::high_resolution_clock::now();
            total_duration += std::chrono::duration<double, std::milli>(end - start).count();
        }
        double avg_search_time = total_duration / 1000;
        std::cout << "Average search time in vector with " << n << " elements: " << avg_search_time << " ms" << std::endl;
    }
}

void measure_add_remove_time_vector() {
    for (int n : {1000, 10000, 100000}) {
        std::vector<int> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(lcg());
        }
        double total_add_duration = 0.0;
        double total_remove_duration = 0.0;
        for (int i = 0; i < 1000; ++i) {
            int key_to_add = lcg();
            auto add_start = std::chrono::high_resolution_clock::now();
            vec.push_back(key_to_add);
            auto add_end = std::chrono::high_resolution_clock::now();
            total_add_duration += std::chrono::duration<double, std::milli>(add_end - add_start).count();
            int key_to_remove = lcg();
            auto remove_start = std::chrono::high_resolution_clock::now();
            vec.erase(std::remove(vec.begin(), vec.end(), key_to_remove), vec.end());
            auto remove_end = std::chrono::high_resolution_clock::now();
            total_remove_duration += std::chrono::duration<double, std::milli>(remove_end - remove_start).count();
        }
        double avg_add_time = total_add_duration / 1000;
        double avg_remove_time = total_remove_duration / 1000;
        std::cout << "Average add time in vector with " << n << " elements: " << avg_add_time << " ms" << std::endl;
        std::cout << "Average remove time in vector with " << n << " elements: " << avg_remove_time << " ms" << std::endl;
    }
}
