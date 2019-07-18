#define NOMINMAX

#include <iostream>
#include <string>
#include <algorithm>
#include "LinkedList.h"
#include "ConsoleColor.h"
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <time.h>

bool equalIgnoreCase(std::string s1, std::string s2)
{
    bool eq = false;
        for(unsigned int i = 0; i < std::min(s1.length(), s2.length()); i++)
        {
            if(isupper(s1.at(i)))
            {
                if(s1.at(i) == s2.at(i) || s1.at(i)+32 == s2.at(i))
                    eq = true;
                else
                {
                    eq = false;
                    break;
                }
            }
            else
            {
                if(s1.at(i) == s2.at(i) || s1.at(i)-32 == s2.at(i))
                    eq = true;
                else
                {
                    eq = false;
                    break;
                }
            }
        }
    return eq;
}

bool yes(std::string asw)
{
    if(equalIgnoreCase(asw, "Yes") || equalIgnoreCase(asw, "y"))
        return true;
    else
        return false;
}

void getCombinations(int N, int K, sll::LinkedList<sll::LinkedList<int>>& cmb)
{
    std::string bitmask(K, 1);
    bitmask.resize(N, 0);

        do
        {
            sll::LinkedList<int> tmp;
                for(int i = 0; i < N; i++)
                {
                    if(bitmask[i])
                    {
                        tmp.push(i);
                    }
                }
                    cmb.push(tmp);
        }while(std::prev_permutation(bitmask.begin(), bitmask.end()));
}

void getPermutations(int inx[], sll::LinkedList<std::string>& prm, unsigned int ln, std::string ss)
{
    std::string sx = "";
        do
        {
            for(unsigned int i = 0; i < ln; i++)
            {
                sx += ss.at(inx[i]);
                //std::cout << sx;
                //std::cout << inx[i] << (i != ss.length()-1 ? " - " : "\n");
            }
                prm.push(sx);
                sx = "";
                //std::cout << std::endl;
        }while(std::next_permutation(inx, inx+ln));
}

static void redrawPrompt(void)
{
    static int  numDots;
    const  int  maxDots = 3;
    const  char prompt[] = "Loading";

    // Return and clear with spaces, then return and print prompt.
    printf("\r%*s\r%s", sizeof(prompt) - 1 + maxDots, "", prompt);
    for (int i = 0; i < numDots; i++)
        fputc('.', stdout);
    fflush(stdout);
    if (++numDots > maxDots)
        numDots = 0;
}

sll::LinkedList<std::string> sorted(sll::LinkedList<std::string>& wrs)
{
    sll::LinkedList<std::string> srt;
        for(unsigned int i = 0; i < wrs.length(); i++)
        {
            if(wrs[i].length() == 5)
                srt.push(wrs[i]);
        }
            for(unsigned int i = 0; i < wrs.length(); i++)
            {
                if(wrs[i].length() == 4)
                    srt.push(wrs[i]);
            }
                for(unsigned int i = 0; i < wrs.length(); i++)
                {
                    if(wrs[i].length() == 3)
                        srt.push(wrs[i]);
                }
                    for(unsigned int i = 0; i < wrs.length(); i++)
                    {
                        if(wrs[i].length() == 2)
                            srt.push(wrs[i]);
                    }

    return srt;
}

int doubleLetters(sll::LinkedList<sll::LinkedList<int>>& cmb)
{
    int dd = 0;
        for(unsigned int i = 0; i < cmb.length(); i++)
        {
            if(cmb[i].length() == 2)
                dd++;
        }
    return dd;
}

int main()
{
    std::string asw;
    std::ifstream ifs;
    ifs.open("engdict.txt");
    std::ofstream of("res.txt");
    std::string letter = "";
    std::string tmp = "";
    int filter = 0;
    std::cout << ccl::yellow;
    sll::LinkedList<sll::LinkedList<int>> Combs;
    sll::LinkedList<std::string> Perms;
    sll::LinkedList<std::string> Words;
    const int trigger = (CLOCKS_PER_SEC * 500) / 1000;  // 500 ms in clocks.
    clock_t prevClock = clock() - trigger;

        do
        {
            std::cout << "Enter letters: ";
            std::cin >> letter;
                if(letter.length() > 6)
                    std::cout << ccl::red << "Only 6 letters can be accepted. Try Again.." << std::endl << ccl::yellow;
        }while(letter.length() > 6);

        std::transform(letter.begin(), letter.end(), letter.begin(), ::tolower);

            for(unsigned int i = letter.length(); i > 1; i--)
                getCombinations(letter.length(), i, Combs);

                std::cout << "Do you want to unsee the 2 letter words ?(y/n): ";
                std::cin >> asw;
                    if(yes(asw))
                        filter = doubleLetters(Combs);

                for(unsigned int i = 0; i < Combs.length()-filter; i++)
                    getPermutations(Combs[i].toArray(), Perms, Combs[i].length(), letter);

                    for(unsigned int i = 0; i < Perms.length(); i++)
                        of << Perms[i] << std::endl;

                        if(ifs.is_open())
                        {
                            std::cout << ccl::blue;
                            while(!ifs.eof())
                            {
                                clock_t curClock = clock();

                                    if (curClock - prevClock >= trigger)
                                    {
                                        prevClock = curClock;
                                        redrawPrompt();
                                    }
                                        ifs >> tmp;
                                            for(unsigned int i = 0; i < Perms.length(); i++)
                                            {
                                                if(tmp.compare(Perms[i]) == 0)
                                                {
                                                    Words.push(tmp);
                                                }
                                            }
                            }
                                ifs.close();
                                std::cout << std::endl << ccl::yellow << "There were " << Words.length() << " words found !" << std::endl;
                                std::cout << "The words are:" << std::endl;
                                sorted(Words).showVert();
                        }
                        else
                            std::cout << ccl::red << "Dictionary Not Found!" << std::endl << ccl::yellow;

    return 0;
}
