#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H


class Player {
public:
    Player(int player_id,int team_id, int goals, int cards, int games_played, bool is_GK);
    ~Player() = default;
    Player(const Player& v1) = default;
    Player& operator=(const Player& other) = default;
    int getPlayerId() const;

    int getGoals() const;
    void addGoals(int addGoals);

    int getCards() const;
    void addCards(int addCards);

    int getGamesPlayed() const;
    void addGamesPlayed(int added);

    bool isGk() const;

    void setTeamID(int teamID);
    int getTeamID() const;

    bool operator>(const Player& other) const;
    bool operator<(const Player& other) const;
    bool operator/(const Player& other) const;   //left is smaller in all parameters than the right
    Player& operator-=(const Player& other);
    Player* getClosestLeft() const;
    Player* getClosestRight() const;
    void setClosestLeft(Player* other);
    void setClosestRight(Player* other);



private:
    int player_id;
    int team_id;
    int goals;
    int cards;
    int games_played;
    bool is_GK;
    int sub;
    Player* closest_left;
    Player* closest_right;

};
bool operator!=(const Player& v1, const Player& v2);
bool operator==(const Player& v1, const Player& v2);
Player operator-(const Player& v1, const Player& v2);


#endif //EX1_PLAYER_H
