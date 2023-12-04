

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findMaxProfit(vector<vector<int>> predictedPrices);
void printMaxProfitValues(vector<int> maxProfitValues, string vectorName);

int recursiveStockMaxProfit(vector<int> daysVector, int currentDay, int subtractedDay);

vector<int> maxProfitValues;

int main()
{

    //  I am declaring and initializing the 2D vectors to test the implementation
    //  of the algorithm.

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //                  STOCK       BUY DAY     SELL DAY    PROFIT      //
    //      ANSWER:     1,          2,          5,          15          //
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices1
    {

        {12, 1, 5, 3, 16},
        {4, 4, 13, 4, 9},
        {6, 8, 6, 1, 2},
        {14, 3, 4, 8, 10}

    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //              STOCK       BUY DAY     SELL DAY    PROFIT          //
    //  ANSWER:     4,          2,          3,          11              //
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices2
    {

        {7, 1, 5, 3, 6},
        {2, 4, 3, 7, 9},
        {5, 8, 9, 1, 2},
        {9, 3, 14, 8, 7}

    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //              STOCK       BUY DAY     SELL DAY    PROFIT          //
    //  ANSWER:     0,          0,          0,          0               //
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
    vector<vector<int>> predictedPrices3
    {

        {12, 8, 5, 3, 1},
        {20, 16, 14, 8, 7},
        {5, 4, 3, 2, 1},
        {0, 0, 0, 0, 0}

    };

    maxProfitValues.resize(4, 0);

    //  I'm calling the findMaxProfit() function, which is the implementation
    //  of the algorithm, and the printMaxProfitValues() function that will
    //  confirm that the correct values are returned.
    vector<int> maxProfitValues1 = findMaxProfit(predictedPrices1);
    printMaxProfitValues(maxProfitValues1, "predictedPrices1");

    vector<int> maxProfitValues2 = findMaxProfit(predictedPrices2);
    printMaxProfitValues(maxProfitValues2, "predictedPrices2");

    vector<int> maxProfitValues3 = findMaxProfit(predictedPrices3);
    printMaxProfitValues(maxProfitValues3, "predictedPrices3");

    return 0;

}

//  Implementation of the algorithm.
vector<int> findMaxProfit(vector<vector<int>> predictedPrices)
{

    //  I'm declaring and intializing all necessary variables.
    long unsigned int i = 0;
    long unsigned int j = 0;

    int maxProfitStock = 0;
    int maxProfitBuyDay = 0;
    int maxProfitSellDay = 0;
    int maxProfit = 0;

    int buyPrice = 0;
    int buyPriceIndex = 0;

    //  I'm creating a vector of size 4 filled with 0 as all of its values.
    //  If a max profit from a transaction is, indeed, found, then the 0's
    //  will change to other values.
    vector<vector<int>> maxProfitStockDay(predictedPrices.size(), vector<int>(predictedPrices[0].size(), 0));
    vector<int> maxProfitValues(4, 0);

    //  **************************************************************************************************  //
    //                                                                                                      //
    //  Because we’re solving the same problem as the problem in Task 2 (including a lack of n^2 time       //
    //  complexity) while using a dynamic algorithm instead, I would expect the resulting algorithm to      //
    //  be similar to Task 2’s algorithm but, however, contain memoization which is the storing of results  //
    //  to subproblems so that they are immediately available without the need for recalculation. This      //
    //  technique of memoization is often implemented in cases where similar calculations are               //
    //  repeatedly made like in the case of recursion. Because we are repeatedly doing similar              //
    //  calculations when trying to find the maximum price by subtracting previous stock prices from a      //
    //  later (future) stock price, we want to implement memoization here                                   //
    //                                                                                                      //
    //  **************************************************************************************************  //

    //  Iterating through each stock
    for (i = 0; i < predictedPrices.size(); i++)
    {

        buyPrice = predictedPrices[i][0];
        buyPriceIndex = 0;

        //  Iterating through the prices for each stock
        for (j = 0; j < predictedPrices[i].size(); j++)
        {
            // Update minimum stock price encountered so far
            buyPrice = min(buyPrice, predictedPrices[i][j]);
            if (predictedPrices[i][j] < buyPrice)
            {
                buyPriceIndex = j;
            }

            //  If it's the first day for a given stock, then no profit is possible yet.
            if (j == 0)
            {
                maxProfitStockDay[i][j] = 0;
            }
            //  Otherwise, we want to see whether subtracting the lowest price found so far
            //  from the current stock price will yield a larger value that the current
            //  value found within the maxProfit variable. If it is larger, the we've
            //  we've found a new maxProfit. We do this until we ultimately find the largest
            //  profit possible within the 2d vector.
            else
            {
                maxProfitStockDay[i][j] = max(maxProfitStockDay[i][j - 1], predictedPrices[i][j] - buyPrice);

                if (predictedPrices[i][j] - buyPrice > maxProfit)
                {
                    maxProfitStock = i;
                    maxProfitBuyDay = buyPriceIndex + 1;
                    maxProfitSellDay = j;
                    maxProfit = predictedPrices[i][j] - buyPrice;

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
    
    if (maxProfit > 0)
    {
        maxProfitValues[0] = maxProfitStock + 1;
        maxProfitValues[1] = maxProfitBuyDay + 1;
        maxProfitValues[2] = maxProfitSellDay + 1;
        maxProfitValues[3] = maxProfit;
    }
    //  If maxProfit is 0, then no transaction was found that would
    //  lead to a profit. So we want to return the tuple (0, 0, 0, 0).
    else if (maxProfit <= 0)
    {
        maxProfitValues[0] = maxProfitStock;
        maxProfitValues[1] = maxProfitBuyDay;
        maxProfitValues[2] = maxProfitSellDay;
        maxProfitValues[3] = maxProfit;
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
    cout << "(" << maxProfitValues[0]   << ", "
                << maxProfitValues[1]   << ", "
                << maxProfitValues[2]   << ", "
                << maxProfitValues[3]   << ")";
    cout << endl;
    cout << endl;

}
