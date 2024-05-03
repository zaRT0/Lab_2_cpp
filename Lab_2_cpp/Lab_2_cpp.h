#pragma once
#include <iostream>

using namespace std;
namespace hash {

	template <typename T>
	class HashTable {
	private:

		struct Node {
			int _key;
			T _value;
			bool _deleted;
			Node() : _key(0), _deleted(1) {}
			Node(int key, const T& value) : _key(key), _value(value), _deleted(0) {}
		};

		Node* _hash_table;
		int _capacity;
		int _size;
		  
		int find_the_position(int key) const;
		int hash(int key) const;
		void resize(int new_size);

	public:

		HashTable(int first_size = 10);

		HashTable(const HashTable& other);

		HashTable& operator=(const HashTable& other);

		void insert(int key, const T& value);

		void insert_or_assign(int key, const T& value);

		bool contains(const T& value) const;

		T* search(int key);

		int count(int key) const;

		void print() const;

		bool erase(int key);

		~HashTable();

		int hash_to_roman(const string& roman);
	};

	template <typename T>
	HashTable<T>::HashTable(int first_size) : _size(0), _capacity(first_size) {
		this->_hash_table = new Node[_capacity];
	}

	template<typename T>
    HashTable<T>::HashTable(const HashTable& other) : _size(other._size), _capacity(other._capacity) {
		_hash_table = new Node[_capacity];
		for (int i = 0; i < _capacity; ++i) {
			_hash_table[i] = other._hash_table[i];
		}
	}

	template<typename T>
	HashTable<T>& HashTable<T>::operator=(const HashTable& other) {
		if (this != &other) {
			delete[] _hash_table;
			this->_size = other._size;
			this->_capacity = other._capacity;
			_hash_table = new Node[_capacity];
			for (int i = 0; i < _capacity; ++i) {
				_hash_table[i] = other._hash_table[i];
			}
		}
		return *this;
	}

	template<typename T>
	inline int HashTable<T>::hash(int key) const {
		const double value_a = 0.6180339887;
		double fractional_part = value_a * key - int(value_a * key);
		int result = _capacity * fractional_part;
		return result;
	}

	template<typename T>
	inline int HashTable<T>::find_the_position(int key) const {
		int hash_value = hash(key);
		int initial_position = hash_value % _capacity;
		int position = initial_position;
		do {
			if (_hash_table[position]._key == key && !_hash_table[position]._deleted) {
				return position;
			}
			if (_hash_table[position]._deleted) {
				break;
			}
			position = (position + 1) % _capacity;
		} while (position != initial_position);

		return -1;
	}

	template<typename T>
	inline void HashTable<T>::resize(int new_size) {
		Node* new_hash_table = new Node[new_size];
		for (int i = 0; i < _capacity; ++i) {
			if (!_hash_table[i]._deleted) {
				int new_position = hash(_hash_table[i]._key) % new_size;
				while (!new_hash_table[new_position]._deleted) {
					new_position = (new_position + 1) % new_size;
				}
				new_hash_table[new_position] = _hash_table[i];
			}
		}
		delete[] _hash_table;
		_hash_table = new_hash_table;
		_capacity = new_size;
	}

	template<typename T>
	inline void HashTable<T>::insert(int key, const T& value) {
		if (_size >= 0.75 * _capacity) {
			resize(2 * _capacity);
		}
		int position = hash(key) % _capacity;
		while (!_hash_table[position]._deleted && _hash_table[position]._key != key) {
			position = (position + 1) % _capacity;
		}
		if (_hash_table[position]._deleted) {
			++_size;
		}
		_hash_table[position] = Node(key, value);
		_hash_table[position]._deleted = false;
	}

	template<typename T>
	inline void HashTable<T>::insert_or_assign(int key, const T& value) {
		if (_size >= 0.75 * _capacity) {
			resize(2 * _capacity);
		}
		int position = hash(key) % _capacity;
		int initial_position = position;
		do {
			if (_hash_table[position]._key == key && !_hash_table[position]._deleted) {
				_hash_table[position]._value = value;
				return;
			}
			position = (position + 1) % _capacity;
		} while (position != initial_position && !_hash_table[position]._deleted);

		if (_hash_table[position]._deleted) {
			++_size;
		}
		_hash_table[position] = Node(key, value);
		_hash_table[position]._deleted = false;
	}

	template<typename T>
	inline bool HashTable<T>::contains(const T& value) const {
		for (int i = 0; i < _capacity; ++i) {
			if (!_hash_table[i]._deleted && _hash_table[i]._ value == value) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T* HashTable<T>::search(int key) {
		int position = find_the_position(key);
		if (position != -1) {
			return &(_hash_table[position]._value);
		}
		return nullptr;
	}

	template<typename T>
	inline int HashTable<T>::count(int key) const {
		int counter = 0;
		int position = hash(key) % _capacity;
		while (!_hash_table[position]._deleted && (_hash_table[position]._key != key || _hash_table[position]._deleted)) {
			if (_hash_table[position]._key == key) {
				++counter;
			}
			position = (position + 1) % _capacity;
		}
		return counter;
	}

	template<typename T>
	inline void HashTable<T>::print() const {
		for (int i = 0; i < _capacity; ++i) {
			if (!_hash_table[i]._deleted) {
				cout << "Ключ: " << _hash_table[i]._key << endl; 
				cout << "Значение: " << _hash_table[i]._value << endl;
			}
		}
	}

	template<typename T>
	inline bool HashTable<T>::erase(int key) {
		int position = find_the_position(key);
		if (position != -1) {
			_hash_table[position]._deleted = true;
			--_size;
			return true;
		}
		return false;
	}

	template<typename T>
	inline HashTable<T>::~HashTable() {
		delete[] _hash_table;
	}

	template<typename T>
	inline int HashTable<T>::hash_to_roman(const string& roman) {
		const char roman_symbols[] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
		const int roman_values[] = { 1, 5, 10, 50, 100, 500, 1000 };
		const string invalid_combinations[] = { "IIII", "VV", "XXXX", "LL", "CCCC", "DD", "MMMM" };
		int result = 0;
		int prev_value = 0;

		for (const auto& combination : invalid_combinations) {
			if (roman.find(combination) != string::npos) {
				return 0;
			}
		}

		for (int i = roman.size() - 1; i >= 0; --i) {
			char symbol = roman[i];
			int value = 0;
			bool valid_symbol = false;

			for (int j = 0; j < sizeof(roman_symbols); ++j) {
				if (roman_symbols[j] == symbol) {
					value = roman_values[j];
					valid_symbol = true;
					break;
				}
			}

			if (!valid_symbol) {
				return 0;
			}

			if (value < prev_value) {
				if (!((prev_value == 5 && (value == 1 || value == 10)) ||
					(prev_value == 10 && (value == 1 || value == 50)) ||
					(prev_value == 50 && (value == 10 || value == 100)) ||
					(prev_value == 100 && (value == 10 || value == 500)) ||
					(prev_value == 500 && (value == 100 || value == 1000)))) {
					return 0;
				}
				result -= value;
			}
			else {
				result += value;
			}
			prev_value = value;
		}
		return result;
	}
}