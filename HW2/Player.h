#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "wet2util.h"

class Player {
public:
    Player(int player_id, int team_id, permutation_t *spirit, int games_played, int
    ability, int cards, bool is_GK);

    ~Player();

    Player(const Player &v1) = default;

    Player &operator=(const Player &other) = default;

    int getPlayerId() const;

    int getCards() const;

    void addCards(int addCards);

    int getGamesPlayed() const;

    permutation_t getSpirit() const;


private:
    int player_id;
    int team_id;
    permutation_t *spirit;
    int games_played;
    int ability;
    int cards;
    bool is_GK;
};

bool operator!=(const Player &v1, const Player &v2);

bool operator==(const Player &v1, const Player &v2);

Player operator-(const Player &v1, const Player &v2);


#endif //EX1_PLAYER_H
