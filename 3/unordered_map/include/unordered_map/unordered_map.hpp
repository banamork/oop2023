#ifndef _unordered_map_hpp_
#define _unordered_map_hpp_

#include <stdexcept>
#include <functional>
#include <utility>
#include <type_traits> 
#include <cassert> 

namespace vaa
{
	/**
	* @brief A custom implementation of an unordered map container.
	*
	* This class provides an unordered map that stores key-value pairs and allows for insertion,
	* removal, and searching of elements in constant average time.
	*
	* @tparam Key The type of the keys in the map.
	* @tparam Value The type of the values in the map.
	* @tparam Hash The hash function type. By default, it uses std::hash<Key>.
	* @tparam Equal The equality comparison function for keys. By default, it uses std::equal_to<Key>.
	*/

	template<typename Key, typename Value, typename Hash = std::hash<Key>, typename Equal = std::equal_to<Key>>
	class unordered_map
	{

	public:
		template<typename T, bool is_const>
		class Iterator;

		using iterator = Iterator<std::pair<Key, Value>, false>;

		using const_iterator = Iterator<std::pair<Key, Value>, true>;

	private:

		struct Node
		{
			std::pair<Key, Value> value_;

			Node* next_;

			Node() = default;

			Node(const std::pair<Key, Value>& value) : value_(value), next_(nullptr) {}
		};

		Node** data_;

		size_t size_;

		size_t count_;

		float max_load_factor_;

		size_t hash_function(const Key& key)
		{
			return Hash{}(key);
		}

	public:

		/**
	    * @brief Default constructor for the unordered_map.
	    *
	    * Initializes the unordered_map with default parameters.
	    */

		unordered_map() noexcept: size_(0), count_(1), max_load_factor_(1.0f)
		{
			data_ = new Node * [count_]();
		}

		/**
	    * @brief Copy constructor for the unordered_map.
	    *
	    * Copies elements from the given map to construct a new unordered_map.
	    *
	    * @param map The unordered_map to be copied.
	    *
	    * @throw An exception is thrown if memory allocation fails while copying elements.
	    */

		unordered_map(const unordered_map& map) : size_(map.size_), count_(map.count_), max_load_factor_(map.max_load_factor_)
		{
			data_ = new Node * [count_]();
			try
			{
				for (size_t i = 0; i < count_; i++)
				{
					if (map.data_[i] == nullptr)
					{
						continue;
					}
					Node* node = map.data_[i];
					Node** current = &data_[i];
					while (node != nullptr)
					{
						*current = new Node(node->value_);
						current = &((*current)->next_);
						node = node->next_;
					}
				}
			}
			catch (...)
			{
				for (size_t i = 0; i < count_; i++)
				{
					Node* node = data_[i], *pred = nullptr;
					while (node != nullptr)
					{
						pred = node;
						node = node->next_;
						delete pred;
					}
				}
				delete[] data_;
				throw; 
			}
		}

		/**
		* @brief Move constructor for unordered_map.
		*
		* Moves the resources from the given map to construct a new unordered_map.
		*
		* @param map The unordered_map to be moved.
		*/

		unordered_map(unordered_map&& map) noexcept : size_(map.size_), count_(map.count_), data_(map.data_), max_load_factor_(map.max_load_factor_)
		{
			map.data_ = nullptr;
			map.count_ = 0;
			map.size_ = 0;
			map.max_load_factor_ = 0.0;
		}

		/**
		* @brief Copy assignment operator for unordered_map.
		*
		* Copies elements from the given map to construct a new unordered_map and swaps the contents with the current map.
		*
		* @param map The unordered_map to be copied.
		*
		* @return A reference to the modified unordered_map.
		*/

		unordered_map& operator = (const unordered_map& map)
		{
			unordered_map new_unordered_map(map);
			swap(new_unordered_map);
			return *this;
		}

		/**
		* @brief Move assignment operator for unordered_map.
		*
		* Moves the resources from the given map and swaps the contents with the current map.
		*
		* @param map The unordered_map to be moved.
		*
		* @return A reference to the modified unordered_map.
		*/

