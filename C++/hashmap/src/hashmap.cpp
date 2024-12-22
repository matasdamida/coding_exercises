#include "hashmap.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename V> size_t hashmap<V>::djb2(std::string key) {
	assert(!key.empty());
	size_t hash = 5381;
	for (size_t i = 0; i < key.size(); i++) {
		hash = ((hash << 5) + hash) + key[i];
	}
	return hash % _capacity;
}

template <typename V>
hashmap<V>::hashmap()
	: _capacity(HASHMAP_STARTING_CAP), _size(0),
	  _table(new std::pair<std::string, V>[_capacity]) {}

template <typename V>
hashmap<V>::hashmap(size_t capacity)
	: _capacity(capacity), _size(0),
	  _table(new std::pair<std::string, V>[_capacity]) {}

template <typename V>
hashmap<V>::hashmap(const hashmap &other)
	: _capacity(other._capacity), _size(other._size),
	  _table(new std::pair<std::string, V>[_capacity]) {
	std::copy(other._table, other._table + other._capacity, _table);
}

template <typename V> hashmap<V>::~hashmap() { delete[] _table; }

template <typename V> void hashmap<V>::auto_resize() {
	if (_size >= _capacity * HASHMAP_LOAD_FACTOR) {
		size_t old_capacity = _capacity;
		_capacity *= HASHMAP_MULT;
		std::pair<std::string, V> *new_table =
			new std::pair<std::string, V>[_capacity];
		for (size_t i = 0; i < old_capacity; i++) {
			if (!_table[i].first.empty()) {
				size_t index = djb2(_table[i].first);
				while (!new_table[index].first.empty()) {
					index = (index + 1) % _capacity;
				}
				new_table[index] = _table[i];
			}
		}
		delete[] _table;
		_table = new_table;
	}
}

template <typename V> V &hashmap<V>::operator[](std::string key) {
	assert(!key.empty());
	auto_resize();
	size_t index = djb2(key);
	while (_table[index].first != key && !_table[index].first.empty()) {
		index = (index + 1) % _capacity;
	}
	if (_table[index].first.empty()) {
		_table[index].first = key;
		++_size;
	}
	return _table[index].second;
}

template <typename V> std::vector<V> hashmap<V>::values() {
	std::vector<V> values;
	for (size_t i = 0; i < _capacity; i++) {
		if (!_table[i].first.empty()) {
			values.push_back(_table[i].second);
		}
	}
	return values;
}

template <typename V> std::vector<std::string> hashmap<V>::keys() {
	std::vector<std::string> keys;
	for (size_t i = 0; i < _capacity; i++) {
		if (!_table[i].first.empty()) {
			keys.push_back(_table[i].first);
		}
	}
	return keys;
}

template <typename V>
std::vector<std::pair<std::string, V>> hashmap<V>::items() {
	std::vector<std::pair<std::string, V>> items;
	for (size_t i = 0; i < _capacity; i++) {
		if (!_table[i].first.empty()) {
			items.push_back(_table[i]);
		}
	}
	return items;
}

template <typename V> void hashmap<V>::remove(std::string key) {
	assert(!key.empty());
	size_t starting_index = djb2(key);
	size_t index = starting_index;
	while (_table[index].first != key && !_table[index].first.empty()) {
		index = (index + 1) % _capacity;
		if (index == starting_index) {
			return;
		}
	}
	_table[index].first.clear();
	--_size;
}

template <typename V> bool hashmap<V>::contains(std::string key) {
	assert(!key.empty());
	size_t starting_index = djb2(key);
	size_t index = starting_index;
	while (_table[index].first != key && !_table[index].first.empty()) {
		index = (index + 1) % _capacity;
		if (index == starting_index) {
			return false;
		}
	}
	return !_table[index].first.empty();
}

template <typename V> size_t hashmap<V>::size() { return _size; }

template <typename V> bool hashmap<V>::empty() { return _size == 0; }

template <typename V> void hashmap<V>::clear() {
	delete[] _table;
	_capacity = HASHMAP_STARTING_CAP;
	_size = 0;
	_table = new std::pair<std::string, V>[_capacity];
}

#include "hashmap.inl"