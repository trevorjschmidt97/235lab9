//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <string>
#include <utility>
#include <math.h>
#include "HashMapInterface.h"

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

template <typename KEY, typename VALUE>
class HashMap : public HashMapInterface<KEY, VALUE>
{
private:
	size_t capacity;
	pair<KEY, VALUE>* myPairs;
	size_t num_items = 0;

	void reallocate()
	{
		size_t new_capacity = 2 * capacity;

		pair<KEY, VALUE>* new_myPairs = new pair<KEY, VALUE>[new_capacity];

		for (size_t i = 0; i < capacity; i++)
		{
			if (myPairs[i].first.length())
			{
				size_t hash = 0;
				for (size_t j = 0; j < myPairs[i].first.length(); ++j)
				{
					hash = hash + myPairs[i].first[j] * pow(3, myPairs[i].first.length() - (i + 1));
				}
				hash %= new_capacity;

				int k = 1;
				while (1)
				{
					if (new_myPairs[hash].first.length() == true)
					{
						if (new_myPairs[hash].first == myPairs[i].first) break;
						hash = (hash + k) % new_capacity;
						k += 2;
						continue;
					}
					
					break;
				}
				new_myPairs[hash].first = myPairs[i].first;
				new_myPairs[hash].second = myPairs[i].second;
			}
		}

		capacity = new_capacity;

		swap(myPairs, new_myPairs);

		delete[] new_myPairs;
	}
public:
	HashMap<KEY, VALUE>() : myPairs(new pair<KEY, VALUE>[DEFAULT_MAP_HASH_TABLE_SIZE]), capacity(DEFAULT_MAP_HASH_TABLE_SIZE) {}
	virtual ~HashMap() 
	{
		delete[] myPairs;

	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual VALUE& operator[](const KEY& key)
	{
		size_t hash = 0;
		for (size_t i = 0; i < key.length(); ++i)
		{
			hash = hash + key[i] * pow(3, key.length() - (i + 1));
		}
		hash %= capacity;

		int k = 1;
		while (1)
		{
			if (myPairs[hash].first.length())
			{
				if (myPairs[hash].first == key) break;
				hash = (hash + k) % capacity;
				k += 2;
				continue;
			}
			myPairs[hash].first = key;
			num_items++;
			break;
		}
		if (static_cast<double>(num_items) / capacity > .75)
		{
			reallocate();
		}
		return myPairs[hash].second;
	}

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const KEY& key)
	{
		return capacity;
	}

	/** Removes all items from the Map. */
	virtual void clear(void)
	{
		for (size_t i = 0; i < capacity; ++i)
		{
			myPairs[i].first = "";
		}
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size(void) const
	{
		return num_items;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size(void) const
	{
		return capacity;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString(void)
	{
		ostringstream os;
		for (size_t i = 0; i < capacity; ++i)
		{
			if (myPairs[i].first.length())
			{
				os << endl;
				os << "  [" << i << ":" << myPairs[i].first << "->";
				os << myPairs[i].second; 
				os << "]";
			}
		}

		return os.str();
	}
};

template<typename T>
ostream& operator<<(ostream& out, Set<T>& set)
{
	return out << set.toString();
}
#endif // HASH_MAP_H