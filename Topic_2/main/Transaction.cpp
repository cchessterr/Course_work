#include "Transaction.h"

const string &Transaction::getCategory() const
{
   return category;
}

double Transaction::getAmount() const
{
	return amount;
}

const time_t &Transaction::getTimestamp() const
{
	return timestamp;
}
