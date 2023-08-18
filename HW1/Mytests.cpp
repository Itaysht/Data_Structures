//
// Created by itayi on 21/11/2022.
//
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <random>

#include "Dictionary.h"
#include "Player.h"
#include "worldcup23a1.h"

#define REQUIRE(x) std::cout << (x)


const int MAX_LINE_LENGTH = 75;

void printFunctionName(std::string str) {
    std::string out;
    out += str[0] - 32;
    for (int i = 1; i < str.length(); i++) {
        if (str[i]>='A' && str[i]<='Z') {
            str[i]=str[i]+32;
            if (i != 0) {
                out += " ";
            }
            out += str[i];
        }
        else {
            out += str[i];
        }
    }
    std::cout << "Running test: " << out << std::string(MAX_LINE_LENGTH - out.length(), ' ');
}
/*
bool findInEmptyDictionaryByKey() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    return dict.find(1) == nullptr;
}

bool findInEmptyDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    return dict.find(1) == nullptr;
}

bool findInOneElementDictionaryByKey() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(1) == &element;
}

bool findInOneElementDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(1) == &element;
}

bool findMissingElementInOneElementDictionaryByKey() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(0) == &element;
}

bool findMissingElementInOneElementDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(0) == &element;
}

void testSingleRrRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {1,2,3};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleLlRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {3,2,1};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleRlRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {1,3,2};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleLrRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {3,1,2};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleRrRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {1,2,3};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleLlRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {3,2,1};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleRlRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {1,3,2};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleLrRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {3,1,2};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testMultipleRotationsByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    const int length = 15;
    int elements[length];
    for (int i = 0; i < length; i++) {
        elements[i] = i + 1;
    }
    for (int i = 0; i < length; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

bool findElementAfterRemoval() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    dict.remove(element, &element);
    return dict.find(element) == nullptr;
}

void testSingleRrRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {2,1,3,4};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 1);
    dict.print();
}

void testSingleLlRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {3,4,2,1};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(4, elements + 1);
    dict.print();
}

void testSingleLrRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {3,4,1,2};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(4, elements + 1);
    dict.print();
}

void testSingleRlRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {2,1,4,3};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 1);
    dict.print();
}

void testRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[5] = {2,1,4,3,5};
    for (int i = 0; i < 5; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(2, elements);
    dict.print();
}

void testMultiplyRotationsAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[12] = {5,2,8,1,4,7,10,6,9,11,3,12};
    for (int i = 0; i < 12; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 3);
    dict.print();
}
*/
bool constructorCrush() {
    printFunctionName(__FUNCTION__);
    try {
        world_cup_t game = world_cup_t();
    }
    catch(...){
        return false;
    }
    return true;
}

bool addTeamInvalidInputId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(0, 1) == StatusType::INVALID_INPUT;
}

bool addTeamInvalidInputPoints() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(1, -1) == StatusType::INVALID_INPUT;
}

bool addTeamSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(1, 0) == StatusType::SUCCESS;
}

bool addTeamAlreadyExistingTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.add_team(1, 1) == StatusType::FAILURE;
}

bool removeTeamSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(1) == StatusType::SUCCESS;
}

bool removeTeamInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(0) == StatusType::INVALID_INPUT;
}

bool removeTeamTeamIdDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(2) == StatusType::FAILURE;
}

bool removeTeamNotEmpty() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_team(1) == StatusType::FAILURE;
}

bool removeTeamAfterLastPlayerRemoval() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    return game.remove_team(1) == StatusType::SUCCESS;
}

bool addPlayerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, 1, 1, false) == StatusType::SUCCESS;
}

bool addPlayerInvalidPlayerId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(0, 1, 1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 0, 1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGamesPlayed() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, -1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGoals() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, -1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidCards() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, 1, -1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidCardsWithoutGames() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 0, 0, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGoalsWithoutGames() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 0, 1, 0, false) == StatusType::INVALID_INPUT;
}

bool addPlayerAlreadyExistsInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 2, 3, 4, false);
    return game.add_player(1, 1, 1, 1, 1, false) == StatusType::FAILURE;
}

bool addPlayerAlreadyExistsInAnotherTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1, 1, 2, 3, 4, false);
    return game.add_player(1, 2, 1, 1, 1, false) == StatusType::FAILURE;
}

bool addPlayerTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 2, 1, 1, 1, false) == StatusType::FAILURE;
}

bool removePlayerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_player(1) == StatusType::SUCCESS;
}

bool removePlayerInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.remove_player(0) == StatusType::INVALID_INPUT;
}

bool removePlayerDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_player(2) == StatusType::FAILURE;
}

bool updatePlayerStatsInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(0, 1, 1, 1) == StatusType::INVALID_INPUT;
}

bool updatePlayerStatsInvalidGamesPlayed() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(1, -1, 1, 1) == StatusType::INVALID_INPUT;
}

bool updatePlayerStatsInvalidGoals() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(1, 1, -1, 1) == StatusType::INVALID_INPUT;
}

bool updatePlayerStatsInvalidCards() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(1, 1, 1, -1) == StatusType::INVALID_INPUT;
}

bool updatePlayerStatsPlayerDoesntExists() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(2, 1, 1, 1) == StatusType::FAILURE;
}

bool updatePlayerStatsSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.update_player_stats(1, 1, 1, 1) == StatusType::SUCCESS;
}

bool playMatchInvalidFirstTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(0, 1) == StatusType::INVALID_INPUT;
}

bool playMatchInvalidSecondTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(1, 0) == StatusType::INVALID_INPUT;
}

bool playMatchSameTeamsId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(1, 1) == StatusType::INVALID_INPUT;
}

bool playMatchFirstTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(3, 1) == StatusType::FAILURE;
}

bool playMatchSecondTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(1, 3) == StatusType::FAILURE;
}

bool playMatchFirstTeamIsNotValid() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        if (i == 1) {
            game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
        }
    }
    return game.play_match(1, 2) == StatusType::FAILURE;
}

bool playMatchSecondTeamIsNotValid() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        if (i == 0) {
            game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
        }
    }
    return game.play_match(1, 2) == StatusType::FAILURE;
}

bool playMatchSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.play_match(1, 2) == StatusType::SUCCESS;
}

bool getNumPlayedGamesInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.get_num_played_games(0).status() == StatusType::INVALID_INPUT;
}

bool getNumPlayedGamesPlayerDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.get_num_played_games(1).status() == StatusType::FAILURE;
}

bool getNumPlayedGamesSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.get_num_played_games(1).status() == StatusType::SUCCESS;
}

bool getNumPlayedGamesTestOutValue() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.get_num_played_games(1).ans() == 1;
}

bool getNumPlayedGamesAfterUpdate() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.update_player_stats(1, 1, 1, 1);
    return game.get_num_played_games(1).ans() == 2;
}

bool getNumPlayedGamesAfterMatch() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_num_played_games(1).ans() == 1;
}

bool getTeamPointsInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.get_team_points(0).status() == StatusType::INVALID_INPUT;
}

bool getTeamPointsTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.get_team_points(1).status() == StatusType::FAILURE;
}

bool getTeamPointsSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.get_team_points(1).status() == StatusType::SUCCESS;
}

bool getTeamPointsTestOutValue() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,1);
    return game.get_team_points(1).ans() == 1;
}

bool getTeamPointsAfterMatchWin() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,1);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_team_points(1).ans() == 4;
}

bool getTeamPointsAfterMatchLoose() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,1);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_team_points(2).ans() == 0;
}

bool getTeamPointsAfterMatchTie() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_team_points(1).ans() == 1;
}

bool getTeamPointsAfterMatchWinByGoals() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 1, i, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_team_points(2).ans() == 3;
}

bool getTeamPointsAfterMatchWinByCards() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 1, 0, i, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1, 2);
    return game.get_team_points(1).ans() == 3;
}

bool uniteTeamsInvalidTeam1Id() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.unite_teams(0, 1, 1) == StatusType::INVALID_INPUT;
}

bool uniteTeamsInvalidTeam2Id() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.unite_teams(1, 0, 1) == StatusType::INVALID_INPUT;
}

bool uniteTeamsInvalidNewTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    return game.unite_teams(1, 2, 0) == StatusType::INVALID_INPUT;
}

