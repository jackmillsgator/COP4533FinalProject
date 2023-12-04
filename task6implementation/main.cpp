
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findMaxProfit(vector<vector<int>> predictedPrices, int c);
void printMaxProfitValues(vector<int> maxProfitValues, string vectorName);

int main()
{

    //  I am declaring and initializing the 2D vectors to test the implementation
    //  of the algorithm.

    //////////////////////////////////////////////////////////////
    //                                                          //
    //  MAX                                                     //
    //  PROFIT:     13                                          //
    //                                                          //
    //////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices1
    {

        {7, 1, 5, 3, 6, 8, 9},
        {2, 4, 3, 7, 9, 1, 8},
        {5, 9, 9, 4, 2, 3, 7},
        {9, 3, 4, 8, 7, 4, 1},
        {3, 5, 5, 3, 1, 6, 10}

    };
    int c1 = 2;

    //////////////////////////////////////////////////////////////
    //                                                          //
    //  MAX                                                     //
    //  PROFIT:     16                                          //
    //                                                          //
    //////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices2
    {

        {2, 9, 8, 4, 5, 0, 7},
        {6, 7, 3, 9, 1, 0, 8},
        {1, 7, 9, 6, 4, 9, 11},
        {7, 8, 3, 1, 8, 5, 2},
        {1, 8, 4, 0, 9, 2, 1}

    };
    int c2 = 2;

    //////////////////////////////////////////////////////////////
    //                                                          //
    //  MAX                                                     //
    //  PROFIT:     0                                           //
    //                                                          //
    //////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices3
    {

        {12, 8, 5, 3, 1},
        {20, 16, 14, 8, 7},
        {5, 4, 3, 2, 1},
        {0, 0, 0, 0, 0}

    };
    int c3 = 2;

    //  I'm calling the findMaxProfit() function, which is the implementation
    //  of the algorithm, and the printMaxProfitValues() function that will
    //  confirm that the correct values are returned.
    vector<int> maxProfitValues1 = findMaxProfit(predictedPrices1, c1);
    printMaxProfitValues(maxProfitValues1, "predictedPrices1");

    vector<int> maxProfitValues2 = findMaxProfit(predictedPrices2, c2);
    printMaxProfitValues(maxProfitValues2, "predictedPrices2");

    vector<int> maxProfitValues3 = findMaxProfit(predictedPrices3, c3);
    printMaxProfitValues(maxProfitValues3, "predictedPrices3");

    return 0;

}

