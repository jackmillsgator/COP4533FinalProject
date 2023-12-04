
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findMaxProfit(vector<vector<int>> predictedPrices);
void printMaxProfitValues(vector<int> maxProfitValues, string vectorName);

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
    long unsigned int k = 0;

    int maxProfitStock = 0;
    int maxProfitBuyDay = 0;
    int maxProfitSellDay = 0;
    int maxProfit = 0;
    int tempInt = 0;

    //  I'm creating a vector of size 4 filled with 0 as all of its values.
    //  If a max profit from a transaction is, indeed, found, then the 0's
    //  will change to other values.
    vector<int> maxProfitValues(4, 0);

    //  **************************************************************************************************  //
    //                                                                                                      //
    //  With the given time complexity of O(m · n^2), we know that n^2 could describe a nested for loop     //
    //  that will search through each element of a 2d array. And because there is also ‘m’ within the       //
    //  time complexity, it appears that we have an additional, novel loop through our data                 //
    //                                                                                                      //
    //  **************************************************************************************************  //

    //  Iterating through each stock
    for (i = 0; i < predictedPrices.size(); i++)
    {
    
        //  Iterating through the prices for each stock
        for (j = 0; j < predictedPrices[i].size(); j++)
        {

            //  I'm going through each previous price before the current
            //  stock price (price at index j) and subtracting each
            //  previous stock from the current stock. If the sum of
            //  that operation is larger than the current value of
            //  maxProfit, then the sum becomes the new value of
            //  maxProfit.
            for (k = 0; k < j; k++)
            {

                tempInt = predictedPrices[i][j] - predictedPrices[i][k];

                //  If a new, larger value for maxProfit is found, we
                //  want to store and keep track of the new value for
                //  value for maxProfit as well as other information
                //  regarding that transaction for when we print the
                //  desired tuple of informational values.
                if (tempInt > maxProfit)
                {
                    maxProfitStock = i;
                    maxProfitBuyDay = k;
                    maxProfitSellDay = j;
                    maxProfit = tempInt;
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