bool uniteTeamsSameTeamsId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.unite_teams(1, 1, 2) == StatusType::INVALID_INPUT;
}

bool uniteTeamsTeam1DoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.unite_teams(2, 1, 3) == StatusType::FAILURE;
}

bool uniteTeamsTeam2DoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.unite_teams(1, 2, 3) == StatusType::FAILURE;
}

bool uniteTeamsNewTeamIdAlreadyExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_team(3,0);
    return game.unite_teams(1, 2, 3) == StatusType::FAILURE;
}

bool uniteTeamsSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    return game.unite_teams(1, 2, 1) == StatusType::SUCCESS;
}

bool uniteTeamsNewTeamPoints() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,1);
    game.add_team(2,2);
    game.unite_teams(1, 2, 3);
    return game.get_team_points(3).ans() == 3;
}

bool getTopScorerInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.get_top_scorer(0).status() == StatusType::INVALID_INPUT;
}

bool getTopScorerNoPlayers() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    return game.get_top_scorer(-1).status() == StatusType::FAILURE;
}

bool getTopScorerTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.remove_team(1);
    return game.get_top_scorer(1).status() == StatusType::FAILURE;
}

bool getTopScorerNoPlayersInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    return game.get_top_scorer(1).status() == StatusType::FAILURE;
}

bool getTopScorerTestValueInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 3, 1, false);
    game.add_player(3, 2, 1, 10, 1, false);
    return game.get_top_scorer(1).ans() == 2;
}

bool getTopScorerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.get_top_scorer(1).status() == StatusType::SUCCESS;
}

bool getTopScorerTestValueInAllTeams() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 3, 1, false);
    game.add_player(3, 2, 1, 10, 1, false);
    return game.get_top_scorer(-1).ans() == 3;
}

bool getAllPlayersCountInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.get_all_players_count(0).status() == StatusType::INVALID_INPUT;
}

bool getAllPlayersCountTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.get_all_players_count(2).status() == StatusType::FAILURE;
}

bool getAllPlayersCountSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.get_all_players_count(1).status() == StatusType::SUCCESS;
}

bool getAllPlayersCountInAllTeams() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1,1,1,1,1, false);
    game.add_player(2,2,1,1,1, false);
    game.add_player(3,1,1,1,1, false);
    game.remove_player(3);
    return game.get_all_players_count(-1).ans() == 2;
}

bool getAllPlayersCountInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1,1,1,1,1, false);
    game.add_player(2,2,1,1,1, false);
    game.add_player(3,1,1,1,1, false);
    game.remove_player(3);
    return game.get_all_players_count(1).ans() == 1;
}

bool getAllPlayersCountInTeamAfterUnite() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1,1,1,1,1, false);
    game.add_player(2,2,1,1,1, false);game.unite_teams(1, 2, 3);
    return game.get_all_players_count(3).ans() == 2;
}

bool getAllPlayersInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    int players_count = game.get_all_players_count(-1).ans();
    int players[players_count];
    return game.get_all_players(0, players) == StatusType::INVALID_INPUT;
}

bool getAllPlayersInvalidOutput() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.get_all_players(-1, nullptr) == StatusType::INVALID_INPUT;
}

bool getAllPlayersTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.remove_team(2);
    int players[1];
    return game.get_all_players(2, players) == StatusType::FAILURE;
}

bool getAllPlayersEmptyTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    int players_count = game.get_all_players_count(1).ans();
    int players[players_count];
    return game.get_all_players(1, players) == StatusType::FAILURE;
}

bool getAllPlayersNoPlayers() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    int players_count = game.get_all_players_count(-1).ans();
    int players[players_count];
    return game.get_all_players(-1, players) == StatusType::FAILURE;
}

bool getAllPlayersSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    int players_count = game.get_all_players_count(-1).ans();
    int players[players_count];
    return game.get_all_players(-1, players) == StatusType::SUCCESS;
}

bool getAllPlayersTestValueInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 2, 1, 1, 1, false);
    game.add_player(3, 1, 1, 1, 1, false);
    game.remove_player(1);
    int players_count = game.get_all_players_count(1).ans();
    int players[players_count];
    game.get_all_players(1, players);
    return players_count == 1 and players[0] == 3;
}

