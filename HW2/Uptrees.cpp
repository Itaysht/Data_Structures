#include "Uptrees.h"

const int REMOVED_TEAM = -1;
const int PLAYER_NOT_FOUND = -1;
const int PLAYER_ALREADY_EXISTS = -1;

const double GOLD_FOR_HASH = ((sqrt(5) - 1) / 2);

void Uptrees::insert(Player *player, Team *team) {
    if (size_of_array / 2 < (num_of_players + 1)) {
        allocateBiggerArray();
    }
    int index = hashID(player->getPlayerId(), false, array_of_players);
    NodePlayer *player_gets_in = new NodePlayer(player->getPlayerId(), player);
    player_gets_in->addGamesPlayedToNode(-1 * (team->getBalanace()));
    team->setBalance(0);
    array_of_players[index] = player_gets_in;
    num_of_players++;
    if (team->getLastPlayer() == nullptr) {
        NodeTeam *team_node = new NodeTeam(team->getID(), team);
        player_gets_in->setFatherTeam(team_node);
    } else {
        int last_player_id = team->getLastPlayer()->getPlayerId();
        player_gets_in->setFatherPlayer(array_of_players[hashID(last_player_id, true, array_of_players)]);
    }
    team->setLastPlayer(player);
    if (team->getFirstPlayer() == nullptr) {
        team->setFirstPlayer(player);
    }
}

int Uptrees::hashID(int i, bool is_find, NodePlayer **players_array_to_hash) const {
    //constant hash function
    double before_frac = (i * GOLD_FOR_HASH);
    double after_frac = before_frac - long(before_frac);
    int ans = floor(size_of_array * after_frac);
    if (!is_find) {
        int counter = 0;
        while (players_array_to_hash[ans] != nullptr and counter < size_of_array) {
            if (players_array_to_hash[ans]->value->getPlayerId() == i) {
                return PLAYER_ALREADY_EXISTS;   //player already exist
            }
            ans++;
            ans %= size_of_array;
            counter++;
        }
        return ans;
    }
    int counter = 0;
    while (players_array_to_hash[ans] != nullptr and counter < size_of_array) {
        if (players_array_to_hash[ans]->value->getPlayerId() == i) {
            return ans;
        }
        ans++;
        ans %= size_of_array;
        counter++;
    }
    return PLAYER_NOT_FOUND;
}

Player *Uptrees::findPlayer(int player_id) const {
    int index = hashID(player_id, true, array_of_players);
    if (index == PLAYER_NOT_FOUND) {
        return nullptr;
    }
    return array_of_players[index]->value;
}

int Uptrees::playerGamesPlayedNode(int player_id) const {   //assume the player exist
    int index = hashID(player_id, true, array_of_players);
    int ans = array_of_players[index]->games_played_of_team;
    return ans;
}

void Uptrees::addGamesPlayedOnlyToFirst(Player *player) {
    int index = hashID(player->getPlayerId(), true, array_of_players);
    array_of_players[index]->addGamesPlayedToNode(1);
}

bool Uptrees::isFirstOfSomeTeam(int player_id) const {
    int index = hashID(player_id, true, array_of_players);
    if (array_of_players[index]->father_player == nullptr) {
        return true;
    }
    return false;
}


void Uptrees::allocateBiggerArray() {
    NodePlayer **biggerArray = new NodePlayer *[size_of_array * 2];
    int before_size_of_array = size_of_array;
    size_of_array *= 2;
    for (int i = 0; i < size_of_array; i++) {
        biggerArray[i] = nullptr;
    }
    for (int i = 0; i < before_size_of_array; i++) {
        if (array_of_players[i] != nullptr) {
            int temp_player_id = array_of_players[i]->value->getPlayerId();
            biggerArray[hashID(temp_player_id, false, biggerArray)] = array_of_players[i];
        }
    }
    delete[] array_of_players;
    array_of_players = biggerArray;
}


