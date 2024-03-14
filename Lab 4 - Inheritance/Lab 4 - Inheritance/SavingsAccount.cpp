#include "SavingsAccount.h"

void SavingsAccount::Withdraw(float amount)
{
	if (this->isWithdrawalLimitReached())
		BaseAccount::Withdraw(amount);
}

bool SavingsAccount::isWithdrawalLimitReached()
{
	if (mWithdrawals < 3) //if equal to 3, this is withdrawal number 4
		return true;
	else
		return false;
}