bool getAllPlayersTestValueInAllTeams() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 2, 1, 1, 1, false);
    game.add_player(3, 1, 1, 1, 1, false);
    game.remove_player(1);
    int players_count = game.get_all_players_count(-1).ans();
    int players[players_count];
    game.get_all_players(-1, players);
    return players_count == 2 and players[0] == 2 and players[1] == 3;
}

bool getAllPlayersTestPlayersOrder() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    for (int i = 1; i <= 10; i++) {
        game.add_team(i, 0);
    }

    const int REPETITIONS = 1000;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(1,10*REPETITIONS);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(1,10);

    int player_ids[REPETITIONS];
    int team_ids[REPETITIONS];

    for (int i = 0; i < REPETITIONS; i++) {
        player_ids[i] = dist1(rng);
        team_ids[i] = dist2(rng);
    }

    for (int i = 0; i < REPETITIONS; i++) {
        game.add_player(player_ids[i], team_ids[i], 1, 1, 1, false);
        if (i == 71) {
            int x = 1;
        }
        int players_count = game.get_all_players_count(-1).ans();
        int players[players_count];
        game.get_all_players(-1, players);

        for (int j = 0; j < players_count - 1; j++) {
            if (players[j+1] <= players[j]) {
                return false;
            }
        }
    }

    return true;
}

bool getClosestPlayerInvalidPlayerId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 1, 1, false);
    return game.get_closest_player(0, 1).status() == StatusType::INVALID_INPUT;
}

bool getClosestPlayerInvalidTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 1, 1, false);
    return game.get_closest_player(1, 0).status() == StatusType::INVALID_INPUT;
}

bool getClosestPlayerPlayerDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 1, 1, false);
    return game.get_closest_player(3, 1).status() == StatusType::FAILURE;
}

bool getClosestPlayerPlayerInWrongTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 2, 1, 1, 1, false);
    return game.get_closest_player(2, 1).status() == StatusType::FAILURE;
}

bool getClosestPlayerTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 1, 1, false);
    return game.get_closest_player(1, 2).status() == StatusType::FAILURE;
}

bool getClosestPlayerOnePlayer() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 2, 1, 1, 1, false);
    game.remove_player(2);
    return game.get_closest_player(1, 1).status() == StatusType::FAILURE;
}

bool getClosestPlayerMiddleSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 2, 1, false);
    game.add_player(3, 2, 1, 3, 1, false);
    return game.get_closest_player(2, 1).status() == StatusType::SUCCESS;
}

bool getClosestPlayerFirstSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 2, 1, false);
    game.add_player(3, 2, 1, 3, 1, false);
    return game.get_closest_player(1, 1).status() == StatusType::SUCCESS;
}

bool getClosestPlayerLastSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.add_player(2, 1, 1, 2, 1, false);
    game.add_player(3, 2, 1, 3, 1, false);
    return game.get_closest_player(3, 2).status() == StatusType::SUCCESS;
}