		unordered_map& operator = (unordered_map&& map) noexcept
		{
			swap(map);
			return *this;
		}

		/**
		* @brief Swaps the contents of two unordered_map objects.
		*
		* Swaps the internal data and fields with the given map.
		*
		* @param map The unordered_map to be swapped with.
		*/

		void swap(unordered_map& map) noexcept
		{
			std::swap(size_, map.size_);
			std::swap(count_, map.count_);
			std::swap(data_, map.data_);
		}

		/**
		* @brief Finds the element with the given key.
		*
		* @param key The key to search for.
		*
		* @return An iterator to the found element, or end() if the element is not found.
		*/

		iterator find(const Key& key)
		{
			size_t index = hash_function(key) % count_;
			Node* node = data_[index];
			while (node != nullptr)
			{
				if (key == node->value_.first)
				{
					return iterator(data_, count_, index, node);
				}
				node = node->next_;
			}
			return end();
		}

		/**
		* @brief Finds the element with the given key (const version).
		*
		* @param key The key to search for.
		*
		* @return A const_iterator to the found element, or end() if the element is not found.
		*/

		const_iterator find(const Key& key) const
		{
			size_t index = hash_function(key) % count_;
			Node* node = data_[index];
			while (node != nullptr)
			{
				if (key == node->value_.first)
				{
					return const_iterator(data_, count_, index, node);
				}
				node = node->next_;
			}
			return end();
		}

		/**
		* @brief Constructs and inserts a new element into the unordered_map.
		*
		* This function constructs an element in-place and inserts it into the unordered_map.
		*
		* @tparam Args Types of arguments for constructing the new element.
		* @param args Arguments to forward to the constructor of the new element.
		*
		* @return A pair with an iterator to the inserted element and a bool indicating the success of the insertion.
		*/

		template<typename... Args>
		std::pair<iterator, bool> emplace(Args&&... args)
		{
			std::pair<Key, Value> pair(std::forward<Args>(args)...);
			return insert(std::move(pair));
		}

		/**
		* @brief Inserts elements from an initializer list into the unordered_map.
		*
		* This function inserts elements from the provided initializer list into the unordered_map.
		*
		* @param list The initializer list of key-value pairs.
		*/

		void insert(std::initializer_list<std::pair<Key, Value>> list)
		{
			for (const auto& element : list)
			{
				insert(element);
			}
		}

		/**
		* @brief Erases the element with the given key from the unordered_map.
		*
		* This function erases the element with the provided key from the unordered_map.
		*
		* @param key The key of the element to be erased.
		*/

		void erase(const Key& key)
		{
			size_t index = hash_function(key) % count_;
			Node* node = data_[index], *pred = nullptr;
			while (node != nullptr && key != node->value_.first)
			{
				pred = node;
				node = node->next_;
			}
			if (node == nullptr)
			{
				return;
			}
			if (pred == nullptr)
			{
				data_[index] = node->next_;
			}
			else
			{
				pred->next_ = node->next_;
			}
			size_--;

			delete node;
		}

		/**
		* @brief Inserts a new element into the unordered_map (move version).
		*
		* Inserts the provided pair into the unordered_map. If the key already exists, returns an iterator to the existing element.
		*
		* @param pair The key-value pair to be inserted.
		*
		* @return A pair with an iterator to the inserted element and a bool indicating the success of the insertion.
		*/

		std::pair<iterator, bool> insert(std::pair<Key, Value>&& pair)
		{
			auto it = find(pair.first);
			if (it != end())
			{
				return std::make_pair(it, false);
			}
			size_t index = hash_function(pair.first) % count_;
			Node* node = new Node(std::move(pair));
			node->next_ = data_[index];
			data_[index] = node;
			size_++;
			if (size_ > max_load_factor_ * count_)
			{
				resize(count_ * 2);
			}
			return std::make_pair(iterator(data_, count_, index, node), true);
		}

