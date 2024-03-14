#include "BaseAccount.h"

void BaseAccount::Withdraw(float amount)
{
	//check if withdrawal is legal. cannot withdraw nothing.
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
	//check if deposit is legal. cannot deposit nothing.
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