bool getClosestPlayerTestFromExample() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(21, 1, 1, 1, 20, false);
    game.add_player(25, 1, 1, 1, 20, false);
    game.add_player(3, 1, 1, 1, 5, false);
    game.add_player(4, 1, 1, 1, 1, false);
    game.add_player(5, 1, 1, 2, 5, false);
    game.add_player(6, 1, 1, 2, 4, false);
    game.add_player(24, 1, 1, 2, 3, false);
    game.add_player(7, 1, 1, 2, 2, false);
    game.add_player(8, 1, 1, 2, 1, false);
    game.add_player(9, 1, 1, 5, 30, false);
    game.add_player(10, 1, 1, 5, 29, false);
    game.add_player(11, 1, 1, 5, 28, false);
    game.add_player(12, 1, 1, 5, 27, false);
    game.add_player(51, 1, 1, 6, 40, false);
    game.add_player(52, 1, 1, 6, 40, false);
    game.add_player(53, 1, 1, 6, 40, false);
    game.add_player(54, 1, 1, 6, 10, false);
    game.add_player(60, 1, 1, 6, 5, false);
    game.add_player(70, 1, 1, 6, 5, false);
    game.add_player(100, 1, 1, 8, 6, false);
    game.add_player(80, 1, 1, 10, 7, false);
    game.add_player(90, 1, 1, 10, 7, false);
    return game.get_closest_player(21, 1).ans() == 25 and game.get_closest_player(25, 1).ans() ==
    21 and game.get_closest_player(3, 1).ans() == 4 and game.get_closest_player(4, 1).ans() == 3
    and game.get_closest_player(5, 1).ans() == 6 and game.get_closest_player(6, 1).ans() == 5 and
    game.get_closest_player(24, 1).ans() == 7 and game.get_closest_player(7, 1).ans() == 8 and
    game.get_closest_player(8, 1).ans() == 7 and game.get_closest_player(9, 1).ans() == 10 and
    game.get_closest_player(10, 1).ans() == 11 and game.get_closest_player(11, 1).ans() == 12 and
    game.get_closest_player(12, 1).ans() == 11 and game.get_closest_player(51, 1).ans() == 52 and
    game.get_closest_player(52, 1).ans() == 53 and game.get_closest_player(53, 1).ans() == 52 and
    game.get_closest_player(54, 1).ans() == 60 and game.get_closest_player(60, 1).ans() == 70 and
    game.get_closest_player(70, 1).ans() == 60 and game.get_closest_player(100, 1).ans() == 80
    and game.get_closest_player(80, 1).ans() == 90 and game.get_closest_player(90, 1).ans() == 80;
}

bool knockoutWinnerInvalidMinId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 1, 0, i, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.knockout_winner(-1, 2).status() == StatusType::INVALID_INPUT;
}

bool knockoutWinnerInvalidMaxId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 1, 0, i, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.knockout_winner(1, -2).status() == StatusType::INVALID_INPUT;
}

bool knockoutWinnerMinIdBiggerThanMax() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 1, 0, i, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    return game.knockout_winner(2, 1).status() == StatusType::INVALID_INPUT;
}

bool knockoutWinnerNoValidTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);

    for (int i = 1; i <= 9; i++) {
        game.add_player(i, 1, 1, 0, i, false);
    }
    game.add_player(10, 1, 0, 0, 0, true);

    for (int i = 1; i <= 11; i++) {
        game.add_player(i + 10, 2, 1, 0, i, false);
    }

    return game.knockout_winner(1, 2).status() == StatusType::FAILURE;
}

bool knockoutWinnerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i * 11, i + 1, 1, 0, i, false);
        }
        game.add_player(11 * (i + 1), i + 1, 0, 0, 0, true);
    }
    return game.knockout_winner(1, 2).status() == StatusType::SUCCESS;
}

bool knockoutWinnerBasicTest() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i * 11, i + 1, 1, i, 0, false);
        }
        game.add_player(11 * (i + 1), i + 1, 0, 0, 0, true);
    }
    return game.knockout_winner(1, 2).ans() == 2;
}

bool knockoutWinnerBasicTestIsGameChanged() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_team(2, 0);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i * 11, i + 1, 1, i, 0, false);
        }
        game.add_player(11 * (i + 1), i + 1, 0, 0, 0, true);
    }
    game.knockout_winner(1, 2);
    return game.get_all_players_count(1).ans() == 11 and game.get_all_players_count(2).ans() ==
    11 and game.get_team_points(1).ans() == 0 and game.get_team_points(2).ans() == 0;
}

bool knockoutWinnerTestFromExample() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 20);
    game.add_team(3, 20);
    game.add_team(6, 5);
    game.add_team(7, 30);
    game.add_team(10, 11);
    game.add_team(11, 1000);
    int team_ids[6] = {1,3,6,7,10,11};
    for (int i = 0; i < 6; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i * 11, team_ids[i], 0, 0, 0, false);
        }
        game.add_player(11 * (i + 1), team_ids[i], 0, 0, 0, true);
    }
    return game.knockout_winner(1, 10).ans() == 3;
}

