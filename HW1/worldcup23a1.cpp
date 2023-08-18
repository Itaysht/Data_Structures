#include "worldcup23a1.h"

world_cup_t::world_cup_t(): m_dict_of_teams(Dictionary<int, Team*>(true, false)),
                            m_dict_of_active_teams(Dictionary<int, Team*>(true, false)),
                            m_dict_of_valid_teams(Dictionary<int, Team*>(true, false)),
                            m_dict_of_players_by_value(Dictionary<int, Player*>(false, true)),
                            m_dict_of_players_by_key(Dictionary<int, Player*>(true, false)),
                            m_top_scorer(nullptr),
                            m_teams_total(0), m_active_teams_total(0), m_valid_teams_total(0), m_players_total(0) {}

world_cup_t::~world_cup_t()
{
    m_dict_of_active_teams.destroyNodes();
    m_dict_of_valid_teams.destroyNodes();
    m_dict_of_teams.destroyNodesAndContent();
    m_dict_of_players_by_value.destroyNodes();
    m_dict_of_players_by_key.destroyNodesAndContent();
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if ((teamId <= 0) || (points < 0)){
        return StatusType::INVALID_INPUT;
    }
    try {
        Team *added_team = new Team(teamId, points);
        StatusType ans = m_dict_of_teams.insert(teamId, added_team);
        if (ans == StatusType::SUCCESS){
            m_teams_total += 1;
        }
        else{
            delete added_team;
        }
        return ans;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* curr = m_dict_of_teams.find(teamId);
    if (curr == nullptr || (curr->getID() != teamId) || (curr->numberOfPlayers() > 0)){
        return StatusType::FAILURE;
    }
    StatusType ans = m_dict_of_teams.remove(teamId, curr);
    if (ans == StatusType::SUCCESS){
        m_teams_total -= 1;
        delete curr;
    }
	return ans;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if ((playerId <= 0) || (teamId <= 0) || (gamesPlayed < 0) || (goals < 0) || (cards < 0)){
        return StatusType::INVALID_INPUT;
    }
    if ((gamesPlayed == 0) && ((cards > 0) || (goals > 0))){
        return StatusType::INVALID_INPUT;
    }
    try{
        Team* temp_team2 = m_dict_of_teams.find(teamId);
        if (temp_team2 == nullptr || temp_team2->getID() != teamId){
            return StatusType::FAILURE;
        }
        Player* temp_player = new Player(playerId, teamId, goals, cards, gamesPlayed, goalKeeper);
        StatusType ans1 = m_dict_of_players_by_key.insert(playerId, temp_player);
        if (ans1 != StatusType::SUCCESS){
            delete temp_player;
            return ans1;
        }

        ans1 = m_dict_of_players_by_value.insert(playerId, temp_player);
        if (ans1 != StatusType::SUCCESS){
            delete temp_player;
            return ans1;
        }

        Team* temp_team = m_dict_of_teams.find(teamId);
        if (temp_team == nullptr || temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        ans1 = temp_team->add_player_in_team(playerId, temp_player);
        if (ans1 != StatusType::SUCCESS){
            return ans1;
        }
        if (temp_team->numberOfPlayers() == 1){
            ans1 = m_dict_of_active_teams.insert(teamId, temp_team);
            if (ans1 != StatusType::SUCCESS){
                return ans1;
            }
            m_active_teams_total += 1;
        }
        if (temp_team->isValidTeam()){
            if (!(m_dict_of_valid_teams.isExist(teamId))){
                ans1 = m_dict_of_valid_teams.insert(teamId, temp_team);
                if (ans1 != StatusType::SUCCESS){
                    return ans1;
                }
                m_valid_teams_total += 1;
            }
        }
        if (m_top_scorer == nullptr){
            m_top_scorer = temp_player;
        }
        else{
            if (*m_top_scorer < *temp_player){
                m_top_scorer = temp_player;
            }
        }
        m_players_total += 1;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Player* temp_player = m_dict_of_players_by_key.find(playerId);
    if (temp_player == nullptr || temp_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    if (temp_player == m_top_scorer){
        m_top_scorer = temp_player->getClosestLeft();
    }
    int player_team_id = temp_player->getTeamID();
    StatusType ans = m_dict_of_players_by_value.remove(playerId, temp_player);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    StatusType ans2 = m_dict_of_players_by_key.remove(playerId, temp_player);
    if (ans2 != StatusType::SUCCESS){
        return ans2;
    }
    Team* temp_team = m_dict_of_active_teams.find(player_team_id);
    ans = temp_team->remove_player_in_team(playerId, temp_player);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    if (!(temp_team->isValidTeam())){
        if (m_dict_of_valid_teams.isExist(temp_team->getID())){
            m_dict_of_valid_teams.remove(temp_team->getID(), temp_team);
            m_valid_teams_total -= 1;
        }
    }
    if (temp_team->numberOfPlayers() == 0){
        m_dict_of_active_teams.remove(temp_team->getID(), temp_team);
        m_active_teams_total -= 1;
    }
    m_players_total -= 1;
    delete temp_player;
    return ans;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if ((playerId <= 0) || (gamesPlayed < 0) || (scoredGoals < 0) || (cardsReceived < 0)){
        return StatusType::INVALID_INPUT;
    }
	Player* temp_player = m_dict_of_players_by_key.find(playerId);
    if (temp_player == nullptr || temp_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    Team* temp_team = m_dict_of_active_teams.find(temp_player->getTeamID());
    temp_team->remove_player_in_team(playerId, temp_player);
    m_dict_of_players_by_value.remove(playerId, temp_player);
    if (temp_player == m_top_scorer){
        m_top_scorer = temp_player->getClosestLeft();
    }
    temp_player->addGoals(scoredGoals);
    temp_player->addGamesPlayed(gamesPlayed+temp_team->getGamesPlayed());
    temp_player->addCards(cardsReceived);
    temp_team->add_player_in_team(playerId, temp_player);
    m_dict_of_players_by_value.insert(playerId, temp_player);
    if (m_top_scorer == nullptr){
        m_top_scorer = temp_player;
    }
    else{
        if (*m_top_scorer < *temp_player){
            m_top_scorer = temp_player;
        }
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2)){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_dict_of_teams.find(teamId1);
    Team* team2 = m_dict_of_teams.find(teamId2);
    if (team1 == nullptr || team2 == nullptr || (team1->getID() != teamId1) ||
    (team2->getID() !=teamId2) || (!(team2->isValidTeam())) || (!(team1->isValidTeam()))){
        return StatusType::FAILURE;
    }
    if (*team1 < *team2){
        team2->addPoints(3);
    }
    else{
        if (*team1 > *team2){
            team1->addPoints(3);
        }
        else{
            team1->addPoints(1);
            team2->addPoints(1);
        }
    }
    team1->addGamesPlayed(1);
    team2->addGamesPlayed(1);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Player* pl = m_dict_of_players_by_key.find(playerId);
    if (pl == nullptr || pl->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    int number_of_games_in_team = m_dict_of_active_teams.find(pl->getTeamID())->getGamesPlayed();
	return number_of_games_in_team + pl->getGamesPlayed();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team_curr = m_dict_of_teams.find(teamId);
    if (team_curr == nullptr || team_curr->getID() != teamId){
        return StatusType::FAILURE;
    }
	return team_curr->getPoints();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2) || (newTeamId <= 0)){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_dict_of_teams.find(teamId1);
    Team* team2 = m_dict_of_teams.find(teamId2);
    if (team1 == nullptr || team2 == nullptr || (team1->getID() != teamId1) ||
       (team2->getID() != teamId2)){
        return StatusType::FAILURE;
    }
    Team* temp_team = m_dict_of_teams.find(newTeamId);
    if (temp_team->getID() == newTeamId){
        if (teamId1 == newTeamId){
            if (team2->isValidTeam()){
                m_dict_of_valid_teams.remove(teamId2, team2);
                m_valid_teams_total -= 1;
            }
            team1->move_all_players(team2);
            if (m_dict_of_active_teams.isExist(teamId2)){
                m_dict_of_active_teams.remove(teamId2, team2);
                m_active_teams_total -= 1;
            }
            if (team1->numberOfPlayers() > 0){m_dict_of_active_teams.insert(teamId1, team1);m_active_teams_total+=1;}
            if (team1->isValidTeam()){
                if (!(m_dict_of_valid_teams.isExist(teamId1))){
                    m_dict_of_valid_teams.insert(teamId1, team1);
                    m_valid_teams_total += 1;
                }
            }
            m_dict_of_teams.remove(teamId2, team2);
            m_teams_total -= 1;
            team1->addPoints(team2->getPoints());
            delete team2;
        }
        else{
            if (teamId2 == newTeamId){
                if (team1->isValidTeam()){
                    m_dict_of_valid_teams.remove(teamId1, team1);
                    m_valid_teams_total -= 1;
                }
                team2->move_all_players(team1);
                if (m_dict_of_active_teams.isExist(teamId1)){
                    m_dict_of_active_teams.remove(teamId1, team1);
                    m_active_teams_total -= 1;
                }
                if (team2->numberOfPlayers() > 0){m_dict_of_active_teams.insert(teamId2, team2);m_active_teams_total+=1;}
                if (team2->isValidTeam()){
                    if (!(m_dict_of_valid_teams.isExist(teamId2))){
                        m_dict_of_valid_teams.insert(teamId2, team2);
                        m_valid_teams_total += 1;
                    }
                }
                m_dict_of_teams.remove(teamId1, team1);
                m_teams_total -= 1;
                team2->addPoints(team1->getPoints());
                delete team1;
            }
            else{
                return StatusType::FAILURE;
            }
        }
        return StatusType::SUCCESS;
    }
    try {
        Team *added_team = new Team(newTeamId, team1->getPoints()+team2->getPoints());
        StatusType ans = m_dict_of_teams.insert(newTeamId, added_team);
        if (ans == StatusType::SUCCESS){
            m_teams_total += 1;
        }
        else{
            delete added_team;
            return ans;
        }
        if (team2->isValidTeam()){
            m_dict_of_valid_teams.remove(teamId2, team2);
            m_valid_teams_total -= 1;
        }
        if (team1->isValidTeam()){
            m_dict_of_valid_teams.remove(teamId1, team1);
            m_valid_teams_total -= 1;
        }
        added_team->move_all_players(team1);
        added_team->move_all_players(team2);
        if (added_team->numberOfPlayers() > 0){
            StatusType ans2 = m_dict_of_active_teams.insert(newTeamId, added_team);
            if (ans2 != StatusType::SUCCESS){
                return ans2;
            }
            m_active_teams_total += 1;
        }
        if (added_team->isValidTeam()){
            if (!(m_dict_of_valid_teams.isExist(newTeamId))){
                m_dict_of_valid_teams.insert(newTeamId, added_team);
                m_valid_teams_total += 1;
            }
        }
        if (m_dict_of_active_teams.isExist(teamId1)){
            m_dict_of_active_teams.remove(teamId1, team1);
            m_active_teams_total -= 1;
        }
        if (m_dict_of_active_teams.isExist(teamId2)){
            m_dict_of_active_teams.remove(teamId2, team2);
            m_active_teams_total -= 1;
        }
        m_dict_of_teams.remove(teamId1, team1);
        m_dict_of_teams.remove(teamId2, team2);
        m_teams_total -= 2;
        delete team1;
        delete team2;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_active_teams.find(teamId);
        if (temp_team == nullptr || temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        return temp_team->getTopScorerInTeam();
    }
    if (m_players_total == 0){
        return StatusType::FAILURE;
    }
	return m_top_scorer->getPlayerId();
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_teams.find(teamId);
        if ((temp_team == nullptr) || (temp_team->getID() != teamId)){
            return StatusType::FAILURE;
        }
        return temp_team->numberOfPlayers();
    }
    return m_players_total;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if ((output == nullptr) || (teamId == 0)){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_active_teams.find(teamId);
        if (temp_team == nullptr || temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        int* answer = temp_team->getAllPlayersInTeam();
        int num_of_players = temp_team->numberOfPlayers();
        int i = 0;
        while (i < num_of_players){
            output[i] = answer[i];
            i++;
        }
        delete[] answer;
    }
    else{
        if (m_players_total == 0){
            return StatusType::FAILURE;
        }
        int* answer = m_dict_of_players_by_value.inorderNodesByKey();
        int i = 0;
        while (i < m_players_total){
            output[i] = answer[i];
            i++;
        }
        delete[] answer;
    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if ((playerId <= 0) || (teamId <= 0)){
        return StatusType::INVALID_INPUT;
    }
    if ((m_players_total == 1) || (m_players_total == 0)){
        return StatusType::FAILURE;
    }
	Team* curr_team = m_dict_of_active_teams.find(teamId);
    if ((curr_team == nullptr) || (curr_team->getID() != teamId)) {
        return StatusType::FAILURE;
    }
    Player* curr_player = curr_team->findPlayerByKey(playerId);
    if ((curr_player == nullptr) || (curr_player->getPlayerId() != playerId)){
        return StatusType::FAILURE;
    }
    if (curr_player->getClosestLeft() == nullptr) {
        return curr_player->getClosestRight()->getPlayerId();
    }
    if (curr_player->getClosestRight() == nullptr) {
        return curr_player->getClosestLeft()->getPlayerId();
    }
    if ((*curr_player->getClosestLeft() - *curr_player) / (*curr_player->getClosestRight() - *curr_player)){
        return curr_player->getClosestLeft()->getPlayerId();
    }
	return curr_player->getClosestRight()->getPlayerId();
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if ((minTeamId < 0) || (maxTeamId < 0) || (maxTeamId < minTeamId)){
        return StatusType::INVALID_INPUT;
    }
    Team** ans = m_dict_of_valid_teams.inorderNodesByValueBetween(minTeamId, maxTeamId);
    Team** begin = ans;
    int counter = m_dict_of_valid_teams.getCounterForArray();
    if (counter == 0){
        delete[] ans;
        return StatusType::FAILURE;
    }
    int valid_counter = counter;

    try {
        Team **validTeams = new Team *[valid_counter]; //building new array which will contain all valids
        Team **decreasing_valid_teams = nullptr;
        int j = 0, temp_valid_counter = 0;
        for (int i = 0; i < counter; i++) {
            if ((*begin) != nullptr) {
                validTeams[j] = *begin;
                j++;
            }
            begin++;
        }
        delete[] ans;
        if (valid_counter == 1) {
            int winner = validTeams[0]->getID();
            delete[] validTeams;
            return winner;
        }
        while (valid_counter != 1) {
            temp_valid_counter = valid_counter;
            for (int i = 0; i < valid_counter - 1; i += 2) {
                if (((*(validTeams[i])) > ((*(validTeams[i + 1])))) ||
                    ((((*(validTeams[i])) == ((*(validTeams[i + 1]))))) &&
                     (validTeams[i]->getID() > (validTeams[i + 1]->getID())))) {
                    validTeams[i]->addPoints(validTeams[i + 1]->getPoints() + 3);
                    validTeams[i]->addCompensationPoints((validTeams[i + 1]->getPoints() * -1) - 3);
                    validTeams[i]->addStrength(validTeams[i + 1]->getStrength());
                    validTeams[i]->addCompensationStrength(validTeams[i + 1]->getStrength() * -1);
                    validTeams[i + 1]->addPoints(validTeams[i + 1]->getCompensationPoints());
                    validTeams[i + 1]->addStrength(validTeams[i + 1]->getCompensationStrength());
                    validTeams[i + 1]->addCompensationPoints((-1) * validTeams[i + 1]->getCompensationPoints());
                    validTeams[i + 1]->addCompensationStrength((-1) * validTeams[i + 1]->getCompensationStrength());
                    validTeams[i + 1] = nullptr;
                } else {
                    validTeams[i + 1]->addPoints(validTeams[i]->getPoints() + 3);
                    validTeams[i + 1]->addCompensationPoints((validTeams[i]->getPoints() * -1) - 3);
                    validTeams[i + 1]->addStrength(validTeams[i]->getStrength());
                    validTeams[i + 1]->addCompensationStrength(validTeams[i]->getStrength() * -1);
                    validTeams[i]->addPoints(validTeams[i]->getCompensationPoints());
                    validTeams[i]->addStrength(validTeams[i]->getCompensationStrength());
                    validTeams[i]->addCompensationPoints((-1) * validTeams[i]->getCompensationPoints());
                    validTeams[i]->addCompensationStrength((-1) * validTeams[i]->getCompensationStrength());
                    validTeams[i] = nullptr;
                }
                temp_valid_counter--;
            }
            decreasing_valid_teams = new Team *[temp_valid_counter];
            begin = validTeams;
            j = 0;
            for (int i = 0; i < valid_counter; i++) {
                if ((*begin) != nullptr) {
                    decreasing_valid_teams[j] = *begin;
                    j++;
                }
                begin++;
            }
            delete[] validTeams;

            //releasing certain values in validTeams will release also in decreasing_valid_teams
            valid_counter = temp_valid_counter;
            validTeams = decreasing_valid_teams;
        }
        validTeams[0]->addPoints(validTeams[0]->getCompensationPoints());
        validTeams[0]->addStrength(validTeams[0]->getCompensationStrength());
        validTeams[0]->addCompensationPoints((-1) * validTeams[0]->getCompensationPoints());
        validTeams[0]->addCompensationStrength((-1) * validTeams[0]->getCompensationStrength());
        int winner = validTeams[0]->getID();
        delete[] decreasing_valid_teams;
        return winner;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
}