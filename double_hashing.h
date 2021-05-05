//Mena Bebawy
//Double hashing implementation

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace
{
	/*
	Purpose: Finds the prime number that is before a given unsigned integer
	In: table size
	Out: the biggest prime number smaller than the table size
	*/
	int PreviousPrime(size_t n)
	{
		n--;			//We move back one integer
		if (n % 2 == 0) //IF it is divisible by 2, it is not prime, so we move back another integer
			--n;
		while (!IsPrime(n)) //We keep moving back by 2, traversing the odd numbers until the integer is, in fact, prime
			n -= 2;
		return n;
	}

} // namespace

// Double Hashing implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
	enum EntryType
	{
		ACTIVE,
		EMPTY,
		DELETED
	};

	explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
	{
		MakeEmpty();
		numberOfCollisions = 0;
		numberOfProbes = 0;
		R = PreviousPrime(array_.size()); //The R value is set to be the largest prime number that is smaller than the table size
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

	void SetR(int x) //Sets the r-value
	{
		if (x != 0) //If the given input is not empty
		{
			R = x; //Set r to the given integer value
		}
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

	size_t returnRValue() //Returns the r value
	{
		return R;
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
	mutable size_t R;

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
			current_pos = (current_pos + (offset * InternalHash2(x))) % array_.size(); // current_pos currenty has the value of Hash1(x). We compute (Hash1(x) + i * Hash2(x)) % table_size
			offset++;
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

	/*
	Purpose: Hash2(x) function for double hashing
	In: an object
	Out: the key result
	*/
	size_t InternalHash2(const HashedObj &x) const //This applies the same hash function as InternalHash. However, it takes in that value and follows the formula for hash2(x)
	{
		static std::hash<HashedObj> hf2;
		return R - (hf2(x) % R); // formula for hash2(x) R-(key % R) where R is a prime number smaller than the table size
	}
};

#endif // DOUBLE_HASHING_H
