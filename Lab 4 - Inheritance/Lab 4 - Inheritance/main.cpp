#include <iostream>
#include <fstream>
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

    //LAB 5 - Binary File I/O ----- START
 
    //open file
    std::fstream fin;
    fin.open("Balances.bin", std::ios_base::in | std::ios_base::binary);

    //check if file exists
    if (fin.is_open())
    {
        //calculate size
        fin.seekg(0, std::ios_base::end);
        int fSize = fin.tellg();
        fin.seekg(0, std::ios_base::beg);

        //create variables
        float checkingBal, savingsBal, creditBal;

        //read file
        fin.read((char*)&checkingBal, sizeof(float));
        fin.read((char*)&savingsBal, sizeof(float));
        fin.read((char*)&creditBal, sizeof(float));

        //set balances
        myChecking->SetBalance(checkingBal);
        mySavings->SetBalance(savingsBal);
        myCredit->SetBalance(creditBal);

        //close file
        fin.close();
    }
    else
    {
        //set balances to default
        myChecking->SetBalance(1000.0f);
        mySavings->SetBalance(10000.0f);
        myCredit->SetBalance(0.0f);
    }
    //LAB 5 - Binary File I/O ----- END
    
    //menu initializations
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

    //choose your account for credit repayment
    const std::string creditMenu[2] =
    {
        "Checking Account ($5 fee if more than 10 withdrawals are made)",
        "Savings Account (no more than 3 withdrawals permitted)"
    };

    //just a yes or no menu for various choices to be made
    const std::string ynMenu[2] =
    {
        "Yes",
        "No"
    };

    //initialize variables
    int menuChoice = 0;
    int creditMenuChoice = 0;
    int ynMenuChoice = 0;
    float amount = 0.0f;
    int maxAmount;

    //program starts here
    do
    {
        //refresh screen afer returning here
        system("cls");

        //print balances
        PrintBalances(myChecking, mySavings, myCredit);

        //print menu
        menuChoice = Helper::MenuAndChoice("Please select one of the following options: ", menu, 7);

        //after user makes their choice, clear screen again for case menu
        system("cls");

        //print balances again so they stay at the top of the screen for reference
        PrintBalances(myChecking, mySavings, myCredit);

        switch (menuChoice)
        {
        case 1: //DEPOSIT TO CHECKING ACCOUNT

            //ask user for amount
            amount = Helper::GetValidatedFloat("How much would you like to deposit to your checking account? $", 0.01f);

            //deposit amount
            DepositPtr(myChecking, amount);

            //print confirmation
            std::cout << "$" << amount << " deposited to your checking account!" << std::endl;
            break;
        case 2: //DEPOSIT TO SAVINGS ACCOUNT

            //ask user for amount
            amount = Helper::GetValidatedFloat("How much would you like to deposit to your savings account? $", 0.01f);

            //deposit amount
            DepositPtr(mySavings, amount);

            //print confirmation
            std::cout << "$" << amount << " deposited to your savings account!" << std::endl;
            break;
        case 3: //MAKE CREDIT PAYMENT

            //ask user which account they want to use
            creditMenuChoice = Helper::MenuAndChoice("Which account would you like to pay your balance from? ", creditMenu, 2);

            //get maximum amount they can take, user cannot take more than their balance
            maxAmount = creditMenuChoice == 1 ? myChecking->GetBalance() : mySavings->GetBalance();

            //ask user for amount
            amount = Helper::GetValidatedFloat("How much would you like to pay towards your credit account? $", 0.01f, maxAmount);

            //credit menu
            switch (creditMenuChoice)
            {
            case 1: //MAKE PAYMENT FROM CHECKING ACCOUNT

                //check if withdrawal fee needs to be assessed
                if (myChecking->isWithdrawalLimitReached())

                    //ask user if fee is okay
                    ynMenuChoice = Helper::MenuAndChoice("At least 10 withdrawals from this account have been made today. Proceeding with this transaction will incur a $5 fee to your Checking Account. Do you accept? ", ynMenu, 2);
                if (ynMenuChoice == 2)
                    //cancel transaction if not okay
                    break;
                else
                {
                    //pay amount from checking to credit
                    WithdrawPtr(myChecking, amount);
                    DepositPtr(myCredit, amount);

                    //print confirmation
                    std::cout << "Thank you for your payment of $" << amount << " to your credit account!";
                    if (ynMenuChoice == 1) //alert user of charged fee for good measure
                        std::cout << " Your Checking Account has been charged $5." << std::endl;
                    break;
                }
            case 2: //MAKE PAYMENT FROM SAVINGS ACCOUNT

                //check if withdrawal limit has been reached
                if (mySavings->isWithdrawalLimitReached())

                    //cancel transaction and notify user if limit reached
                    std::cout << "You have reached your withdrawal limit for this account. Please choose a different account." << std::endl;
                else
                {
                    //pay amount from savings to credit
                    WithdrawPtr(mySavings, amount);
                    DepositPtr(myCredit, amount);

                    //print confirmation
                    std::cout << "Thank you for your payment of $" << amount << " to your credit account!" << std::endl;
                }
                break;
            }
            break;
        case 4: //WITHDRAW FROM CHECKING ACCOUNT

            //ask user for amount
            amount = Helper::GetValidatedFloat("How much would you like to withdraw? $", 0.01f, myChecking->GetBalance());

            //check if withdrawal fee needs to be assessed
            if (myChecking->isWithdrawalLimitReached())

                //ask user if fee is okay
                ynMenuChoice = Helper::MenuAndChoice("At least 10 withdrawals from this account have been made today. Proceeding with this transaction will incur a $5 fee to your Checking Account. Do you accept? ", ynMenu, 2);
            if (ynMenuChoice == 2)
                //cancel transaction if not okay
                break;
            else
            {
                //withdraw amount
                WithdrawPtr(myChecking, amount);

                //print confirmation
                std::cout << "$" << amount << " successfully withdrawn.";
                if (ynMenuChoice == 1) //alert user of charged fee for good measure
                    std::cout << " Your Checking Account has been charged $5.";
                std::cout << " Have a good day!" << std::endl;
                break;
            }
        case 5: //WITHDRAW FROM SAVINGS ACCOUNT

            //ask user for amount
            amount = Helper::GetValidatedFloat("How much would you like to withdraw? $", 0.01f, mySavings->GetBalance());

            //check if withdrawal limit has been reached
            if (mySavings->isWithdrawalLimitReached())

                //cancel transaction and notify user if limit reached
                std::cout << "You have reached your withdrawal limit for this account. Transaction canceled." << std::endl;
            else
            {
                //withdraw amount
                WithdrawPtr(mySavings, amount);

                //print confirmation
                std::cout << "$" << amount << " successfully withdrawn. Have a good day!" << std::endl;
            }
            break;
        case 6: //CREDIT CASH ADVANCE

            //ask user for amount, remind user of unneccessarily massive overspending fee
            amount = Helper::GetValidatedFloat("WARNING: There is a $40 spending limit for this account. If you go over that amount, there is a $5000 fee automatically charged. \nHow much would you like to withdraw? $", 0.01f);

            //withdraw amount
            WithdrawPtr(myCredit, amount);

            //print confirmation
            std::cout << "$" << amount << " successfully withdrawn.";
            if (myCredit->isWithdrawalLimitReached()) //do evil things to the user
                std::cout << " You have incurred a fee of $5000 to your credit account.";
            //try to help the user to forget about the fact that they have to sell their car, all because they wanted those extra fries.
            std::cout << " Have a good day!" << std::endl;
            break;
        case 7:
        default:
            break; //exit code
        }

        //let the user see the confirmation messages before going back to the main menu
        system("pause");

    } while (menuChoice != 7); //loop unless user chooses to exit

    //LAB 5 - Binary File I/O ----- START

    //open file
    std::fstream fout;
    fout.open("Balances.bin", std::ios_base::out | std::ios_base::binary);

    //write to file using binary
    if (fout.is_open())
    {
        //create variables
        float checkingBal = myChecking->GetBalance();
        float savingsBal = mySavings->GetBalance();
        float creditBal = myCredit->GetBalance();

        //write out each account balance
        fout.write((char*)&checkingBal, sizeof(float));
        fout.write((char*)&savingsBal, sizeof(float));
        fout.write((char*)&creditBal, sizeof(float));

        //close file
        fout.close();
    }

     //LAB 5 - Binary File I/O ----- END

    //clean up memory here
    delete myChecking;
    delete mySavings;
    delete myCredit;

    return 0;
}