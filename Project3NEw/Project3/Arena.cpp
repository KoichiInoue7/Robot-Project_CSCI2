#include "Arena.h"	
#include "Player.h"	
#include "Robot.h"		
#include "globals.h"	
#include <iostream>	
#include <cstdlib>	
#include <string>	
using namespace std;

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }

    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;

    // Initialize all robot pointers to nullptr
    for (int i = 0; i < MAXROBOTS; i++)
        m_robots[i] = nullptr;
}


Arena::~Arena()
{
    // TODO:  Delete the player and all remaining dynamically allocated robots.
    delete m_player;
    m_player = nullptr;

    for (int i = 0; i < m_nRobots; i++)
    {
        delete m_robots[i];
        m_robots[i] = nullptr;
    }
      m_nRobots = 0; 

      for (int i = 0; i < MAXROBOTS; i++)
          m_robots[i] = nullptr;
}

int Arena::rows() const
{
    // TODO:  TRIVIAL:  Return the number of rows in the arena.
    // Delete the following line and replace it with the correct code.
    return m_rows;  // DONE
}

int Arena::cols() const
{
    // TODO:  TRIVIAL:  Return the number of columns in the arena.
    // Delete the following line and replace it with the correct code.
    return m_cols;  // DONE
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    // TODO:  Return the number of robots at row r, column c.
    int count = 0;
    for (int i = 0; i < m_nRobots; i++)
    {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
            count++;
    }
    return count;

}

void Arena::display(string msg) const
{
    char grid[MAXROWS][MAXCOLS];

    // Fill with dots
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            grid[r - 1][c - 1] = '.';

    // Robots
    for (int i = 0; i < m_nRobots; i++)
    {
        int r = m_robots[i]->row();
        int c = m_robots[i]->col();

        int count = nRobotsAt(r, c);
        if (count == 1)
            grid[r - 1][c - 1] = 'R';
        else if (count <= 8)
            grid[r - 1][c - 1] = '0' + count;
        else
            grid[r - 1][c - 1] = '9';
    }

    // Player
    if (m_player != nullptr)
    {
        int r = m_player->row();
        int c = m_player->col();
        grid[r - 1][c - 1] = '@';
    }

    // Print
    clearScreen();
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }

    cout << endl << msg << endl;
}


bool Arena::addRobot(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.

    // TODO:  Implement this.


    if (m_nRobots >= MAXROBOTS)
    {
        return false;
    }
    else
    {
        m_robots[m_nRobots] = new Robot(this, r, c);
        m_nRobots++;
        return true;
    }


    // DONE
}

bool Arena::addPlayer(int r, int c)
{
    // TODO:  Return the number of robots at row r, column c.
    if (m_player != nullptr)
        return false;
    cout << "Creating player at (" << r << "," << c << ")" << endl;

    
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.

    for (int i = m_nRobots - 1; i >= 0; i--)
    {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
        {
            if (!m_robots[i]->takeDamageAndLive())
            {
                delete m_robots[i];
                m_robots[i] = m_robots[m_nRobots - 1]; 
                m_robots[m_nRobots - 1] = nullptr;     
                m_nRobots--;
            }
            break; 
        }
    }
}


bool Arena::moveRobots()
{

    for (int k = 0; k < m_nRobots; k++)
    {
        //TODO:  Have the k - th robot in the arena make one move.
        //        If that move results in that robot being in the same
        //        position as the player, the player dies.
        m_robots[k]->move();
        if (m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col())
        {
            m_player->setDead();
            return false;
        }
    }

    // return true if the player is still alive, false otherwise
    return true;
}
