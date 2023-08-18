#include "Team.h"

Team::Team(int teamID, int points) : teamID(teamID), m_points(points), m_strength(0),
                                m_games_played(0), m_number_of_players(0), m_goalKeeper_exist(0),
                                m_compensation_points(0), m_compensation_strength(0),
                                m_dict_of_players_in_team(Dictionary<int, Player*>(false, false)),
                                m_top_scorer_of_team(nullptr),
                                m_dict_of_players_in_team_by_key(Dictionary<int, Player*>(true, false)){}


Team::~Team() {
    m_dict_of_players_in_team_by_key.destroyNodes();
    m_dict_of_players_in_team.destroyNodes();
}

int Team::valueOfTeam() const {
    return m_strength + m_points;
}

int Team::getGamesPlayed() const {
    return m_games_played;
}

bool Team::isValidTeam() const {
    return ((numberOfPlayers() >= 11) && (isGoalKeeperExists()));
}

void Team::addGamesPlayed(int added) {
    m_games_played += added;
}

int Team::getPoints() const {
    return m_points;
}

int Team::getStrength() const {
    return m_strength;
}

void Team::addPoints(int points) {
    m_points += points;
}

void Team::move_all_players(Team *team2) {
    Player** moving_players_begin = team2->m_dict_of_players_in_team.inorderNodesByValue();
    Player** moving_players = moving_players_begin;
    int number_of_players_to_move = team2->numberOfPlayers();
    int i = 0;
    while (i < number_of_players_to_move){
        (*moving_players)->addGamesPlayed(team2->m_games_played);
        add_player_in_team((*moving_players)->getPlayerId(), *moving_players);
        (*moving_players)->setTeamID(getID());
        team2->remove_player_in_team((*moving_players)->getPlayerId(), *moving_players);
        i++;
        moving_players++;
    }
    delete[] moving_players_begin;
}

bool Team::operator>(const Team &other) const {
    return (valueOfTeam()) > (other.valueOfTeam());
}

bool Team::operator==(const Team &other) const {
    return (valueOfTeam()) == (other.valueOfTeam());
}

int Team::numberOfPlayers() const {
    return m_number_of_players;
}

void Team::addStrength(int strength) {
    m_strength += strength;
}

int Team::getCompensationPoints() const {
    return m_compensation_points;
}

int Team::getCompensationStrength() const {
    return m_compensation_strength;
}

void Team::addCompensationPoints(int points) {
    m_compensation_points += points;
}

void Team::addCompensationStrength(int strength) {
    m_compensation_strength += strength;
}

int Team::getID() const {
    return teamID;
}

bool Team::isGoalKeeperExists() const {
    if (m_goalKeeper_exist > 0){
        return true;
    }
    return false;
}

Player *Team::findPlayerByKey(int key) {
    return m_dict_of_players_in_team_by_key.find(key);
}

StatusType Team::add_player_in_team(int playerID, Player *pl){
    StatusType ans = m_dict_of_players_in_team.insert(playerID, pl);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    ans = m_dict_of_players_in_team_by_key.insert(playerID, pl);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    if (m_top_scorer_of_team == nullptr) {
        m_top_scorer_of_team = pl;
    }
    else {
        if (*m_top_scorer_of_team < *pl) {
            m_top_scorer_of_team = pl;
        }
    }
    m_number_of_players += 1;
    addStrength(pl->getGoals() - pl->getCards());
    if (pl->isGk()){
        m_goalKeeper_exist += 1;
    }
    pl->addGamesPlayed(-m_games_played);
    return ans;
}

StatusType Team::remove_player_in_team(int playerID, Player* pl){
    if (!m_dict_of_players_in_team.isExist(playerID, pl)){
        return StatusType::FAILURE;
    }
    int player_strength = pl->getCards() - pl->getGoals();
    bool is_player_gk = pl->isGk();
    bool is_top = (m_top_scorer_of_team == pl);
    Player* father = m_dict_of_players_in_team.findClosestLeft(pl);
    StatusType ans = m_dict_of_players_in_team.remove(playerID, pl);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    ans = m_dict_of_players_in_team_by_key.remove(playerID, pl);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    if (is_top){
        m_top_scorer_of_team = father;
    }
    m_number_of_players -= 1;
    addStrength(player_strength);
    if (is_player_gk){
        m_goalKeeper_exist -= 1;
    }
    return ans;
}

int Team::getTopScorerInTeam() const {
    return m_top_scorer_of_team->getPlayerId();
}

int *Team::getAllPlayersInTeam() {
    return m_dict_of_players_in_team.inorderNodesByKey();
}
bool operator!=(const Team& v1, const Team& v2){
    return !(v1 == v2);
}
bool operator<(const Team& v1, const Team& v2){
    return v2 > v1;
}

Team operator-(const Team& v1, const Team& v2){
    return Team(v1) -= v2;
}
Team &Team::operator-=(const Team &other) {
    return *this;
}

bool  Team::operator/(const Team &other) const {
    return true;
}

void Team::setClosestLeft(Team *other) {

}

void Team::setClosestRight(Team *other) {

}

Team *Team::getClosestLeft() {
    return nullptr;
}

Team *Team::getClosestRight() {
    return nullptr;
}

