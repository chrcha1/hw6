#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = {0};
        int i = k.length() - 1;
				int count = 0;
        int exponent = 1;
        int wwwIndex = 4;

				size_t runningSum = 0;
        
        while (i >= 0)
        {
            if (count == 6)
            {
                w[wwwIndex--]=runningSum;
                exponent=1;
                count=0;
                runningSum=0;
            }
            runningSum += letterDigitToNumber(k[i])*exponent;
            exponent *= 36;
            count++;
						i--;
        }
        if (count != 0)
        {
            w[wwwIndex] = runningSum;
        }


        HASH_INDEX_T result = 0;
        for (int i=0; i<5; i++)
        {
						result += w[i]*rValues[i];
        }
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
		int num;
        if (!isalpha(letter))
        {
						num = (int)letter - 22; // '0' = 48 --> '0' = 26

        }
        else
        {
            num = tolower(letter) - 97; // 'a' = 97 --> 'a' = 0
        }
        return num;
    }


    // Code to generate the random R values
    void generateRValues()
    {
        // obtaining a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard randomnum generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif