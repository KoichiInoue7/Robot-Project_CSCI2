
#include "Robot.h"	
#include "Arena.h"	
#include "globals.h"	
#include <iostream>	
#include <cstdlib>	
using namespace std;

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_hit = false;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    // TODO: TRIVIAL:  Return what column the robot is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // DONE
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
    case UP:
        if (m_row > 1) m_row--;
        // TODO:  Move the robot up one row if possible.
        break;
    case DOWN:
        if (m_row < m_arena->rows()) m_row++;
        break;
    case LEFT:
        if (m_col > 1) m_col--;
        break;
    case RIGHT:
        if (m_col < m_arena->cols()) m_col++;
        // TODO:  Implement the other movements.
        break;

    }

}

bool Robot::takeDamageAndLive()
{
    if (m_hit)
        return false;

    m_hit = true;
    return true;
    // TODO:  If the robot has been hit once before, return false (since a
    // second hit kills a robot).  Otherwise, return true (since the robot
    // survived the damage).
}