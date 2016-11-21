/*
Author: Adam Walls
Date: 3/7/2016
Class: CS216-001

The purpose of this program is to create a round robin tournament schedule where
the number of teams lies on the range of 1 to 512 inclusive and the number of
teams must be a power of two (1, 2, 4,...).
*/


#include <iostream>
#include <vector>
#include "scheduler.h"
#include <string>
#include<cstdlib>
#include <iomanip>

using namespace std;

int main()
{
    scheduler s;//creates object of the scheduler class
    s.getTeam();//method that calls all of the other scheduler class methods
    return 0;
}
