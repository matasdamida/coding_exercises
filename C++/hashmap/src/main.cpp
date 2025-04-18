#include "../../../C/lib/custom_testing.h"
#include "hashmap.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::string read_file(const std::string &filename) {
	std::ifstream file(filename);
	std::string content((std::istreambuf_iterator<char>(file)),
						std::istreambuf_iterator<char>());
	return content;
}

std::vector<std::string> split_whitespace(const std::string &s) {
	std::vector<std::string> tokens;
	std::istringstream stream(s);
	std::string token;
	while (stream >> token) {
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);
		tokens.push_back(token);
	}
	return tokens;
}

// start and stop timer funcs
#include <chrono>
std::chrono::time_point<std::chrono::high_resolution_clock> start;

void start_timer() { start = std::chrono::high_resolution_clock::now(); }

size_t stop_timer() {
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	return duration.count();
}

size_t count_words_hashmap(const std::vector<std::string> &words) {
	start_timer();
	hashmap<int> word_count;
	for (const std::string &word : words) {
		if (word.empty()) {
			continue;
		}
		word_count[word]++;
	}
	return stop_timer();
	// std::vector<std::pair<std::string, int>> items = word_count.items();
	// std::sort(items.begin(), items.end(),
	// 		  [](const std::pair<std::string, int> &a,
	// 			 const std::pair<std::string, int> &b) {
	// 			  return a.second > b.second;
	// 		  });
	// for (size_t i = 0; i < 10 && i < items.size(); i++) {
	// 	std::cout << items[i].first << ": " << items[i].second << std::endl;
	// }
}

size_t count_words_unordered_map(const std::vector<std::string> &words) {
	start_timer();
	std::unordered_map<std::string, int> word_count;
	for (const std::string &word : words) {
		if (word.empty()) {
			continue;
		}
		word_count[word]++;
	}
	return stop_timer();
	// std::vector<std::pair<std::string, int>> items(word_count.begin(),
	// 											   word_count.end());
	// std::sort(items.begin(), items.end(),
	// 		  [](const std::pair<std::string, int> &a,
	// 			 const std::pair<std::string, int> &b) {
	// 			  return a.second > b.second;
	// 		  });
	// for (size_t i = 0; i < 10 && i < items.size(); i++) {
	// 	std::cout << items[i].first << ": " << items[i].second << std::endl;
	// }
}

int main(void) {
	std::string content = read_file("shakespeare.txt");
	std::cout << "Content length: " << content.size() << std::endl;

	std::vector<std::string> words = split_whitespace(content);
	std::cout << "Words: " << words.size() << std::endl;

	std::cout << std::endl;

	std::cout << "Using custom hashmap:" << std::endl;
	size_t time = 0;
	for (size_t i = 0; i < 100; i++) {
		time += count_words_hashmap(words);
	}
	std::cout << "Average time: " << time / 100 << "ms" << std::endl;

	std::cout << std::endl;

	std::cout << "Using std::unordered_map:" << std::endl;
	time = 0;
	for (size_t i = 0; i < 100; i++) {
		time += count_words_hashmap(words);
	}
	std::cout << "Average time: " << time / 100 << "ms" << std::endl;

	return 0;
}
