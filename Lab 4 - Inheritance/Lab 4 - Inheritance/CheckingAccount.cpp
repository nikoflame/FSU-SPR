#include "CheckingAccount.h"

void CheckingAccount::Withdraw(float amount)
{
	//check if withdrawal is legal. cannot withdraw nothing.
	if (amount > 0.0f)
	{
		//check if fee needs to be added for more than 10 withdrawals
		if (this->isWithdrawalLimitReached())
			mAccountBalance -= 5.0f;
		mAccountBalance -= amount;
		mWithdrawals++;
	}
}

bool CheckingAccount::isWithdrawalLimitReached()
{
	if (mWithdrawals >= 10) //if equal to 10, then this withdrawal is number 11
		return true;
	else
		return false;
}