bool runAutomaticTests(const std::vector<bool(*)()>& tests) {
    std::cout << "Running Automatic Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    bool all_tests_passed = true;
    for (auto test : tests) {
        try {
            if (test()) {
                std::cout << "\033[1;32m - TEST PASSED\033[0m" << std::endl;
            }
            else {
                all_tests_passed = false;
                std::cout << "\033[1;31m - TEST FAILED\033[0m" << std::endl;
            }
        }
        catch (...) {
            all_tests_passed = false;
            std::cout << "\033[1;31m - TEST FAILED\033[0m" << std::endl;
        }
    }
    return all_tests_passed;
}

int main4() {
    std::cout << "Ignore this (Its for the colors)-> ";
    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;

    std::vector<bool(*)()> automatic_tests = {&constructorCrush,
                                              &addTeamInvalidInputId, &addTeamInvalidInputPoints,
                                              &addTeamSuccess, &addTeamAlreadyExistingTeam,
                                              &removeTeamSuccess, &removeTeamInvalidId,
                                              &removeTeamTeamIdDoesntExist, &removeTeamNotEmpty,
                                              &removeTeamAfterLastPlayerRemoval,
                                              &addPlayerSuccess, &addPlayerInvalidPlayerId,
                                              &addPlayerInvalidTeamId,
                                              &addPlayerInvalidGamesPlayed,
                                              &addPlayerInvalidGoals, &addPlayerInvalidCards,
                                              &addPlayerInvalidCardsWithoutGames,
                                              &addPlayerInvalidGoalsWithoutGames,
                                              &addPlayerAlreadyExistsInTeam,
                                              &addPlayerAlreadyExistsInAnotherTeam,
                                              &addPlayerTeamDoesntExist, &removePlayerSuccess,
                                              &removePlayerInvalidId, &removePlayerInvalidId,
                                              &removePlayerDoesntExist,
                                              &updatePlayerStatsInvalidId,
                                              &updatePlayerStatsInvalidGamesPlayed,
                                              &updatePlayerStatsInvalidGoals,
                                              &updatePlayerStatsInvalidCards,
                                              &updatePlayerStatsPlayerDoesntExists,
                                              &updatePlayerStatsSuccess,
                                              &playMatchInvalidFirstTeamId,
                                              &playMatchInvalidSecondTeamId,
                                              &playMatchSameTeamsId,
                                              &playMatchFirstTeamDoesntExist,
                                              &playMatchSecondTeamDoesntExist,
                                              &playMatchFirstTeamIsNotValid,
                                              &playMatchSecondTeamIsNotValid, &playMatchSuccess,
                                              &getNumPlayedGamesInvalidId,
                                              &getNumPlayedGamesPlayerDoesntExist,
                                              &getNumPlayedGamesSuccess,
                                              &getNumPlayedGamesTestOutValue,
                                              &getNumPlayedGamesAfterUpdate,
                                              &getNumPlayedGamesAfterMatch,
                                              &getTeamPointsInvalidId,
                                              &getTeamPointsTeamDoesntExist,
                                              &getTeamPointsSuccess, &getTeamPointsTestOutValue,
                                              &getTeamPointsAfterMatchWin,
                                              &getTeamPointsAfterMatchLoose,
                                              &getTeamPointsAfterMatchTie,
                                              &getTeamPointsAfterMatchWinByGoals,
                                              &getTeamPointsAfterMatchWinByCards,
                                              &uniteTeamsInvalidTeam1Id,
                                              &uniteTeamsInvalidTeam2Id,
                                              &uniteTeamsInvalidNewTeamId,
                                              &uniteTeamsSameTeamsId,
                                              &uniteTeamsTeam1DoesntExist,
                                              &uniteTeamsTeam2DoesntExist,
                                              &uniteTeamsNewTeamIdAlreadyExist,
                                              &uniteTeamsSuccess, &uniteTeamsNewTeamPoints,
                                              &getTopScorerInvalidId, &getTopScorerNoPlayers,
                                              &getTopScorerTeamDoesntExist,
                                              &getTopScorerNoPlayersInTeam, &getTopScorerSuccess,
                                              &getTopScorerTestValueInTeam,
                                              &getTopScorerTestValueInAllTeams,
                                              &getAllPlayersCountInvalidId,
                                              &getAllPlayersCountTeamDoesntExist,
                                              &getAllPlayersCountSuccess,
                                              &getAllPlayersCountInAllTeams,
                                              &getAllPlayersCountInTeam,
                                              &getAllPlayersCountInTeamAfterUnite,
                                              getAllPlayersInvalidId,
                                              &getAllPlayersInvalidOutput,
                                              &getAllPlayersTeamDoesntExist,
                                              &getAllPlayersEmptyTeam, &getAllPlayersNoPlayers,
                                              &getAllPlayersSuccess,
                                              &getAllPlayersTestValueInTeam,
                                              &getAllPlayersTestValueInAllTeams,
                                              &getAllPlayersTestPlayersOrder,
                                              getClosestPlayerInvalidPlayerId,
                                              &getClosestPlayerInvalidTeamId,
                                              &getClosestPlayerPlayerDoesntExist,
                                              &getClosestPlayerPlayerInWrongTeam,
                                              &getClosestPlayerTeamDoesntExist,
                                              &getClosestPlayerOnePlayer,
                                              &getClosestPlayerMiddleSuccess,
                                              &getClosestPlayerFirstSuccess,
                                              &getClosestPlayerLastSuccess,
                                              &getClosestPlayerTestFromExample,
                                              &knockoutWinnerInvalidMaxId,
                                              &knockoutWinnerInvalidMaxId,
                                              &knockoutWinnerMinIdBiggerThanMax,
                                              &knockoutWinnerNoValidTeam, &knockoutWinnerSuccess,
                                              &knockoutWinnerBasicTest,
                                              &knockoutWinnerBasicTestIsGameChanged,
                                              &knockoutWinnerTestFromExample};

    /*std::vector<void(*)()> manual_tests = {&testSingleRrRotationByKey,
                                           &testSingleLlRotationByKey,
                                           &testSingleRlRotationByKey,
                                           &testSingleLrRotationByKey,
                                           &testSingleLlRotationByValue,
                                           &testSingleLrRotationByValue,
                                           &testSingleRlRotationByValue,
                                           &testSingleRrRotationByValue,
                                           &testMultipleRotationsByKey,
                                           &testSingleRrRotationAfterRemovalByKey,
                                           &testSingleLlRotationAfterRemovalByKey,
                                           &testSingleLrRotationAfterRemovalByKey,
                                           &testSingleRlRotationAfterRemovalByKey,
                                           &testRotationAfterRemovalByKey,
                                           &testMultiplyRotationsAfterRemovalByKey};
*/
    if (runAutomaticTests(automatic_tests)) {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;32mALL TESTS PASSED!!!\033[0m" << std::endl;
    }
    else {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;31mSome of the automatic tests failed\033[0m" << std::endl;
    }
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    std::cout << "Running Manual Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    /*
    for (auto test : manual_tests) {
        test();
    }
*/
    return 0;
}

/*
void generalTest1() {
    std::cout << "Dictionary 1" << std::endl;
    int num[6] = {6,4,8,9,24,3};
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    dict.insert(1,&num[0]);
    dict.insert(2, &num[1]);
    dict.insert(3,&num[2]);
    dict.insert(4,&num[3]);
    dict.insert(5,&num[4]);
    dict.insert(6,&num[5]);
    dict.print();
    dict.remove(3, &num[2]);
    dict.print();
}

void generalTest2() {
    std::cout << "Dictionary 2" << std::endl;
    Player v1 = Player(1, 1, 3, 5, 2, false);
    Player v2 = Player(2,1,5,2,3,false);
    Player v3 = Player(3,1,5,3,3, false);
    Player v4 = Player(4,1,3,5,1, false);
    Player v5 = Player(5,1,3,7,2, false);
    Dictionary<int, Player*> dict2 = Dictionary<int, Player*>(false);
    dict2.insert(v1.getPlayerId(), &v1);
    dict2.insert(v2.getPlayerId(), &v2);
    dict2.insert(v3.getPlayerId(), &v3);
    dict2.insert(v4.getPlayerId(), &v4);
    dict2.insert(v5.getPlayerId(), &v5);
    dict2.print();
    dict2.remove(v5.getPlayerId(), &v5);
    std::cout << "level 1" << std::endl;
    dict2.print();
}
void generalTest3(){
    std::cout << "Test3" << std::endl;
    world_cup_t game1 = world_cup_t();
    game1.add_team(4, 10);
    game1.add_team(7, 14);
    game1.add_team(2, 17);
    game1.add_team(1, 5);
    game1.add_team(3, 2);
    game1.add_team(5, 1);
    game1.add_team(10, 6);
    game1.add_team(9, 90);
    game1.add_team(20, 44);
    game1.add_team(19, 62);
    game1.add_team(17, 13);
    game1.add_team(30, 12);
    game1.add_player(1,5,2,3,5, false);
    game1.add_player(2,5,3,5,2, true);
    game1.add_player(3,5,3,5,3,false);
    game1.add_player(4,5,1,3,5,false);
    game1.add_player(5,5,2,3,7, false);
    game1.add_player(6,5,2,3,7, false);
    game1.add_player(7,5,2,3,7, false);
    game1.add_player(8,5,2,3,7, false);
    game1.add_player(9,5,2,3,7, false);
    game1.add_player(10,5,2,3,7, false);
    game1.add_player(11,5,2,3,7, false);
    game1.add_player(12,17,2,3,7, true);
    game1.add_player(13,17,2,3,7, false);
    game1.add_player(14,17,2,3,7, false);
    game1.add_player(15,17,2,3,7, false);
    game1.add_player(16,17,2,3,7, false);
    game1.add_player(17,17,2,3,7, false);
    game1.add_player(18,17,2,3,7, false);
    game1.add_player(19,17,2,3,7, false);
    game1.add_player(20,17,2,3,7, false);
    game1.add_player(21,17,2,3,7, false);
    game1.add_player(22,17,2,3,7, false);
    game1.add_player(23,10,2,3,7, true);
    game1.add_player(24,10,5,5,5, false);
    game1.add_player(25,10,6,2,4, false);
    game1.add_player(26,10,3,3,3, false);
    game1.add_player(27,10,6,6,7, false);
    game1.add_player(28,10,3,7,4, false);
    game1.add_player(29,10,6,3,3, false);
    game1.add_player(30,10,8,5,3, false);
    game1.add_player(31,10,3,3,6, false);
    game1.add_player(32,10,2,2,7, false);
    game1.add_player(33,10,4,1,8, false);
    std::cout << "Test 5, begin" << std::endl;
    game1.getTeams();
    std::cout << "Test 5, end" << std::endl;
}

int main2(){
    generalTest3();
}
 */
int main5(){
    world_cup_t *obj = new world_cup_t();
    int playerId = 1;
    StatusType res;
    for (int teamId = 1; teamId < 10; teamId += 2)
    {
        res = obj->add_team(teamId, 1000 / ((6 - teamId) * (6 - teamId)));

        for (int startingId = playerId; playerId < startingId + 10 + teamId; ++playerId)
        {
            res = obj->add_player(playerId, teamId, 1, playerId, 3, true);
        }
        ++playerId;
    }
    obj->add_team(4, 1000000);
    obj->knockout_winner(8,9);
    obj->knockout_winner(1,1);
    obj->knockout_winner(2,4);
    obj->knockout_winner(3,9);
    obj->knockout_winner(2,8);
    obj->knockout_winner(0,5);
    obj->knockout_winner(1,9);
}

int main() {
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(100, 1, 1, 0, 0, false);
    game.add_player(200, 2, 1, 0, 0, false);
    game.update_player_stats(100, 0, 1, 2);
    std::cout << (game.get_num_played_games(100).ans() == 1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 10; j++) {
            game.add_player(j + i*11, i + 1, 0, 0, 0, false);
        }
        game.add_player(11*(i+1), i + 1, 0, 0, 0, true);
    }
    game.play_match(1,2);
    std::cout << (game.get_num_played_games(100).ans() == 2);
    game.add_player(30, 1, 0, 0, 0, false);
    std::cout << (game.get_num_played_games(30).ans() == 0);
    game.unite_teams(1, 2, 3);
    std::cout << (game.get_num_played_games(100).ans() == 2);
}