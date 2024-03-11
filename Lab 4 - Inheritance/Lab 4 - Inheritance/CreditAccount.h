#pragma once
#include "BaseAccount.h"
class CreditAccount :
    public BaseAccount
{
private:
    int mAmountSpent = 0;
    const int mSpendingLimit = 40;

public:
    void Withdraw(float amount);
    bool isWithdrawalLimitReached();
};

