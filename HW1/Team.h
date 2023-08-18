#ifndef EX1_TEAM_H
#define EX1_TEAM_H

#include "Dictionary.h"
#include "Player.h"

class Team
{
public:
    Team(int teamID, int points = 0);
    Team(const Team& other) = default;
    ~Team();
    StatusType add_player_in_team(int playerID, Player* pl);
    StatusType remove_player_in_team(int playerID, Player* pl);

    void move_all_players(Team* team2);
    int valueOfTeam() const;   //points + strength
    int getPoints() const;
    int getStrength() const;
    int getID() const;
    int getGamesPlayed() const;
    int getTopScorerInTeam() const;
    void addPoints(int points);
    void addStrength(int strength);
    void addGamesPlayed(int added);
    int numberOfPlayers() const;
    bool isGoalKeeperExists() const;
    bool isValidTeam() const;
    bool operator>(const Team& other) const;
    bool operator==(const Team& other) const;
    Team& operator-=(const Team& other);
    Player* findPlayerByKey(int key);
    bool operator/(const Team& other) const;
    int* getAllPlayersInTeam();
    int getCompensationPoints() const;
    void addCompensationPoints(int points);
    int getCompensationStrength() const;

    void addCompensationStrength(int strength);
    void setClosestLeft(Team* other);
    void setClosestRight(Team* other);
    Team* getClosestLeft();
    Team* getClosestRight();

private:
    int teamID;
    int m_points;
    int m_strength;
    int m_games_played;
    int m_number_of_players;
    int m_goalKeeper_exist;
    int m_compensation_points;
    int m_compensation_strength;
    Dictionary<int, Player*> m_dict_of_players_in_team;
    Player* m_top_scorer_of_team;
    Dictionary<int, Player*> m_dict_of_players_in_team_by_key;
};
bool operator!=(const Team& v1, const Team& v2);
bool operator<(const Team& v1, const Team& v2);
Team operator-(const Team& v1, const Team& v2);

#endif //EX1_TEAM_H
