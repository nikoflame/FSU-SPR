#include <iostream>
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Helper.h"

//---------- Memory Leak Detection Code ----------//
// Need this block for memory leak detection
#if defined _MSC_VER && defined _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_LEAK_DETECTION()
#endif
//---------- Memory Leak Detection Code ----------//

void WithdrawPtr(BaseAccount* basePtr, float amount)
{
    basePtr->Withdraw(amount);
}

void DepositPtr(BaseAccount* basePtr, float amount)
{
    basePtr->Deposit(amount);
}

void PrintBalances(BaseAccount* checkingPtr, BaseAccount* savingsPtr, BaseAccount* creditPtr)
{
    std::cout << "Here are your current balances: " << std::endl;
    std::cout << "Checking Account: $" << checkingPtr->GetBalance() << std::endl;
    std::cout << "Savings Account: $" << savingsPtr->GetBalance() << std::endl;
    std::cout << "Credit Account: $" << creditPtr->GetBalance() << std::endl;
    std::cout << std::endl;
}

int main()
{
    //---------- Memory Leak Detection Code ----------//
    // Put this block at the top of main in order to turn on memory leak detection
    ENABLE_LEAK_DETECTION(); //will do nothing if NOT a debug build

    // Important! Start this parameter off at -1, but change it to the allocation number to track down any leaks!
    _CrtSetBreakAlloc(-1);
    //---------- Memory Leak Detection Code ----------//

    //initialize
    BaseAccount* myChecking = new CheckingAccount();
    BaseAccount* mySavings = new SavingsAccount();
    BaseAccount* myCredit = new CreditAccount();

    //set balances
    myChecking->SetBalance(1000.0f);
    mySavings->SetBalance(10000.0f);
    myCredit->SetBalance(0.0f);

    //menus
    const std::string menu[7] =
    {
        "Deposit to Checking Account",
        "Deposit to Savings Account",
        "Deposit to Credit Account (make payment)",
        "Withdraw from Checking Account ($5 fee if more than 10 withdrawals are made)",
        "Withdraw from Savings Account (no more than 3 withdrawals permitted)",
        "Withdraw from Credit Account (cash advance) ($40 spending limit, $5000 fee if you go over that spending limit)",
        "Exit"
    };

    const std::string creditMenu[2] =
    {
        "Checking Account ($5 fee if more than 10 withdrawals are made)",
        "Savings Account (no more than 3 withdrawals permitted)"
    };

    const std::string ynMenu[2] =
    {
        "Yes",
        "No"
    };

    int menuChoice = 0;
    int creditMenuChoice = 0;
    int ynMenuChoice = 0;
    float amount = 0.0f;
    int maxAmount;

    do
    {
        system("cls");
        PrintBalances(myChecking, mySavings, myCredit);
        menuChoice = Helper::MenuAndChoice("Please select one of the following options: ", menu, 7);
        system("cls");
        PrintBalances(myChecking, mySavings, myCredit);

        switch (menuChoice)
        {
        case 1:
            amount = Helper::GetValidatedFloat("How much would you like to deposit to your checking account? $", 0.01f);
            DepositPtr(myChecking, amount);
            std::cout << "$" << amount << " deposited to your checking account!" << std::endl;
            break;
        case 2:
            amount = Helper::GetValidatedFloat("How much would you like to deposit to your savings account? $", 0.01f);
            DepositPtr(mySavings, amount);
            std::cout << "$" << amount << " deposited to your savings account!" << std::endl;
            break;
        case 3:
            creditMenuChoice = Helper::MenuAndChoice("Which account would you like to pay your balance from? ", creditMenu, 2);
            maxAmount = creditMenuChoice == 1 ? myChecking->GetBalance() : mySavings->GetBalance();
            amount = Helper::GetValidatedFloat("How much would you like to pay towards your credit account? $", 0.01f, maxAmount);
            switch (creditMenuChoice)
            {
            case 1:
                if (myChecking->isWithdrawalLimitReached())
                    ynMenuChoice = Helper::MenuAndChoice("At least 10 withdrawals from this account have been made today. Proceeding with this transaction will incur a $5 fee to your Checking Account. Do you accept? ", ynMenu, 2);
                if (ynMenuChoice == 2)
                    break;
                else
                {
                    WithdrawPtr(myChecking, amount);
                    DepositPtr(myCredit, amount);
                    std::cout << "Thank you for your payment of $" << amount << " to your credit account!";
                    if (ynMenuChoice == 1)
                        std::cout << " Your Checking Account has been charged $5." << std::endl;
                    break;
                }
            case 2:
                if (mySavings->isWithdrawalLimitReached())
                    std::cout << "You have reached your withdrawal limit for this account. Please choose a different account." << std::endl;
                else
                {
                    WithdrawPtr(mySavings, amount);
                    DepositPtr(myCredit, amount);
                    std::cout << "Thank you for your payment of $" << amount << " to your credit account!" << std::endl;
                }
                break;
            }
            break;
        case 4:
            amount = Helper::GetValidatedFloat("How much would you like to withdraw? $", 0.01f, myChecking->GetBalance());
            if (myChecking->isWithdrawalLimitReached())
                ynMenuChoice = Helper::MenuAndChoice("At least 10 withdrawals from this account have been made today. Proceeding with this transaction will incur a $5 fee to your Checking Account. Do you accept? ", ynMenu, 2);
            if (ynMenuChoice == 2)
                break;
            else
            {
                WithdrawPtr(myChecking, amount);
                std::cout << "$" << amount << " successfully withdrawn.";
                if (ynMenuChoice == 1)
                    std::cout << " Your Checking Account has been charged $5.";
                std::cout << " Have a good day!" << std::endl;
                break;
            }
        case 5:
            amount = Helper::GetValidatedFloat("How much would you like to withdraw? $", 0.01f, mySavings->GetBalance());
            if (mySavings->isWithdrawalLimitReached())
                std::cout << "You have reached your withdrawal limit for this account. Transaction canceled." << std::endl;
            else
                std::cout << "$" << amount << " successfully withdrawn. Have a good day!" << std::endl;
            break;
        case 6:
            amount = Helper::GetValidatedFloat("WARNING: There is a $40 spending limit for this account. If you go over that amount, there is a $5000 fee automatically charged. \nHow much would you like to withdraw? $", 0.01f);
            WithdrawPtr(myCredit, amount);
            std::cout << "$" << amount << " successfully withdrawn.";
            if (myCredit->isWithdrawalLimitReached())
                std::cout << " You have incurred a fee of $5000 to your credit account.";
            std::cout << " Have a good day!" << std::endl;
            break;
        case 7:
        default:
            break;
        }

        system("pause");

    } while (menuChoice != 7);

    delete myChecking;
    delete mySavings;
    delete myCredit;

    return 0;
}