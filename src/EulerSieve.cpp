#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

typedef unsigned char u8;
typedef unsigned long ulong;
static ulong s_last = 0;
static u8* s_pAll = NULL;
static std::vector<ulong> s_vecPrime;

void showDetails()
{
    ulong pos = 0;
    while (true) {
        if (pos >= s_vecPrime.size())
            break;
        std::cout << s_vecPrime[pos++];
        if (pos < s_vecPrime.size())
            std::cout << ",";
        if (pos % 500 == 0) {
            printf("\n %u primes listed, %u left to show [c] continue; <q> quit: ", pos, s_vecPrime.size() - pos);
            std::string strInput;
            getline(std::cin, strInput);
            if (strInput == "q")
                break;
            std::cout << std::endl;
        }
        if (pos % 100 == 0)
            std::cout << std::endl;
    }
}

bool eulerSieve()
{
    DWORD tickBegin = GetTickCount();
    s_pAll = new u8[s_last];
    if (!s_pAll) {
        printf("Lack of memory.\n");
        return false;
    }

    ulong sum = 0;
    memset(s_pAll, 1, s_last);
    for (ulong num = 2; num < s_last; ++num) {
        if (s_pAll[num - 1] == 1) {
            ++sum;
            s_vecPrime.push_back(num);
        }
        for (ulong idx = 0; idx < sum; ++idx) {
            ulong prime = s_vecPrime[idx];
            ulong multiple = num * prime;
            if (multiple >= s_last)
                break;
            s_pAll[multiple - 1] = 0;
            if (num % prime == 0)
                break;
        }
    }
    printf(" %u primes found in %u milliseconds.\n\n", sum, GetTickCount() - tickBegin);
    delete []s_pAll;
    return true;
}

int main()
{
    printf(" EulerSieve: a method to find out all primes below the number that you specify here please: ");
    std::string strInput;
    getline(std::cin, strInput);
    s_last = strtoul(strInput.c_str(), 0, 10);
    if (s_last <= 2) {
        printf("\n Wrong input.\n");
        return 0;
    }
    printf("\n Only the sum of all primes needed [y/n](y as default): ");
    getline(std::cin, strInput);
    bool bDetail = (strInput == "n");
    if (bDetail)
        printf("\n Start to work out all primes below %u...\n", s_last);
    else
        printf("\n Start to work out the sum of all primes below %u...\n", s_last);
    if (!eulerSieve())
        return 0;
    if (bDetail)
        showDetails();
    return 0;
}
