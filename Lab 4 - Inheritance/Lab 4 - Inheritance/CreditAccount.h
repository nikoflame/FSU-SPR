#pragma once
#include "BaseAccount.h"
class CreditAccount :
    public BaseAccount
{
private:
    int mAmountSpent = 0; //amount spend so far
    const int mSpendingLimit = 40; //hard limit on spending

public:
    void Withdraw(float amount);
    bool isWithdrawalLimitReached(); //checks if overspending fee needs to be added to account
};

