#pragma once
class BaseAccount
{
protected:
	float mAccountBalance;
	int mWithdrawals;

public:
	BaseAccount() { mAccountBalance = 0; mWithdrawals = 0; }

	float GetBalance() const;
	void SetBalance(float newBalance);

	virtual void Withdraw(float amount);
	virtual void Deposit(float amount);
	virtual bool isWithdrawalLimitReached();
};

