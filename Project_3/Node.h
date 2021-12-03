#pragma once

#include "Game.h"

template <typename T>
class Node
{
private:
    T m_game;
    Node* m_left;
    Node* m_right;
public:
    Node(T &game)
    {
        m_game  = game;
        m_left  = nullptr;
        m_right = nullptr;
    }
    
    T& getGame() { return m_game; }
    Node* getLeft() const { return m_left; }
    Node* getRight() const { return m_right; }
    
    void setGame(T game) { m_game = game; }
    void setLeft(Node* left) { m_left = left; } 
    void setRight(Node* right) { m_right = right; }
    
    bool operator<(Node<T> node)
    {
        if (getGame().getRev() < node.getGame().getRev())
            return true;
        else
            return false;
    }
    
    bool operator>(Node<T> node)
    {
        if (getGame().getRev() > node.getGame().getRev())
            return true;
        else
            return false;
    }
    
    bool operator==(Node<T> node)
    {
        if (getGame().getRev() == node.getGame().getRev())
            return true;
        else
            return false;
    }
    
    friend ostream& operator<<(ostream &out, Node<T>* node)
    {
        Game g = node->getGame();
        out << "Name: " << g.getName() << '\n'
            << "High Score: " << g.getScore() << '\n'
            << "Initials: " << g.getInitials() << '\n'
            << "Plays: " << g.getPlays() << '\n'
            << "Revenue: $" << g.getRev() << endl;
        
        return out;
    }
};
