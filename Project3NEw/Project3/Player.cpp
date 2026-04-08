#include "Player.h"	
#include "Arena.h"
#include "globals.h"	
#include <iostream>	
#include <cstdlib>	
using namespace std;

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // TODO: TRIVIAL:  Return what row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // DONE
}

int Player::col() const
{
    // TODO: TRIVIAL:  Return what column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // DONE
}

int Player::age() const
{
    // TODO:  TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // DONE
}



string Player::takeComputerChosenTurn()
{
    // TODO:  Replace this implementation:
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."

    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.

    // A more aggressive strategy is possible, where you hunt down robots.
    if (m_row > 1 && m_arena->nRobotsAt(m_row - 1, m_col) == 0)
    {
        move(UP);
        return "Moved.";
    }
    if (m_row < m_arena->rows() && m_arena->nRobotsAt(m_row + 1, m_col) == 0)
    {
        move(DOWN);
        return "Moved.";
    }
    if (m_col > 1 && m_arena->nRobotsAt(m_row, m_col - 1) == 0)
    {
        move(LEFT);
        return "Moved.";
    }
    if (m_col < m_arena->cols() && m_arena->nRobotsAt(m_row, m_col + 1) == 0)
    {
        move(RIGHT);
        return "Moved.";
    }

    if (m_row > 1)
    {
        move(UP);
        return "Moved.";
    }
    if (m_row < m_arena->rows())
    {
        move(DOWN);
        return "Moved.";
    }
    if (m_col > 1)
    {
        move(LEFT);
        return "Moved.";
    }
    if (m_col < m_arena->cols())
    {
        move(RIGHT);
        return "Moved.";
    }


    stand();
    return "Stood.";
}





void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;

    int newRow = m_row;
    int newCol = m_col;

    switch (dir)
    {
    case UP:
        newRow--;
        break;
    case DOWN:
        newRow++;
        break;
    case LEFT:
        newCol--;
        break;
    case RIGHT:
        newCol++;
        break;
    
    }

    if (newRow >= 1 && newRow <= m_arena->rows())
        m_row = newRow;

    if (newCol >= 1 && newCol <= m_arena->cols())
        m_col = newCol;
}


bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;

    if (dir == UP)
    {
        int start = m_row - 1;
        int end = m_row - 4;
        if (end < 1) 
            end = 1;  
        for (int i = start; i >= end; i--)
        {
            if (m_arena->nRobotsAt(i, m_col) > 0)
            {
                m_arena->damageRobotAt(i, m_col);
                return true;
            }
        }
    }

    if (dir == DOWN)
    {
        int start = m_row + 1;
        int end = m_row + 4;
        if (end > m_arena->rows())
            end = m_arena->rows();  
        for (int i = start; i <= end; i++)
        {
            if (m_arena->nRobotsAt(i, m_col) > 0)
            {
                m_arena->damageRobotAt(i, m_col);
                return true;
            }
        }
    }

    if (dir == LEFT)
    {
        int start = m_col - 1;
        int end = m_col - 4;
        if (end < 1) 
            end = 1;
        for (int i = start; i >= end; i--)
        {
            if (m_arena->nRobotsAt(m_row, i) > 0)
            {
                m_arena->damageRobotAt(m_row, i);
                return true;
            }
        }
    }

    if (dir == RIGHT)
    {
        int start = m_col + 1;
        int end = m_col + 4;
        if (end > m_arena->cols()) 
            end = m_arena->cols();
        for (int i = start; i <= end; i++)
        {
            if (m_arena->nRobotsAt(m_row, i) > 0)
            {
                m_arena->damageRobotAt(m_row, i);
                return true;
            }
        }
    }

    return false;
}


bool Player::isDead() const
{
    // TODO:  TRIVIAL:  Return whether the player is dead.
    return m_dead;  // DONE
}

void Player::setDead()
{
    m_dead = true;
}