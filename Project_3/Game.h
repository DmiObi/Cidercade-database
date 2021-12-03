#pragma once

#include <string>
#include <ostream>

using namespace std;

class Game
{
private:
    string m_name;
    int    m_score;
    string m_initials;
    int    m_plays;
    double m_revenue;
    
public:
    Game();
    Game(string name, int score, string initials, int plays, double revenue);
    
    string getName() const;
    int getScore() const;
    string getInitials() const;
    int getPlays() const;
    double getRev() const;
    
    void setName(string &name);
    void setScore(int &score);
    void setInitials(string &initials);
    void setPlays(int &plays); 
    
    bool operator<(Game &game);
    bool operator>(Game &game);
    bool operator==(Game &game);
    friend ostream& operator<<(ostream &out, Game g);
};


