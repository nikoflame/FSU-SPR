#include "CheckingAccount.h"

void CheckingAccount::Withdraw(float amount)
{
	if (amount > 0.0f)
	{
		if (mWithdrawals >= 10)
			mAccountBalance -= 5.0f;
		mAccountBalance -= amount;
		mWithdrawals++;
	}
}

bool CheckingAccount::isWithdrawalLimitReached()
{
	if (mWithdrawals >= 10)
		return true;
	else
		return false;
}
