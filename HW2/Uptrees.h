#ifndef WET2_UPTREES_H
#define WET2_UPTREES_H

#include <cmath>

#include "Player.h"
#include "Team.h"

const int ACTIVE_TEAM_GAMES_PLAYED = -1;

class Uptrees {

public:
    Uptrees();
    ~Uptrees();

    Player* findPlayer(int player_id) const;
    int playerGamesPlayedNode(int player_id) const;
    bool isFirstOfSomeTeam(int player_id) const;
    Team* findTeam(int player_id, bool is_buy);
    void upTreeUnion(Team* bigger_team, Team* smaller_team);
    void insert(Player* player, Team* team);
    void removeTeamFromPlayer(int player_id);
    void addGamesPlayedOnlyToFirst(Player* player);
    int getGamesPlayedDeletedTeam(int player_id);
    permutation_t getPartialPermutation(int player_id);


private:
    class NodeTeam {
    public:
        NodeTeam(int key, Team* value): key(key), value(value),
        games_played_deleted_team(ACTIVE_TEAM_GAMES_PLAYED){}
        NodeTeam(const NodeTeam& node) = default;
        NodeTeam& operator=(const NodeTeam& node) = default;
        ~NodeTeam() = default;
        void setKey(int other_key){ key = other_key;}

        int key;
        Team* value;
        int games_played_deleted_team;
    };
    class NodePlayer {
    public:
        NodePlayer(int key, Player* value): key(key), value(value), father_player(nullptr), father_team(nullptr),
                                            partial_perm(new permutation_t(value->getSpirit().inv())),
                                            games_played_of_team(0){}
        NodePlayer(const NodePlayer& node) = default;
        NodePlayer& operator=(const NodePlayer& node) = default;
        ~NodePlayer();
        void setFatherPlayer(NodePlayer *fat) { father_player = fat;}
        void setFatherTeam(NodeTeam* fat) { father_team = fat;}
        void addGamesPlayedToNode(int added){ games_played_of_team += added;}
        void setPartial(permutation_t* partial){ *partial_perm = *partial;}

        int key;
        Player* value;
        NodePlayer* father_player;
        NodeTeam* father_team;
        permutation_t* partial_perm;
        int games_played_of_team;
    };

    NodePlayer** array_of_players;
    int num_of_players;
    int size_of_array;

    int hashID(int i, bool is_find, NodePlayer** players_array_to_hash) const;
    void allocateBiggerArray();
};


#endif //WET2_UPTREES_H
