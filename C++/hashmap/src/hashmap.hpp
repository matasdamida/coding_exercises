#pragma once
#include <string>
#include <vector>

#define HASHMAP_STARTING_CAP 16
#define HASHMAP_LOAD_FACTOR 0.75
#define HASHMAP_MULT 2
#define HASH_MULT 33

template <typename V> class hashmap {
	size_t _capacity;
	size_t _size;
	std::pair<std::string, V> *_table;

	size_t hash(std::string key);

  public:
	hashmap();
	hashmap(size_t capacity);
	hashmap(const hashmap &other);
	~hashmap();
	void auto_resize();
	V &operator[](std::string key);
	std::vector<V> values();
	std::vector<std::string> keys();
	std::vector<std::pair<std::string, V>> items();
	void remove(std::string key);
	bool contains(std::string key);
	size_t size();
	bool empty();
	void clear();
};
