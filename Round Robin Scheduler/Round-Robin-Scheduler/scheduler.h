#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

const string Sentinel = "q";

class scheduler
{
public:
    scheduler(); //default constructor
    scheduler(int ini_teams); //constructor

    //generate the schedule for the number of teams = teams
    void generateSchedule(int& size);

    //display the table content of the schedule for each team
    void print();

    //destructor
    ~scheduler();

    //more member functions here ...

    //Insures the user inputs a valid team number >=1, <=512, and is a power of 2
    string validTeam();

    //Gets number of teams from the user and calls generate schedule
    void getTeam();

    //places empty vectors equal to the # of teams onto the Arrange vector
    void init();

    //copies the vectors in positions 0 to n/2-1 and reverses them
    //and inserts the resultant vectors in the n/2 to n-1 positions.
    void in_backwards(int size);

private:
    int teams;  //number of teams to be scheduled
    vector< vector<int> > Arrange; //2D vector to represent the scheduling table for each team
};

#endif // SCHEDULER_H_INCLUDED
