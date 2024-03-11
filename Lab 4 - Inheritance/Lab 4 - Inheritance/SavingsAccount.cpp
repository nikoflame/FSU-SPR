#include "SavingsAccount.h"

void SavingsAccount::Withdraw(float amount)
{
	if (mWithdrawals < 3)
		BaseAccount::Withdraw(amount);
}

bool SavingsAccount::isWithdrawalLimitReached()
{
	if (mWithdrawals < 3)
		return true;
	else
		return false;
}