//  Implementation of the algorithm.
vector<int> findMaxProfit(vector<vector<int>> predictedPrices, int c)
{

    //  I'm declaring and intializing all necessary variables.
    long unsigned int i = 0;
    long unsigned int j = 0;
    long unsigned int k = 0;
    long unsigned int m = 0;

    int maxProfit = 0;
    int tempInt = 0;

    int lowestPrice = 0;
    int lowestPriceIndex = 0;

    //  I'm creating a vector of size 4 filled with 0 as all of its values.
    //  If a max profit from a transaction is, indeed, found, then the 0's
    //  will change to other values.
    vector<vector<int>> maxProfitEachStockDay(predictedPrices.size(), vector<int>(predictedPrices[0].size(), 0));

    vector<vector<int>> buyDays(predictedPrices.size(), vector<int>(predictedPrices[0].size(), 0));

    vector<int> maxProfitValues;

    //  **************************************************************************************************  //
    //                                                                                                      //
    //  Because our time complexity contains n^2, we would expect that our algorithm would contain a        //
    //  nested for loop. Therefore, we’re going to iterate through all elements of the 2d array containing  //
    //  the stock prices by using a nested for loop, and because we’re utilizing dynamic programming,       //
    //  we’re going to use recursion to return the maximum profit selling a stock for each day by           //
    //  subtracting previous stock prices from the current stock price, comparing the current value of      //
    //  maxProfit with the profit value returned from each recursion call, returning the larger of the two  //
    //  values each time, and ultimately returning the max profit possible for selling each stock on a      //
    //  particular day.                                                                                     //
    //                                                                                                      //
    //  **************************************************************************************************  //

    //  Iterating through each stock
    for (i = 0; i < predictedPrices.size(); i++)
    {

        maxProfit = 0;
    
        //  Iterating through the prices for each stock
        for (j = 0; j < predictedPrices[i].size(); j++)
        {

            lowestPrice = predictedPrices[i][0];
            lowestPriceIndex = 0;

            //  I'm going through each previous price before the current
            //  stock price (price at index j) and subtracting each
            //  previous stock from the current stock. If the sum of
            //  that operation is larger than the current value of
            //  maxProfit, then the sum becomes the new value of
            //  maxProfit.
            for (k = 0; k < j; k++)
            {

                // I'm updating the lowest stock price found so far
                //lowestPrice = min(lowestPrice, predictedPrices[i][j]);
                if (predictedPrices[i][k] < lowestPrice)
                {
                    lowestPrice = predictedPrices[i][k];
                    lowestPriceIndex = k;
                }

                //tempInt = predictedPrices[i][j] - predictedPrices[i][k];
                tempInt = predictedPrices[i][j] - lowestPrice;

                //  If a new, larger value for maxProfit is found, we
                //  want to store and keep track of the new value for
                //  value for maxProfit as well as other information
                //  regarding that transaction for when we print the
                //  desired tuple of informational values.
                if (tempInt > maxProfit)
                {
                    maxProfit = tempInt;
                }

            }

            maxProfitEachStockDay[i][j] = maxProfit;
            buyDays[i][j] = lowestPriceIndex;

        }

    }

    int maxProfitOverall = 0;

    int stock1 = 0;
    int buyDay1 = 0;
    int sellDay1 = 0;

    int stock2 = 0;
    int buyDay2 = 0;
    int sellDay2 = 0;

    //  Iterating through each stock
    for (i = 0; i < maxProfitEachStockDay.size(); i++)
    {

        //  Iterating through each day for each stock
        for (j = 0; j < maxProfitEachStockDay[i].size(); j++)
        {

            //  Now I'm going to only iterate through each stock that can validly make a second
            //  transaction when considering the constraint c
            for (m = 0; m < maxProfitEachStockDay.size(); m++)
            {

                //  Now I'm going to only iterate through each day for each stock that can validly make a
                //  second transaction when considering the constraint c
                for (k = j + 1 + 1 + c + 1; k < maxProfitEachStockDay[i].size(); k++)
                {

                    //  If the sum of the two transaction can produce a larger value than the current
                    //  value of maxProfitOverall, then we replace maxProfitValue with the new sum.
                    if ( ((maxProfitEachStockDay[i][j] + maxProfitEachStockDay[m][k]) > maxProfitOverall)
                            && ( (buyDays[m][k] - (int)j) >= (c - 2) ) )
                    {

                        maxProfitOverall = maxProfitEachStockDay[i][j] + maxProfitEachStockDay[m][k];

                        stock1 = i;
                        buyDay1 = buyDays[i][j];
                        sellDay1 = j;

                        stock2 = m;
                        buyDay2 = buyDays[m][k];
                        sellDay2 = k;

                    }

                }

            }

        }

    }

    //  If we, indeed, found a max profit of some kind, then we want
    //  to add 1 to the values representing the stock row, buy day,
    //  and sell day. The reason is because the format given in the
    //  Final Project instructions gives examples where tuples
    //  contain values of the actual row and column number as opposed
    //  to programming index values (values that start with 0 i.e.
    //  0, 1, 2, 3, ...).
    if (maxProfitOverall > 0)
    {

        maxProfitValues.push_back(maxProfitOverall);

        maxProfitValues.push_back(stock1 + 1);
        maxProfitValues.push_back(buyDay1 + 1);
        maxProfitValues.push_back(sellDay1 + 1);

        maxProfitValues.push_back(stock2 + 1);
        maxProfitValues.push_back(buyDay2 + 1);
        maxProfitValues.push_back(sellDay2 + 1);

    }
    //  If maxProfit is 0, then no transaction was found that would
    //  lead to a profit. So we want to return the tuple (0, 0, 0, 0).
    else if (maxProfitOverall <= 0)
    {

        maxProfitValues.push_back(0);
        maxProfitValues.push_back(0);
        maxProfitValues.push_back(0);
        maxProfitValues.push_back(0);

    }

    return maxProfitValues;

}

//  Simply prints values to correct that findMaxProfit() is working
void printMaxProfitValues(vector<int> maxProfitValues, string vectorName)
{

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "\t" << vectorName << endl;
    cout << "---------------------------------" << endl;

    cout << endl;
    cout << "Tuple Output: " << endl;
    cout << endl;

    for (long unsigned int i = 0; i < maxProfitValues.size(); i++)
    {

        if (i == 0)
        {
            cout << "maxProfitOverall: " << maxProfitValues[i] << endl;
        }
        else if ( ((i - 1) % 3) == 0)
        {
            cout << "(" << maxProfitValues[i]   << ", ";
        }
        else if ( (i % 3) == 0 && i != 1 && (i + 1) != maxProfitValues.size())
        {
            cout << maxProfitValues[i] << "), " << endl;
        }
        else if ( (i % 3) == 0 && i != 1)
        {
            cout << maxProfitValues[i] << ")" << endl;
        }
        else
        {
            cout << maxProfitValues[i]   << ", ";
        }
    }
    cout << endl;
    cout << endl;

}
