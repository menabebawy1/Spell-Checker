//Mena Bebawy
//linear probing implementation

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename HashedObj>
class HashTableLinear
{
public:
	enum EntryType
	{
		ACTIVE,
		EMPTY,
		DELETED
	};

	explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size))
	{
		MakeEmpty();
		numberOfCollisions = 0;
		numberOfProbes = 0;
	}

	bool Contains(const HashedObj &x) const
	{
		numberOfProbes = 0;
		return IsActive(FindPos(x));
	}

	void MakeEmpty()
	{
		current_size_ = 0;
		for (auto &entry : array_)
			entry.info_ = EMPTY;
	}

	bool Insert(const HashedObj &x)
	{
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos].element_ = x;
		array_[current_pos].info_ = ACTIVE;

		if (++current_size_ > array_.size() / 2)
			Rehash();
		return true;
	}

	bool Insert(HashedObj &&x)
	{
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos] = std::move(x);
		array_[current_pos].info_ = ACTIVE;

		if (++current_size_ > array_.size() / 2)
			Rehash();

		return true;
	}

	bool Remove(const HashedObj &x)
	{
		size_t current_pos = FindPos(x);
		if (!IsActive(current_pos))
			return false;

		array_[current_pos].info_ = DELETED;
		return true;
	}

	size_t returnCurrentSize() //Returns the number of elements in the table
	{
		return current_size_;
	}

	size_t returnArraySize() //Returns the size of the array
	{
		return array_.size();
	}

	size_t returnNumberOfCollisions() //Returns the number of collisions that occured in the table
	{
		return numberOfCollisions;
	}

	size_t returnNumberOfProbes() //Returns the number of probes for each word that is found/ not found
	{
		return numberOfProbes;
	}

private:
	struct HashEntry
	{
		HashedObj element_;
		EntryType info_;

		HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
			: element_{e}, info_{i} {}

		HashEntry(HashedObj &&e, EntryType i = EMPTY)
			: element_{std::move(e)}, info_{i} {}
	};

	std::vector<HashEntry> array_;
	size_t current_size_;
	mutable size_t numberOfCollisions;
	mutable size_t numberOfProbes;

	bool IsActive(size_t current_pos) const
	{
		return array_[current_pos].info_ == ACTIVE;
	}

	size_t FindPos(const HashedObj &x) const
	{
		size_t offset = 1;
		size_t current_pos = InternalHash(x);

		while (array_[current_pos].info_ != EMPTY &&
			   array_[current_pos].element_ != x)
		{
			numberOfCollisions++;
			numberOfProbes++;
			current_pos += offset; // We offset by 1 everytime
			if (current_pos >= array_.size())
				current_pos -= array_.size();
		}
		return current_pos;
	}

	void Rehash()
	{
		std::vector<HashEntry> old_array = array_;

		// Create new double-sized, empty table.
		array_.resize(NextPrime(2 * old_array.size()));
		for (auto &entry : array_)
			entry.info_ = EMPTY;

		// Copy table over.
		current_size_ = 0;
		for (auto &entry : old_array)
			if (entry.info_ == ACTIVE)
			{
				Insert(std::move(entry.element_));
			}
	}

	size_t InternalHash(const HashedObj &x) const
	{
		static std::hash<HashedObj> hf;
		return hf(x) % array_.size();
	}
};

#endif // LINEAR_PROBING_H
