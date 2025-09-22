// estimate_function_root.cpp - student template:
// Estimate the root (or x) of a given linear function, that is, f(x) = 0 using intervall bisection.
#include <iostream>
#include <stdio.h>
#include<cmath>

/* Given: increasing linear function to test f(x)=32*x-1 */
float exampleIncreasingLinearFunc(float x)
{
    return 32 * x - 1;
}

/* Given: decreasing linear function to test f(x)=-32*x-1 */
float exampleDecreasingLinearFunc(float x)
{
    return -32 * x - 1;
}

/* TODO: 1a)
Rounds a float value to n decimal places. E.g. val=1.555, n=2 returns 1.56*/
float roundValToNDecimals(float val, unsigned int n)
{
    float factor = std::pow(10.0f, static_cast<float>(n));
    return std::round(val * factor) / factor;
}

/* TODO: 1b)
 Returns true if the absolute difference of x1 and x2 is smaller or equal than a given epsilon,
otherwise returns false. Default epsilon checks for 5 decimal precision.*/
bool isAlmostEqual(float x1, float x2, float epsilon = 1.0e-5)
{
    return std::abs(x1 - x2) <= epsilon;
}

/* TODO: 1c-f)
Estimates the root, the x, of the linear function that is f(x)=0 within the specified interval [xLower, xUpper].
If the root is equal to the interval bounds or the midpoint it returns the corresponding x-value.
If the root is estimated (the intervall becomes small enough) the resulting x-value is rounded to n decimal places. 
If linear function in the specified interval does not have a root, it returns NAN. */
float estimateFunctionRoot(float (*linearFunc)(float), float xLower, float xUpper, unsigned int nDecimals)
{
    float fLower = linearFunc(xLower);
    float fUpper = linearFunc(xUpper);

    // Edge Cases
    if (fLower == 0.0f) return roundValToNDecimals(xLower, nDecimals);
    if (fUpper == 0.0f) return roundValToNDecimals(xUpper, nDecimals);

    while (!isAlmostEqual(xLower, xUpper)) {
        const float xMid = 0.5f * (xLower + xUpper);
        const float fMid = linearFunc(xMid);

        if (fMid == 0.0f) return roundValToNDecimals(xMid, nDecimals);

        const bool changeLeft = (fLower > 0.0f && fMid < 0.0f) || (fLower < 0.0f && fMid > 0.0f);
        if (changeLeft) {
            xUpper = xMid;
            fUpper = fMid;
        } else {
            xLower = xMid;
            fLower = fMid;
        }
    }
    const float xRoot = 0.5f * (xLower + xUpper);
    return roundValToNDecimals(xRoot, nDecimals);
}

/* Calls estimateFunctionRoot of increasing example function with the specified interval [lowerBound; upperBound] and prints out the result. */
void testAndPrintIncreasing(float xLower, float xUpper, unsigned int nDecimals = 5)
{
    float result = estimateFunctionRoot(&exampleIncreasingLinearFunc, xLower, xUpper, nDecimals);
    std::cout << "interval [" << xLower << ", " << xUpper << "], \t result = " << result << std::endl;
}

/* Calls estimateFunctionRoot of decreasing example function with the specified interval [lowerBound; upperBound] and prints out the result. */
void testAndPrintDecreasing(float xLower, float xUpper, unsigned int nDecimals = 5)
{
    float result = estimateFunctionRoot(&exampleDecreasingLinearFunc, xLower, xUpper, nDecimals);
    std::cout << "interval [" << xLower << ", " << xUpper << "], \t result = " << result << std::endl;
}

/* Test your implementation */
void testEstimateFunctionRoot()
{ 
    // Test 1a) Round up with 1 decimal, round down with 1 decimal, round with 4 decimal precision
    std::cout << "Round 1.55 to 1 decimal: " << roundValToNDecimals(1.55, 1) << ", expected: " << 1.6 << std::endl;
    std::cout << "Round 1.54 to 1 decimal: " << roundValToNDecimals(1.54, 1) << ", expected: " << 1.5 << std::endl << std::endl;

    // Test 1b) abs(x1 - x2) <= epsilon
    // x1 = 0.1, x2 = 0.11, decimal precision (epsilon) varies
    std::cout << "Is x1 = 0.1 almost equal to x2 = 0.11 with 1 decimal precision?: " << isAlmostEqual(0.1f, 0.11f, 0.1f) << ", expected: " << "1" << std::endl;
    std::cout << "Is x1 = 0.1 almost equal to x2 = 0.11 with 2 decimal precision?: " << isAlmostEqual(0.1f, 0.11f, 1e-2f) << ", expected: " << "1" << std::endl;
    std::cout << "Is x1 = 0.1 almost equal to x2 = 0.11 with 3 decimal precision?: " << isAlmostEqual(0.1f, 0.11f, 1e-3f) << ", expected: " << "0" << std::endl << std::endl;

    // Precision with 5 decimals (default of function)
    std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.000019 with 5 decimal precision?: " << isAlmostEqual(0.00001f, 0.000019f) << ", expected: " << "1" << std::endl;
    std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.00002 with 5 decimal precision?: " << isAlmostEqual(0.00001f, 0.00002f) << ", expected: " << "1" << std::endl;
    std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.000021 with 5 decimal precision?: " << isAlmostEqual(0.00001f, 0.000021f) << ", expected: " << "0" << std::endl << std::endl;

    // Test 1c) Estimate rounded
    testAndPrintIncreasing(0.01, 1.5);

    // Test 1d) Special cases: xUpper, xLower, midPoint (no rounding necessary)
    // f(x) = 0 for x = xUpper
    testAndPrintIncreasing(0, 0.03125);

    // f(x) = 0 for x = xLower
    testAndPrintIncreasing(0.03125, 1);

    // f(x) = 0 for x = midpoint = (xUpper - xLower)/2
    testAndPrintIncreasing(0, 0.03125 * 2);

    // Test 1e) Special case: no root found, return NAN
    testAndPrintIncreasing(0.0f, 0.02f);

    // Test 1f) Test decreasing function as well
    testAndPrintDecreasing(-1.0f, 1.0f);
}
