#include "Game.h"

Game::Game()
{
    m_name = "";
    m_score = 0;
    m_initials = "";
    m_plays = 0;
    m_revenue = 0.0;
}

Game::Game(string name, int score, string initials, int plays, double revenue)
{
    m_name = name;
    m_score = score;
    m_initials = initials;
    m_plays = plays;
    m_revenue = revenue;
}

string Game::getName() const { return m_name; }
int Game::getScore() const { return m_score; }
string Game::getInitials() const { return m_initials; }
int Game::getPlays() const { return m_plays; }
double Game::getRev() const { return m_revenue; }

void Game::setName(string &name) { m_name = name; }
void Game::setScore(int &score) { m_score = score; }
void Game::setInitials(string &initials) { m_initials = initials; }
void Game::setPlays(int &plays)
{
    m_plays = plays;
    m_revenue = plays * 0.25;
}

bool Game::operator<(Game &game)
{
    return getName().compare(game.getName()) < 0;
}
bool Game::operator>(Game &game)
{
    return getName().compare(game.getName()) > 0;

}
bool Game::operator==(Game &game)
{
    return getName().compare(game.getName()) == 0;

}

ostream& operator<<(ostream &out, Game g)
{
    out << "Name: " << g.getName() << '\n'
        << "High Score: " << g.getScore() << '\n'
        << "Initials: " << g.getInitials() << '\n'
        << "Plays: " << g.getPlays() << '\n'
        << "Revenue: $" << g.getRev() << endl;
    
    return out;
}
