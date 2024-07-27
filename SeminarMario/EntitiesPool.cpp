#include "EntitiesPool.h"

EntitiesPool::EntitiesPool(std::vector<EntityPtr> _pool, std::vector<bool> _isInUse):_pool(_pool), _isInUse(_isInUse)
{
}

void EntitiesPool::insert(EntityPtr whom)
{
	_pool.push_back(whom);
	_isInUse.push_back(false);
}

EntityPtr EntitiesPool::getNext()
{
	int ind = 0;
	for (auto i : _isInUse)
	{
		if (i == true)
		{
			return _pool.at(ind);
			break;
		}
		ind++;
	}
	return EntityPtr();
}

void EntitiesPool::returnEntity(EntityPtr toFree)
{
	int ind = 0;
	for (auto i : _pool)
	{
		if (i == toFree)
		{
			_isInUse.at(ind) == false;
		}
		ind++;
	}

}
