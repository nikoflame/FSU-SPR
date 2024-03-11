#include "CreditAccount.h"

void CreditAccount::Withdraw(float amount)
{
	if (amount > 0.0f)
	{
		mAccountBalance -= amount;
		mAmountSpent += amount;
		mWithdrawals++;
		if (mAmountSpent > 40)
			mAccountBalance -= 5000.0f;
	}
}

bool CreditAccount::isWithdrawalLimitReached()
{
	if (mAmountSpent > 40)
		return true;
	else
		return false;
}
