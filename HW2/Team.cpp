#include "Team.h"

Team::Team(int teamID) : teamID(teamID), m_points(0), m_total_ability(0),
                         m_games_played(0), m_number_of_players(0), is_valid(false),
                         m_team_spirit(new permutation_t(permutation_t::invalid())), first_player(nullptr),
                         last_player(nullptr), balance(0) {}


Team::~Team() {
    delete m_team_spirit;
}

int Team::getTeamValue() const {
    return m_total_ability + m_points;
}

int Team::getBalanace() const {
    return balance;
}

void Team::setBalance(int bal) {
    balance = bal;
}

int Team::getGamesPlayed() const {
    return m_games_played;
}

bool Team::isValidTeam() const {
    return is_valid;
}

void Team::addGamesPlayed(int games_played) {
    m_games_played += games_played;
}

int Team::getPoints() const {
    return m_points;
}

int Team::getTotalAbility() const {
    return m_total_ability;
}

void Team::addPoints(int points) {
    m_points += points;
}

bool Team::operator>(const Team &other) const {
    if (getTotalAbility() > other.getTotalAbility()) {
        return true;
    }

    if (getTotalAbility() == other.getTotalAbility() && (getID() > other.getID())) {
        return true;
    }
    return false;
}

bool operator==(const Team &v1, const Team &v2) {
    return (v1.getTotalAbility() == v2.getTotalAbility()) && (v1.getID() == v2.getID());
}

int Team::getNumberOfPlayers() const {
    return m_number_of_players;
}

void Team::addNumberOfPlayers(int added) {
    m_number_of_players += added;
}

void Team::addTotalAbility(int ability) {
    m_total_ability += ability;
}

int Team::getID() const {
    return teamID;
}

void Team::setID(int id) {
    teamID = id;
}

bool operator!=(const Team &v1, const Team &v2) {
    return !(v1 == v2);
}

bool operator<(const Team &v1, const Team &v2) {
    return v2 > v1;
}


void Team::addGoalKeeper() {
    is_valid = true;
}

permutation_t Team::getTeamSpirit() const {
    return *m_team_spirit;
}

void Team::updateTeamSpirit(permutation_t *new_spirit) {
    if (not m_team_spirit->isvalid()) {
        delete m_team_spirit;
        m_team_spirit = new permutation_t(*new_spirit);
    } else {
        (*m_team_spirit) = (*m_team_spirit) * (*new_spirit);
    }
}

int Team::getTeamSpiritStrength() const {
    return m_team_spirit->strength();
}

Player *Team::getFirstPlayer() const {
    return first_player;
}

Player *Team::getLastPlayer() const {
    return last_player;
}

void Team::setFirstPlayer(Player *f_ply) {
    first_player = f_ply;
}

void Team::setLastPlayer(Player *l_ply) {
    last_player = l_ply;
}

Team::MatchResult playMatchResult(Team *first_team, Team *second_team) {
    if (first_team->getTeamValue() > second_team->getTeamValue()) {
        return Team::MatchResult::FIRST_TEAM_WON_BY_VALUE;
    }

    if (first_team->getTeamValue() < second_team->getTeamValue()) {
        return Team::MatchResult::SECOND_TEAM_WON_BY_VALUE;
    }

    if (first_team->getTeamSpiritStrength() > second_team->getTeamSpiritStrength()) {
        return Team::MatchResult::FIRST_TEAM_WON_BY_SPIRIT;
    }

    if (first_team->getTeamSpiritStrength() < second_team->getTeamSpiritStrength()) {
        return Team::MatchResult::SECOND_TEAM_WON_BY_SPIRIT;
    }

    return Team::MatchResult::TIE;
}