		/**
		* @brief Inserts a new element into the unordered_map (const reference version).
		*
		* Inserts the provided pair into the unordered_map. If the key already exists, returns an iterator to the existing element.
		*
		* @param pair The key-value pair to be inserted.
		*
		* @return A pair with an iterator to the inserted element and a bool indicating the success of the insertion.
		*/

		std::pair<iterator, bool> insert(const std::pair<Key, Value>& pair)
		{
			auto it = find(pair.first);
			if (it != end())
			{
				return std::make_pair(it, false);
			}
			size_t index = hash_function(pair.first) % count_;
			Node* node = new Node(pair);
			node->next_ = data_[index];
			data_[index] = node;
			size_++;
			if (size_ > max_load_factor_ * count_)
			{
				resize(count_ * 2);
			}
			return std::make_pair(iterator(data_, count_, index, node), true);
		}

		/**
		* @brief Provides access to the value associated with the given key.
		*
		* If the key exists, returns a reference to the associated value. If the key does not exist,
		* creates a new element with the provided key and returns a reference to its associated value.
		*
		* @param key The key for which to access the value.
		*
		* @return A reference to the value associated with the given key.
		*/

		Value& operator[](const Key& key)
		{
			auto it = find(key);
			if (it != end()) 
			{
				return it->second;
			}
			return emplace(key, Value()).first->second;
		}

		/**
		* @brief Provides access to the value associated with the given move-only key.
		*
		* If the key exists, returns a reference to the associated value. If the key does not exist,
		* creates a new element with the provided key and returns a reference to its associated value.
		*
		* @param key The move-only key for which to access the value.
		*
		* @return A reference to the value associated with the given key.
		*/

		Value& operator[](Key&& key)
		{
			auto it = find(key);
			if (it != end())
			{
				return it->second;
			}
			return emplace(std::move(key), Value()).first->second;
		}

		/**
		* @brief Provides access to the value associated with the given key, throwing an exception if the key is not found.
		*
		* @param key The key for which to access the value.
		*
		* @return A reference to the value associated with the given key.
		*
		* @throw std::out_of_range If the key is not found in the unordered_map.
		*/

		Value& at(const Key& key)
		{
			auto it = find(key);
			if (it == end())
			{
				throw std::out_of_range("Key is not found\n");
			}
			return it->second;
		}

		/**
		* @brief Provides access to the value associated with the given key (const version), throwing an exception if the key is not found.
		*
		* @param key The key for which to access the value.
		*
		* @return A reference to the value associated with the given key.
		*
		* @throw std::out_of_range If the key is not found in the unordered_map.
		*/

		const Value& at(const Key& key) const
		{
			auto it = find(key);
			if (it == end())
			{
				throw std::out_of_range("Key is not found\n");
			}
			return it->second;
		}

		/**
		* @brief Resizes the unordered_map to the specified count.
		*
		* Resizes the unordered_map to accommodate the specified count, rehashing elements if necessary.
		*
		* @param count The new size of the unordered_map.
		*/

		void resize(size_t count)
		{
			if (count <= count_)
			{
				return;
			}
			Node** new_data = new Node * [count]();
			size_t old_count = count_;
			Node** old_data = data_;
			data_ = new_data;
			count_ = count;
			size_ = 0;
			for (size_t i = 0; i < old_count; i++)
			{
				Node* node = old_data[i], *pred = nullptr;
				while (node != nullptr)
				{
					insert(node->value_);
					pred = node;
					node = node->next_;
					delete pred;
				}
			}
			delete[] old_data;
		}
		
		/**
		* @brief Removes all elements from the unordered_map.
		*
		* Clears the unordered_map, destroying all elements and setting the size to 0.
		*/

		void clear() noexcept
		{
			for (size_t i = 0; i < count_; i++)
			{
				Node* node = data_[i], *pred = nullptr;
				while (node != nullptr)
				{
					pred = node;
					node = node->next_;
					delete pred;
				}
				data_[i] = nullptr;
			}
			size_ = 0;
		}

		/**
		* @brief Checks if the unordered_map is empty.
		*
		* @return true if the unordered_map is empty, false otherwise.
		*/

