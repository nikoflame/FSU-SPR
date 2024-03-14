#include "CreditAccount.h"

void CreditAccount::Withdraw(float amount)
{
	//check if withdrawal is legal. cannot withdraw nothing.
	if (amount > 0.0f)
	{
		mAccountBalance -= amount;
		mAmountSpent += amount; //track spending for isWithdrawalLimitReached()
		mWithdrawals++;
		//this is added at the end, since we want to check if the user overspends in the same transaction
		if (this->isWithdrawalLimitReached())
			mAccountBalance -= 5000.0f; //overspending fee
	}
}

bool CreditAccount::isWithdrawalLimitReached()
{
	if (mAmountSpent > mSpendingLimit)
		return true;
	else
		return false;
}
