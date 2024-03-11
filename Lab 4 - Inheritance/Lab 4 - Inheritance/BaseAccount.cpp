#include "BaseAccount.h"

void BaseAccount::Withdraw(float amount)
{
	if (amount > 0.0f)
	{
		mAccountBalance -= amount;
		mWithdrawals++;
	}
}

float BaseAccount::GetBalance() const
{
	return mAccountBalance;
}

void BaseAccount::Deposit(float amount)
{
	if (amount > 0.0f)
	{
		mAccountBalance += amount;
	}
}

bool BaseAccount::isWithdrawalLimitReached()
{
	return false;
}

void BaseAccount::SetBalance(float newBalance)
{
	mAccountBalance = newBalance;
}