		bool empty() const noexcept
		{
			return size_ == 0;
		}

		/**
		* @brief Returns the number of elements in the unordered_map.
		*
		* @return The number of elements in the unordered_map.
		*/

		size_t size() const noexcept
		{
			return size_;
		}

		/**
		* @brief Returns the number of buckets in the unordered_map.
		*
		* @return The number of buckets in the unordered_map.
		*/

		size_t bucket_count() const noexcept
		{
			return count_;
		}

		/**
		* @brief Returns the maximum possible size of the unordered_map.
		*
		* @return The maximum possible size of the unordered_map.
		*/

		size_t max_size() const noexcept
		{
			return std::numeric_limits<std::ptrdiff_t>::max();
		}

		/**
		* @brief Returns an iterator to the beginning of the unordered_map.
		*
		* @return An iterator to the beginning of the unordered_map.
		*/

		iterator begin()
		{
			return iterator(data_, count_);
		}

		/**
		* @brief Returns a const iterator to the beginning of the unordered_map.
		*
		* @return A const_iterator to the beginning of the unordered_map.
		*/

		const_iterator begin() const
		{
			return const_iterator(data_, count_);
		}

		/**
		* @brief Returns a const iterator to the beginning of the unordered_map.
		*
		* @return A const_iterator to the beginning of the unordered_map.
		*/

		const_iterator cbegin() const
		{
			return const_iterator(data_, count_);
		}

		/**
		* @brief Returns a iterator to the endnning of the unordered_map.
		*
		* @return A iterator to the endinning of the unordered_map.
		*/

		iterator end()
		{
			return iterator(data_, count_, count_);
		}

		/**
		* @brief Returns a const iterator to the endnning of the unordered_map.
		*
		* @return A const_iterator to the endinning of the unordered_map.
		*/

		const_iterator end() const
		{
			return const_iterator(data_, count_, count_);
		}

		/**
		* @brief Returns a const iterator to the endnning of the unordered_map.
		*
		* @return A const_iterator to the endinning of the unordered_map.
		*/

		const_iterator cend() const
		{
			return const_iterator(data_, count_, count_);
		}

		/**
		* @brief Destroys the unordered_map, releasing all allocated memory.
		*/

		~unordered_map()
		{
			clear();
			delete[] data_;
		}

	public:

		/**
		* @brief Represents an iterator class for traversing elements in the unordered_map.
		*
		* This class provides an iterator for traversing the elements within the unordered_map.
		*
		* @tparam T The type of elements stored in the unordered_map.
		* @tparam is_const A flag indicating whether the iterator is const.
		*/

		template<typename T, bool is_const>
		class Iterator
		{
		private:
			Node** data_;

			Node* node_;

			size_t index_;

			size_t count_;
		
			void search()
			{
				while (index_ < count_ && data_[index_] == nullptr)
				{
					index_++;
				}
				node_ = (index_ < count_) ? data_[index_] : nullptr;
			}

		public:
			friend Iterator<T,  !is_const>;

			using difference_type = std::ptrdiff_t;

			using value_type = std::conditional_t<is_const, const T, T>;

			using pointer = value_type*;

			using reference = value_type&;

			using iterator_category = std::forward_iterator_tag;

			Iterator() = default;

			/**
			* @brief Constructs an iterator with the given parameters.
			*
			* Constructs an iterator with the provided parameters.
			*
			* @param nodes The array of nodes for the unordered_map.
			* @param count The number of nodes in the unordered_map.
			* @param index The index for the iterator.
			* @param node The current node for the iterator.
			*/

			Iterator(Node** nodes, size_t count, size_t index = 0, Node* node = nullptr) :
				data_(nodes), count_(count), index_(index), node_(node) 
			{
				if (node_ == nullptr)
				{
					search();
				}
			}

			/**
			* @brief Copy constructor for the Iterator class.
			*
			* Constructs an Iterator by copying the contents of the given Iterator, with considerations for const-correctness.
			* Only available if the other iterator is non-const or equally const.
			*
			* @tparam other_const A flag indicating whether the other iterator is const.
			* @param o The Iterator to be copied.
			*/

