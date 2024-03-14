#pragma once
class BaseAccount
{
protected:
	float mAccountBalance; //account balance float
	int mWithdrawals; //number of withdrawals made from the account

public:
	BaseAccount() { mAccountBalance = 0; mWithdrawals = 0; } //default constructor

	float GetBalance() const; //getter for balance
	void SetBalance(float newBalance); //setter for balance

	virtual void Withdraw(float amount); //lowers mAccountBalance by 'amount' and increases mWithdrawals by one
	virtual void Deposit(float amount); //increases mAccountBalance by 'amount'
	virtual bool isWithdrawalLimitReached(); //does nothing. meant for derived accounts only.
};

