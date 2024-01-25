///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////

#include "poly_exp.hpp"
#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>

int algorithms::soccer_exhaustive(const std::vector<std::string> field)
{
    if(field.size() == 0){
        throw std::invalid_argument("Invalid Argument");
    }

    if(field[0].size() == 0){
       throw std::invalid_argument("Invalid Argument");
    }

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            if ((field[i][j] == '.' ) || (field[i][j] == 'X')){
                continue;
            }
            else{
                throw std::invalid_argument("Invalid Argument");
            }
        }
    }

    if (field.size() > 1){
        for (int i = 0; i < field.size(); i++) {
            if (field[i].size() == field[0].size()){
                continue;
            }
            else{
                throw std::invalid_argument("Invalid Argument");
            }
        }
    }

    int counter = 0;

    if(field[0][1] == 'X' && field[1][0] == 'X'){
        return counter;
    }

    if(field.size() == 1 && field[0].size() == 1){
        if (field[0][0] == '.')
            counter = 1;
        else
            counter = 0;
        return counter;
    }

    if (field.size() > 1){
        if(field[field.size()-2][field[0].size()-1] == 'X' && field[field.size()-1][field[0].size()- 2] == 'X'){
            return counter;
        }
    }
    
    int len = (field.size()) + (field[0].size()) - 2;
    if (len > 31)
    {
        throw std::invalid_argument("Invalid Argument");
    }
    for (auto bits = 0; bits <= (pow(2, len) - 1); ++bits)
    {
        int right = 0;
        int down = 0;
        for (auto k = 0; k <= (len - 1); ++k)
        {
            auto bit = (bits >> k) & 1;
            if (bit == 1)
                right++;
            else
                down++;
            if (right > field[0].size()-1)
                break;
            if (down > field.size()-1)
                break;
            if (down == field.size() - 1 && right == field[0].size() - 1){
                if (field[down][right] == '.')
                    counter++;
                break;
            }
            if (field[down][right] == '.')
                continue;
            else
                break;
        }
    }
    return counter;
}

int algorithms::soccer_dyn_prog(const std::vector<std::string> field)
{

    if(field.size() == 0){
        throw std::invalid_argument("Invalid Argument");
    }

    if(field[0].size() == 0){
        throw std::invalid_argument("Invalid Argument");
    }

    if (field.size() > 1){
        for (int i = 0; i < field.size(); ++i) {
            if (field[i].size() == field[0].size()){
                continue;
            }
            else{
                throw std::invalid_argument("Invalid Argument");
            }
        }
    }

    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            if ((field[i][j] == '.' ) || (field[i][j] == 'X')){
                continue;
            }
            else{
                throw std::invalid_argument("Invalid Argument");
            }
        }
    }

    // corner case: initial cell is impassible
    std::vector<std::vector<int>> A(field.size(), std::vector<int> (field[0].size(), 0));
    if (field[0][0] == 'X')
        return 0;
    // base case
    A[0][0] = 1;
    // general cases
    for (int i = 0; i <= (field.size() - 1); i++)
    {
        for (int j = 0; j <= (field[0].size() - 1); j++)
        {
            if (field[i][j] == 'X')
            {
                A[i][j] = 0;
                continue;
            }
            int above = 0;
            int left = 0;
            if (i > 0 && field[i - 1][j] == '.')
                above = A[i - 1][j];
            if (j > 0 && field[i][j - 1] == '.')
                left = A[i][j - 1];
            A[i][j] += above + left;
        }
    }
    return A[field.size() - 1][field[0].size() - 1];
}