			template<bool other_const>
			Iterator(Iterator<T, other_const>& o) noexcept
				requires (is_const >= other_const)
			: data_(o.data_), count_(o.count_), index_(o.index_), node_(o.node_) {};

			/**
			* @brief Move constructor for the Iterator class.
			*
			* Constructs an Iterator by moving the contents of the given Iterator, with considerations for const-correctness.
			* Only available if the other iterator is non-const or equally const.
			*
			* @tparam other_const A flag indicating whether the other iterator is const.
			* @param o The Iterator to be moved from.
			*/

			template<bool other_const>
			Iterator(Iterator<T, other_const >&& o) noexcept
				requires (is_const >= other_const)
			: data_(o.data_), count_(o.count_), index_(o.index_), node_(o.node_)
			{
				o.count_ = 0;
				o.index_ = 0;
				o.data_ = nullptr;
				o.node_ = nullptr;
			};

			/**
			* @brief Copy assignment operator for the Iterator class.
			*
			* Assigns the contents of the given Iterator to this Iterator, with considerations for const-correctness.
			* Only available if the other iterator is non-const or equally const.
			*
			* @tparam other_const A flag indicating whether the other iterator is const.
			* @param o The Iterator to be assigned.
			*
			* @return A reference to the modified Iterator.
			*/

			template<bool other_const>
			Iterator& operator = (const Iterator<T, other_const>& o) noexcept
				requires (is_const >= other_const)
			{
				data_ = o.data_;
				node_ = o.node_;
				index_ = o.index_;
				count_ = o.count_;
				return *this;
			}

			/**
			* @brief Move assignment operator for the Iterator class.
			*
			* Assigns the contents of the given Iterator to this Iterator by moving, with considerations for const-correctness.
			* Only available if the other iterator is non-const or equally const.
			*
			* @tparam other_const A flag indicating whether the other iterator is const.
			* @param o The Iterator to be moved from.
			*
			* @return A reference to the modified Iterator.
			*/

			template<bool other_const>
			Iterator& operator = (Iterator<T, other_const>&& o) noexcept
				requires (is_const >= other_const)
			{
				data_ = o.data_;
				node_ = o.node_;
				index_ = o.index_;
				count_ = o.count_;
				o.node_ = nullptr;
				o.count_ = 0;
				o.index_ = 0;
				o.data_ = nullptr;
				return *this;
			}

			/**
			* @brief Returns a reference to the value being pointed to by the iterator.
			*
			* @return A reference to the value being pointed to by the iterator.
			*/

			reference operator * ()
			{
				return node_->value_;
			}

			/**
			* @brief Returns a pointer to the value being pointed to by the iterator.
			*
			* @return A pointer to the value being pointed to by the iterator.
			*/

			pointer operator -> ()
			{
				return &(node_->value_);
			}

			/**
			* @brief Advances the iterator to the next element in the unordered_map.
			*
			* @return A reference to the advanced iterator.
			*/

			Iterator& operator++()
			{
				if (node_ != nullptr && node_->next_ != nullptr)
				{
					node_ = node_->next_;
				}
				else
				{
					index_++;
					search();
				}
				return *this;
			}

			/**
			* @brief Postfix increment operator for the iterator.
			*
			* @return The iterator prior to advancing.
			*/

			Iterator operator++(int)
			{
				Iterator it = *this;
				++(*this);
				return it;
			}

			/**
			* @brief Checks if two iterators are equal.
			*
			* @param it The iterator to compare with.
			*
			* @return true if the iterators are equal, false otherwise.
			*/

			bool operator == (const Iterator& it) const
			{
				return node_ == it.node_;
			}

			/**
			* @brief Checks if two iterators are not equal.
			*
			* @param it The iterator to compare with.
			*
			* @return true if the iterators are not equal, false otherwise.
			*/

			bool operator !=(const Iterator& it) const
			{
				return node_ != it.node_;
			}
		};

	};
}

#endif