Team *Uptrees::findTeam(int player_id, bool is_buy) {
    int index = hashID(player_id, true, array_of_players);
    if (index == PLAYER_NOT_FOUND) {
        return nullptr;
    }
    NodePlayer *player_node = array_of_players[index];
    NodePlayer *found_player = player_node;

    int sum_games = found_player->games_played_of_team;
    permutation_t *ans = new permutation_t(permutation_t::neutral());
    while (found_player->father_team == nullptr) {
        (*ans) = (*ans) * (*found_player->partial_perm);
        found_player = found_player->father_player;
        sum_games += found_player->games_played_of_team;
    }
    int temp_sum;
    NodePlayer *next_player = player_node->father_player;
    permutation_t *last_partial = new permutation_t(*player_node->partial_perm);
    if (is_buy) {
        player_node->setFatherPlayer(found_player);
        sum_games -= player_node->games_played_of_team;
        player_node->addGamesPlayedToNode(-found_player->games_played_of_team);
        player_node->setPartial(ans);
        *ans = (ans->inv() * (*last_partial)).inv();
        player_node = next_player;
        delete last_partial;
        last_partial = new permutation_t(*player_node->partial_perm);
        next_player = player_node->father_player;
    }
    while (player_node->father_team == nullptr) {
        player_node->setFatherPlayer(found_player);
        temp_sum = player_node->games_played_of_team;
        player_node->addGamesPlayedToNode(sum_games - found_player->games_played_of_team - temp_sum);
        sum_games -= temp_sum;
        player_node->setPartial(ans);
        *ans = (ans->inv() * (*last_partial)).inv();
        player_node = next_player;
        delete last_partial;
        last_partial = new permutation_t(*player_node->partial_perm);
        next_player = player_node->father_player;
    }
    delete ans;
    delete last_partial;
    return found_player->father_team->value;
}

void Uptrees::upTreeUnion(Team *bigger_team, Team *smaller_team) {
    int first_player_of_smaller_team = smaller_team->getFirstPlayer()->getPlayerId();

    NodePlayer *first_player_of_smaller_team_node = array_of_players[hashID
            (first_player_of_smaller_team,
             true, array_of_players)];
    if (bigger_team->getNumberOfPlayers() == 0) {
        first_player_of_smaller_team_node->father_team->value->setID(bigger_team->getID());
        first_player_of_smaller_team_node->father_team->setKey(bigger_team->getID());
        return;
    }
    int last_player_of_bigger_team = bigger_team->getLastPlayer()->getPlayerId();
    NodePlayer *last_player_of_bigger_team_node = array_of_players[hashID
            (last_player_of_bigger_team,
             true, array_of_players)];
    first_player_of_smaller_team_node->setFatherPlayer(last_player_of_bigger_team_node);

    int first_player_of_bigger_team = bigger_team->getFirstPlayer()->getPlayerId();
    NodePlayer *first_player_of_bigger_team_node = array_of_players[hashID
            (first_player_of_bigger_team,
             true, array_of_players)];
    NodeTeam *new_root = first_player_of_bigger_team_node->father_team;
    new_root->value->setLastPlayer(smaller_team->getLastPlayer());
    new_root->value->addPoints(first_player_of_smaller_team_node->father_team->value->getPoints());
    delete first_player_of_smaller_team_node->father_team;
    first_player_of_smaller_team_node->setFatherTeam(nullptr);
    findTeam(first_player_of_smaller_team, true);
}

void Uptrees::removeTeamFromPlayer(int player_id) {
    int index = hashID(player_id, true, array_of_players);
    NodeTeam *deleted_team_node = array_of_players[index]->father_team;
    deleted_team_node->games_played_deleted_team = deleted_team_node->value->getGamesPlayed();
    deleted_team_node->key = REMOVED_TEAM;
    deleted_team_node->value = nullptr;
}

Uptrees::~Uptrees() {
    for (int i = 0; i < size_of_array; i++) {
        delete array_of_players[i];
    }
    delete[] array_of_players;
}

Uptrees::Uptrees() : array_of_players(new NodePlayer *[2]), num_of_players(0), size_of_array(2) {
    array_of_players[0] = nullptr;
    array_of_players[1] = nullptr;
}

int Uptrees::getGamesPlayedDeletedTeam(int player_id) {
    int index = hashID(player_id, true, array_of_players);
    NodePlayer *player_node = array_of_players[index];

    while (player_node->father_team == nullptr) {
        player_node = player_node->father_player;
    }

    return player_node->father_team->games_played_deleted_team;
}

permutation_t Uptrees::getPartialPermutation(int player_id) {
    findTeam(player_id, false);
    int index = hashID(player_id, true, array_of_players);
    NodePlayer *found_player = array_of_players[index];
    permutation_t *ans = new permutation_t(*found_player->partial_perm);
    while (found_player->father_team == nullptr) {
        found_player = found_player->father_player;
        (*ans) = (*ans) * (*found_player->partial_perm);
    }
    if (found_player->father_team->key == REMOVED_TEAM) {
        delete ans;
        return permutation_t::invalid();
    }
    permutation_t return_ans = ans->inv();
    delete ans;
    return return_ans;
}

Uptrees::NodePlayer::~NodePlayer() {
    delete value;
    delete partial_perm;
    delete father_team;
}
