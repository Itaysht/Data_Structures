#include "worldcup23a2.h"

const int MATCH_WIN_POINTS = 3;
const int MATCH_TIE_POINTS = 1;

world_cup_t::world_cup_t() : m_teams_dictionary(RankedTree(true)),
                             m_all_players_dictionary(Uptrees()),
                             m_teams_by_ability(RankedTree(false)),
                             m_number_of_teams(0) {}

world_cup_t::~world_cup_t() {
    m_teams_by_ability.destroyNodes();
    m_teams_dictionary.destroyNodesAndContent();
}

StatusType world_cup_t::add_team(int teamId) {
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        Team *new_team = new Team(teamId);

        StatusType insert_status = m_teams_dictionary.insert(teamId, new_team);

        if (insert_status != StatusType::SUCCESS) {
            delete new_team;
            return insert_status;
        }
        m_number_of_teams += 1;
        insert_status = m_teams_by_ability.insert(teamId, new_team);
        return insert_status;
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId) {
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Team *removed_team = m_teams_dictionary.find(teamId);

    if (removed_team == nullptr) {
        return StatusType::FAILURE;
    }

    Player *first_player_of_removed_team = removed_team->getFirstPlayer();
    if (first_player_of_removed_team != nullptr) {
        int first_player_id_of_removed_team = first_player_of_removed_team->getPlayerId();
        m_all_players_dictionary.removeTeamFromPlayer(first_player_id_of_removed_team);
    }

    if (StatusType::SUCCESS != m_teams_dictionary.remove(removed_team)) {
        return StatusType::FAILURE;
    }
    m_number_of_teams -= 1;
    m_teams_by_ability.remove(removed_team);
    delete removed_team;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {

    if (playerId <= 0 or teamId <= 0 or not spirit.isvalid() or gamesPlayed < 0 or cards < 0) {
        return StatusType::INVALID_INPUT;
    }

    if (m_all_players_dictionary.findPlayer(playerId) != nullptr or m_teams_dictionary.find
            (teamId) == nullptr) {
        return StatusType::FAILURE;
    }

    try {
        Team *new_player_team = m_teams_dictionary.find(teamId);
        permutation_t *temp_spirit = new permutation_t(spirit);
        Player *new_player = new Player(playerId, teamId, temp_spirit, gamesPlayed, ability,
                                        cards, goalKeeper);
        m_all_players_dictionary.insert(new_player, new_player_team);
        m_teams_by_ability.remove(new_player_team);
        new_player_team->addTotalAbility(ability);
        permutation_t *added_spirit = new permutation_t(*temp_spirit);
        new_player_team->updateTeamSpirit(added_spirit);
        delete added_spirit;
        new_player_team->addNumberOfPlayers(1);
        if (goalKeeper) {
            new_player_team->addGoalKeeper();
        }
        m_teams_by_ability.insert(teamId, new_player_team);
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {
    if (teamId1 <= 0 or teamId2 <= 0 or teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }

    Team *first_team = m_teams_dictionary.find(teamId1);
    Team *second_team = m_teams_dictionary.find(teamId2);
    if (first_team == nullptr or second_team == nullptr or not first_team->isValidTeam() or not
            second_team->isValidTeam()) {
        return StatusType::FAILURE;
    }

    Team::MatchResult match_result = playMatchResult(first_team, second_team);

    switch (match_result) {
        case Team::MatchResult::TIE:
            first_team->addPoints(MATCH_TIE_POINTS);
            second_team->addPoints(MATCH_TIE_POINTS);
            break;

        case Team::MatchResult::FIRST_TEAM_WON_BY_VALUE:
        case Team::MatchResult::FIRST_TEAM_WON_BY_SPIRIT:
            first_team->addPoints(MATCH_WIN_POINTS);
            break;

        case Team::MatchResult::SECOND_TEAM_WON_BY_VALUE:
        case Team::MatchResult::SECOND_TEAM_WON_BY_SPIRIT:
            second_team->addPoints(MATCH_WIN_POINTS);
            break;
    }
    first_team->addGamesPlayed(1);
    second_team->addGamesPlayed(1);
    first_team->setBalance(first_team->getBalanace() + 1);
    second_team->setBalance(second_team->getBalanace() + 1);
    m_all_players_dictionary.addGamesPlayedOnlyToFirst(first_team->getFirstPlayer());
    m_all_players_dictionary.addGamesPlayedOnlyToFirst(second_team->getFirstPlayer());

    return static_cast<const int>(match_result);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Player *player = m_all_players_dictionary.findPlayer(playerId);
    if (player == nullptr) {
        return StatusType::FAILURE;
    }

    Team *team = m_all_players_dictionary.findTeam(playerId, false);

    int team_games_played;
    if (team == nullptr) {
        team_games_played = m_all_players_dictionary.getGamesPlayedDeletedTeam(playerId);
    } else {
        team_games_played = team->getGamesPlayed();
    }

    int games_player_from_node = m_all_players_dictionary.playerGamesPlayedNode(playerId);
    if (m_all_players_dictionary.isFirstOfSomeTeam(playerId)) {
        return player->getGamesPlayed() + team_games_played;
    }
    return player->getGamesPlayed() + team_games_played + games_player_from_node;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards) {
    if (playerId <= 0 or cards < 0) {
        return StatusType::INVALID_INPUT;
    }

    Player *player = m_all_players_dictionary.findPlayer(playerId);
    if (player == nullptr or m_all_players_dictionary.findTeam(playerId, false) == nullptr) {
        return StatusType::FAILURE;
    }

    player->addCards(cards);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Player *player = m_all_players_dictionary.findPlayer(playerId);
    if (player == nullptr) {
        return StatusType::FAILURE;
    }

    return player->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Team *team = m_teams_dictionary.find(teamId);
    if (team == nullptr) {
        return StatusType::FAILURE;
    }

    return team->getPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i) {
    if ((i < 0) || (m_number_of_teams <= i)) {
        return StatusType::FAILURE;
    }
    return m_teams_by_ability.find_ith(i);
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId) {
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (m_all_players_dictionary.findPlayer(playerId) == nullptr) {
        return StatusType::FAILURE;
    }
    permutation_t *ans = new permutation_t(m_all_players_dictionary.getPartialPermutation(playerId));
    if (!ans->isvalid()) {
        delete ans;
        return StatusType::FAILURE;
    }
    permutation_t return_ans = *ans;
    delete ans;
    return return_ans;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
    if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2)) {
        return StatusType::INVALID_INPUT;
    }
    Team *team1 = m_teams_dictionary.find(teamId1);
    Team *team2 = m_teams_dictionary.find(teamId2);
    if ((team1 == nullptr) || (team2 == nullptr)) {
        return StatusType::FAILURE;
    }
    if (team2->getNumberOfPlayers() == 0) {
        m_teams_dictionary.remove(team2);
        m_teams_by_ability.remove(team2);
        m_number_of_teams -= 1;
        delete team2;
        return StatusType::SUCCESS;
    }
    if (team1->getNumberOfPlayers() == 0) {
        m_teams_dictionary.remove(team2);
        m_teams_by_ability.remove(team2);
        m_all_players_dictionary.upTreeUnion(team1, team2);
        m_teams_dictionary.remove(team1);
        m_teams_by_ability.remove(team1);
        m_number_of_teams -= 1;
        m_teams_dictionary.insert(team2->getID(), team2); //sorted by id
        m_teams_by_ability.insert(team2->getID(), team2);
        delete team1;
        return StatusType::SUCCESS;
    }
    m_teams_by_ability.remove(team1);
    m_all_players_dictionary.upTreeUnion(team1, team2);
    team1->addNumberOfPlayers(team2->getNumberOfPlayers());
    team1->addTotalAbility(team2->getTotalAbility());
    team1->setBalance(team2->getBalanace());
    permutation_t *added_team_spirit = new permutation_t(team2->getTeamSpirit());
    team1->updateTeamSpirit(added_team_spirit);
    delete added_team_spirit;
    if (team2->isValidTeam()) {
        team1->addGoalKeeper();
    }
    m_teams_by_ability.insert(team1->getID(), team1);
    m_number_of_teams -= 1;
    m_teams_dictionary.remove(team2);
    m_teams_by_ability.remove(team2);
    delete team2;
    return StatusType::SUCCESS;
}
