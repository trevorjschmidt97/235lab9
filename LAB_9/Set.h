//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef SET_H
#define SET_H
#include <string>
#include "SetInterface.h"
#include "BST.h"
using namespace std;

template<typename T>
class Set : public SetInterface<T>
{
private:
	BST<T> tree;
public:
	Set() 
	{
	}
	virtual ~Set() 
	{
		//tree.clearTree();
	}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item)
	{
		return tree.addNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear()
	{
		tree.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size()
	{
		return tree.getSize();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item)
	{
		return tree.findNode(item);
		//return 0;
	}

	/** @return: string representation of items in Set. */
	std::string toString()
	{
		return tree.toString();
		}
};
#endif // SET_H