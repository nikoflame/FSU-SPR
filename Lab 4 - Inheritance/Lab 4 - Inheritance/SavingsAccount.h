#pragma once
#include "BaseAccount.h"
class SavingsAccount :
    public BaseAccount
{
public:
    void Withdraw(float amount);

    bool isWithdrawalLimitReached(); //checks if limit of 3 withdrawals per day has been reached
};

