//
// Created by itayi on 21/12/2022.
//

#ifndef WET2_SKIPLISTTEAMS_H
#define WET2_SKIPLISTTEAMS_H

#include "Team.h"
#include "wet2util.h"
#include <ctime>

#define INFINITY_NEGATIVE_ID (-1)

class SkipListTeams {

public:

    SkipListTeams(): root(new Node(INFINITY_NEGATIVE_ID, nullptr)){}
    ~SkipListTeams();

    StatusType insert(int teamId, Team* team);
    Team* find(int teamId) const;
    bool remove(int teamId);
    int get_height() const; //for tests

private:
    class Node {
    public:
        Node(int key, Team* value): key(key), value(value), right(nullptr), down(nullptr){}
        Node(const Node& node) = default;
        Node& operator=(const Node& node) = default;
        ~Node() = default;
        void setRight(Node *rig) {right = rig;}
        void setDown(Node *dow) { down = dow;}
        void setKey(int other_key){ key = other_key;}
        void setValue(Team* other_value){ value = other_value;}
        int key;
        Team* value;
        Node* right;
        Node* down;
    };

    Node* root;
    int genZeroOrOne();

    Node* recursiveInsert(int teamId, Team* team, Node* current_node);
    Node* addNodeAfter(int teamId, Team* team, Node* left_node);
    bool coinToss() const;
    void removeNodeAfter(Node* left_node);

};


#endif //WET2_SKIPLISTTEAMS_H
