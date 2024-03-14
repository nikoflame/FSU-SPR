#pragma once
#include "BaseAccount.h"
class CheckingAccount :
    public BaseAccount
{
public:
    void Withdraw(float amount);

    bool isWithdrawalLimitReached(); //checks if user is at 10 withdrawals in order to charge a fee for more
};

