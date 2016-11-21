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

//default constructor
scheduler::scheduler()
{
    vector<int> newVec;//empty vector to be nested in the Arrange vector
    Arrange.push_back(newVec);
    teams = 0;//inititialize # of teams to 0
}

//Constructor that nests ini_teams onto Arrange
scheduler::scheduler(int ini_teams)
{
    Arrange.clear();//erases the Arrange elements from the previous generate schedule call
    for(int i = 0; i < teams; i++)//nests empty vectors into Arrange equal to the integer ini_teams
    {
        vector<int> newVec;//empty vector to be nested in Arrange
        Arrange.push_back(newVec);
    }
    Arrange.at(0).push_back(1);//There will always be a tournament of at least one team
}

//Creates round robing schedule for the specified # of teams
void scheduler::generateSchedule(int& size)
{
    for(int i = 0; i < size/2; i++)//will get each vector (A) on the left half of the matrix
    {
        vector<int> temp = Arrange.at(i);//temporarily holds current Arrange vector
        for(int j = 0; j < Arrange.at(i).size(); j++)//Adds (B) which is element at Ai + size/2
        {
            temp.insert(temp.end(), temp.at(j)+size/2);//Insert left half of matrix
        }
        Arrange.at(i)=temp;//Reassign updated vector to Arrange[i]
        in_backwards(size);//have created upper half of matrix, this copies to lower half in reverse order
    }
    if(size < teams)//recursive call to create tournament twice the size until it is equal to # of teams
    {
        size*=2;
        generateSchedule(size);
    }
    if(size == teams)//must reset size for next generate schedule call
    {
        size = 1;
    }
}

//Copies upper half of matrix to lower half in reverse order
void scheduler::in_backwards(int size)
{
    for(int i = size/2-1; i >= 0; i--)
    {
        vector<int> rev;//will contain the reverse order of the current vector
        vector<int> cach = Arrange.at(i);//catches the current Arrange vector
        for(int j = cach.size()-1; j >= 0; j--)
        {
            rev.insert(rev.end(), cach.at(j));//reverses the order of the current Arrange vector
        }
        Arrange.at(size-i-1)= rev;
    }
}

//Outputs the contents of the Arrange
void scheduler::print()
{
    for(int i = 0; i < 80; i++)
        cout << "=";//Separates each print call
    for(int i = 0; i < teams; i++)
    {
       for(int j = 0; j < Arrange.at(i).size(); j++)
            cout << setw(4) << Arrange.at(i).at(j) << setfill(' ');//outputs each Arrange vector's contents
       cout << endl;
    }
    for(int i = 0; i < 80; i++)
        cout << "=";//Separates each print call
    cout << endl;
}

//Scheduler class destructor
scheduler::~scheduler()
{
    Arrange.clear();
    teams = 0;
}

//Validates the user inputs either q or a power of 2 integer <= 512, including 1
string scheduler::validTeam()
{
    string userval;

    cout << endl << "Enter the number of teams in the tournament,";//prompts user for valid input
    cout << "where the number of teams is a power of two <= 512.";
    cout << " (Enter q to stop)" << endl << endl;
    std::getline (std::cin,userval);//gets user input to be validated

    while( (userval != "1")&&(userval != "2")&&(userval != "4")&&(userval != "8")
           &&(userval != "16")&&(userval != "32")&&(userval != "64")
           &&(userval != "128")&&(userval != "256")&&(userval != "512")&&(userval != "q") )//verifies valid team # entry
          {
              cout << "Enter a valid integer between 1 and 512 that is a power of 2.";
              cout << "(Enter q to stop)" << endl << endl;
              std::getline (std::cin,userval);//repeatedly gets user input until proper input is received
          }
    return userval;//have gotten desired input and can return to calling method
}

//calls all the other scheduler class methods
void scheduler::getTeam()
{
    bool done = false;//used to exit while loop
    string userval;//userval to be converted into an integer
    int num;//contains the converted userval from string to int data type
    int size = 1;//sets schedule to generate tournament of size 1

    userval = validTeam();//gets valid user input
    if( userval == Sentinel )//checks for 'q'
            done = true;

    if( !done )//repeatedly prompts the user for their input until 'q' is entered
        while(!done)
            {//loops until user has entered sentinel value q
                num = std::atoi(userval.c_str());//converts from a string to int
                teams = num;//updates desired number of teams in tournament schedule
                init();//nests # of vectors in arrange equal to # of teams
                generateSchedule(size);//generate a schedule of team size 1
                print();//output the contents of Arrange after generateSchedule has completed
                userval = validTeam();//get the next user input
                if( userval == Sentinel )//check for 'q'
                    done = true;
            }
}

//Nests the # of vectors in Arrange equal to the private member teams
void scheduler::init()
{
    Arrange.clear();//clears the contents of Arrange leftover from the previous generateSchedule call
    for(int i = 0; i < teams; i++)//Nests the # of vectors in Arrange equal to the private member teams
    {
        vector<int> newVec;
        Arrange.push_back(newVec);
    }
    Arrange.at(0).push_back(1);//Always will have a tournament of at least 1 team
}
