#pragma once
#include <iostream>
#include <time.h>
#include <string>
#include <bitset>

namespace Helper
{
	//clears the std::cin buffer
	inline void clrcin()
	{
		std::cin.clear();
		std::cin.ignore();
	}

	//sends a message to the user and asks for input, then validates that input to be legal and within range if needed
	inline int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0)
	{
		int userInput;

		//loop until break
		do
		{
			//message
			std::cout << strMessage;

			//retrieve input
			std::cin >> userInput;

			//int validation failed
			while (std::cin.fail())
			{
				clrcin();
				std::cout << "\nInvalid input. Please try again: ";
				std::cin >> userInput;
			}

			//check range
			if ((nMinimumRange != 0 || nMaximumRange != 0) && (userInput < nMinimumRange || userInput > nMaximumRange))
			{
				//range check bad
				std::cout << "You entered a number out of the allowed range. ";
				if (nMinimumRange != 0)
					std::cout << "The minimum range is " << nMinimumRange << ". ";
				if (nMaximumRange != 0)
					std::cout << "The maximum range is " << nMaximumRange << ". ";
				std::cout << "Please try again." << std::endl;
				clrcin();
			}
			else
			{
				//range check good
				clrcin();
				break;
			}
		} while (true);

		return userInput;
	}

	//same as above, but for float instead of int
	inline float GetValidatedFloat(const char* strMessage, float fMinimumRange = 0.0f, float fMaximumRange = 0.0f) {
		float userInput;

		//loop until break
		do {
			//message
			std::cout << strMessage;

			//retrieve input
			std::cin >> userInput;

			//float validation failed
			while (std::cin.fail())
			{
				clrcin();
				std::cout << "\nInvalid input. Please try again: ";
				std::cin >> userInput;
			}

			//check range
			if ((fMinimumRange != 0.0f && userInput < fMinimumRange) || (fMaximumRange != 0.0f && userInput > fMaximumRange))
			{
				//range check bad
				std::cout << "You entered a number out of the allowed range. ";
				if (fMinimumRange != 0.0f)
					std::cout << "The minimum range is " << fMinimumRange << ". ";
				if (fMaximumRange != 0.0f)
					std::cout << "The maximum range is " << fMaximumRange << ". ";
				std::cout << "Please try again." << std::endl;
				clrcin();
			}
			else
			{
				//range check good
				clrcin();
				break;
			}
		} while (true);

		return userInput;
	}

	//returns a random integer between min and max values
	inline int RandomInt(int min, int max)
	{
		srand(time(NULL));
		return rand() % (max - min + 1) + min;
	}

	//outputs an array of strings into a numbered menu, with a title, then asks the user to choose one and validates their response
	inline int MenuAndChoice(const char* menuTitle, const std::string menu[], int menuSize)
	{
		//print menu
		std::cout << menuTitle << std::endl;
		for (int i = 0; i < menuSize; i++) {
			std::cout << i + 1 << ". " << menu[i] << std::endl;
		}

		// Get user's selection
		int choice = GetValidatedInt("Choose One: ", 1, menuSize);

		return choice;
	}

	//converts an integer to binary, hex, or oct using std::cout to the console
	inline void PrintBinHexOct(int intToChange, bool binary, bool hex, bool oct)
	{
		if (binary && !hex && !oct)
		{
			std::cout << std::bitset<sizeof(int) * 8>(intToChange);
		}
		else if (!binary && hex && !oct)
		{
			std::cout << std::hex << intToChange << std::dec;
		}
		else if (!binary && !hex && oct)
		{
			std::cout << std::oct << intToChange << std::dec;
		}
		else
		{
			std::cout << intToChange;
		}
	}

	//takes an array of characters and copies it to another array of characters
	inline void CopyString(const char* source, char*& destination)
	{
		delete[] destination;

		if (source != nullptr)
		{
			size_t len = strlen(source) + 1;
			destination = new char[len];
			strcpy_s(destination, len, source);
		}
		else
		{
			destination = nullptr;
		}
	}
}