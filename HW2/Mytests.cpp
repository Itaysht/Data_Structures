//
// Created by itayi on 21/11/2022.
//
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <random>
#include <iostream>

#include "Player.h"
#include "worldcup23a2.h"

#define REQUIRE(x)

#define ASSERT_WITHOUT_MSG(action, expected) if(action != expected) return false
#define ASSERT_WITH_MSG(action, expected, msg) \
                    if(action != expected){std::cout<<"\033[1;33m"<<msg<<"\033[0m";return false;}
#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define ASSERT_MACRO_CHOOSER(...) GET_4TH_ARG(__VA_ARGS__, ASSERT_WITH_MSG, ASSERT_WITHOUT_MSG,)
#define ASSERT(...) ASSERT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define TEST_PRINT(msg) if(test) std::cout<<msg

#define IS_TEST false

#define PRINT_FUNCTION_NAME if(not test) printFunctionName(__FUNCTION__)

const int MAX_LINE_LENGTH = 50;

enum struct MatchResult {
    TIE                       = 0,
    FIRST_TEAM_WON_BY_VALUE   = 1,
    FIRST_TEAM_WON_BY_SPIRIT  = 2,
    SECOND_TEAM_WON_BY_VALUE  = 3,
    SECOND_TEAM_WON_BY_SPIRIT = 4,
};

void printFunctionName(std::string str) {
    std::string out;
    out += str[0] - 32;
    for (int i = 1; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
            if (i != 0) {
                out += " ";
            }
            out += str[i];
        } else {
            out += str[i];
        }
    }
    std::cout << "Running test: " << out << std::string(MAX_LINE_LENGTH - out.length(), ' ');
}


bool runAutomaticTests(const std::vector<bool (*)(bool)> &tests, bool until_failure = false, bool
until_stuck = false) {
    std::cout << "Running Automatic Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    bool all_tests_passed = true;
    for (auto test: tests) {
        try {
            if (until_stuck) {
                while (true) {
                    test(IS_TEST);
                }
            }
            else if (until_failure) {
                while(test(IS_TEST)){}
                all_tests_passed = false;
            }
            else {
                if (test(IS_TEST)) {
                    std::cout << "\033[1;32m - TEST PASSED\033[0m" << std::endl;
                } else {
                    all_tests_passed = false;
                    std::cout << "\033[1;31m - TEST FAILED\033[0m" << std::endl;
                }
            }
        }
        catch (...) {
            all_tests_passed = false;
            std::cout << "\033[1;31m - TEST FAILED\033[0m" << std::endl;
        }
    }
    return all_tests_passed;
}

bool addRemoveTeam(bool test = false) {
    PRINT_FUNCTION_NAME;
    world_cup_t game = world_cup_t();
    int id = 0;
    for (int i = 1; i <= 1000; i++) {
        ASSERT(game.add_team(id + 1), StatusType::SUCCESS);
        id = (id + 733) % 1000;
    }
    for (int i = 1; i <= 1000; i++) {
        ASSERT(game.add_team(i), StatusType::FAILURE);
    }
    for (int i = 100; i <= 200; i++) {
        ASSERT(game.remove_team(i), StatusType::SUCCESS);
    }
    for (int i = 100; i <= 200; i++) {
        ASSERT(game.add_team(i), StatusType::SUCCESS);
    }

    return true;
}

bool addPlayer(bool test = false) {
    PRINT_FUNCTION_NAME;
    world_cup_t game = world_cup_t();
    const permutation_t spirit = permutation_t::neutral();
    for (int i = 1; i <= 10; i++) {
        ASSERT(game.add_team(i), StatusType::SUCCESS);
    }
    for (int i = 1; i <= 100; i++) {
        ASSERT(game.add_player(i, (i % 10) + 1, spirit, 0, 0, 0, false),
               StatusType::SUCCESS);
    }
    for (int i = 1; i <= 100; i++) {
        ASSERT(game.add_player(i, (i % 10) + 1, spirit, 0, 0, 0, false),
               StatusType::FAILURE);
    }
    ASSERT(game.remove_team(1), StatusType::SUCCESS);
    ASSERT(game.add_player(10, 2, spirit, 0, 0, 0, false), StatusType::FAILURE);
    ASSERT(game.add_player(101, 1, spirit, 0, 0, 0, false), StatusType::FAILURE);
    ASSERT(game.add_team(1), StatusType::SUCCESS);
    ASSERT(game.add_player(101, 1, spirit, 0, 0, 0, false), StatusType::SUCCESS);

    return true;
}

bool getNumPlayedGames(bool test = false) {
    PRINT_FUNCTION_NAME;
    world_cup_t game = world_cup_t();
    const permutation_t spirit = permutation_t::neutral();
    ASSERT(game.add_team(1), StatusType::SUCCESS);
    ASSERT(game.add_team(2), StatusType::SUCCESS);
    ASSERT(game.add_player(1, 1, spirit, 0, 0, 0, false), StatusType::SUCCESS);
    ASSERT(game.add_player(2, 1, spirit, 5, 0, 0, false), StatusType::SUCCESS);
    ASSERT(game.add_player(3, 2, spirit, 0, 0, 0, false), StatusType::SUCCESS);
    ASSERT(game.add_player(4, 2, spirit, 5, 0, 0, false), StatusType::SUCCESS);
    ASSERT(game.num_played_games_for_player(1).ans(), 0);
    ASSERT(game.num_played_games_for_player(2).ans(), 5);
    ASSERT(game.num_played_games_for_player(3).ans(), 0);
    ASSERT(game.num_played_games_for_player(4).ans(), 5);
    ASSERT(game.remove_team(1), StatusType::SUCCESS);
    ASSERT(game.num_played_games_for_player(1).ans(), 0);
    ASSERT(game.num_played_games_for_player(2).ans(), 5);
    return true;
}

bool playMatch(bool test = false) {
    PRINT_FUNCTION_NAME;
    world_cup_t game = world_cup_t();

    const int spirit_list1[5] = {1,3,0,4,2};
    const int spirit_list2[5] = {2,4,1,0,3};
    const permutation_t spirit1 = spirit_list1;
    const permutation_t spirit2 = spirit_list2;
    const permutation_t neutral_spirit = permutation_t::neutral();

    ASSERT(game.add_team(1), StatusType::SUCCESS, "add team 1");
    ASSERT(game.add_team(2), StatusType::SUCCESS);

    ASSERT(game.add_player(1, 1, spirit1, 0, 5, 0, true), StatusType::SUCCESS, "add player 1");
    ASSERT(game.add_player(2, 1, spirit1.inv(), 5, -2, 0, false), StatusType::SUCCESS);
    ASSERT(game.add_player(3, 2, spirit2, 0, 10, 0, true), StatusType::SUCCESS);
    ASSERT(game.add_player(4, 2, spirit2.inv(), 5, -7, 0, false), StatusType::SUCCESS);

    ASSERT(game.get_team_points(1).ans(), 0, "Team 1 points before game");
    ASSERT(game.get_team_points(2).ans(), 0, "Team 2 points before game");

    ASSERT(game.play_match(1, 2).ans(), static_cast<int>(MatchResult::TIE), "TIE");
    ASSERT(game.get_team_points(1).ans(), 1);
    ASSERT(game.get_team_points(2).ans(), 1);

    ASSERT(game.num_played_games_for_player(1).ans(), 1);
    ASSERT(game.num_played_games_for_player(2).ans(), 6);
    ASSERT(game.num_played_games_for_player(3).ans(), 1);
    ASSERT(game.num_played_games_for_player(4).ans(), 6);

    ASSERT(game.add_player(5, 1, spirit1, 10, 10, 0, false), StatusType::SUCCESS);
    ASSERT(game.num_played_games_for_player(5).ans(), 10);

    ASSERT(game.play_match(1, 2).ans(), static_cast<int>(MatchResult::FIRST_TEAM_WON_BY_VALUE),
           "FIRST_TEAM_WON_BY_VALUE");
    ASSERT(game.get_team_points(1).ans(), 4);
    ASSERT(game.get_team_points(2).ans(), 1);

    ASSERT(game.add_player(6, 2, spirit2, 0, 13, 0, false), StatusType::SUCCESS);

    ASSERT(game.play_match(1, 2).ans(), static_cast<int>(MatchResult::FIRST_TEAM_WON_BY_SPIRIT),
           "FIRST_TEAM_WON_BY_SPIRIT");
    ASSERT(game.get_team_points(1).ans(), 7);
    ASSERT(game.get_team_points(2).ans(), 1);

    ASSERT(game.add_player(7, 2, spirit2.inv(), 0, 6, 0, false), StatusType::SUCCESS);

    ASSERT(game.play_match(1, 2).ans(), static_cast<int>(MatchResult::SECOND_TEAM_WON_BY_VALUE),
           "SECOND_TEAM_WON_BY_VALUE");
    ASSERT(game.get_team_points(1).ans(), 7);
    ASSERT(game.get_team_points(2).ans(), 4);

    ASSERT(game.add_player(8, 1, neutral_spirit, 0, 6, 0, false), StatusType::SUCCESS);

    ASSERT(game.play_match(1, 2).ans(), static_cast<int>(MatchResult::SECOND_TEAM_WON_BY_SPIRIT),
           "SECOND_TEAM_WON_BY_SPIRIT");
    ASSERT(game.get_team_points(1).ans(), 7);
    ASSERT(game.get_team_points(2).ans(), 7);

    return true;
}

int main2() {
    std::cout << "Ignore this (Its for the colors)-> ";
    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;

    std::vector<bool (*)(bool)> automatic_tests = {&addRemoveTeam, &addPlayer,
                                                   &getNumPlayedGames, &playMatch};

    std::vector<void (*)()> manual_tests = {};

    if (runAutomaticTests(automatic_tests)) {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;32mALL TESTS PASSED!!!\033[0m" << std::endl;
    } else {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;31mSome of the automatic tests failed\033[0m" << std::endl;
    }
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    std::cout << "Running Manual Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;

    for (auto test: manual_tests) {
        test();
    }

    return 0;
}

int main(){
    int basePerm[5] = {1, 2, 3, 4, 0};
    permutation_t perm = permutation_t(basePerm).inv();

    world_cup_t *obj = new world_cup_t();

    StatusType res = obj->add_team(10);
    REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(11, 10, perm, 1, 1, 1, true);
    (res == StatusType::SUCCESS);

    output_t<int> resn20 = obj->num_played_games_for_player(11);
     (resn20.status() == StatusType::SUCCESS);
    REQUIRE(resn20.ans() == 1);

    res = obj->add_team(20);
    REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(21, 20, perm, 1, 3, 1, true);
    REQUIRE(res == StatusType::SUCCESS);

    res = obj->add_team(30);
    REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(31, 30, perm, 1, 6, 1, true);
    REQUIRE(res == StatusType::SUCCESS);

    output_t<int> resn1 = obj->play_match(10, 20);
    REQUIRE(resn1.status() == StatusType::SUCCESS);
    REQUIRE(resn1.ans() == 3);

    output_t<int> resn21 = obj->num_played_games_for_player(11);
    REQUIRE(resn21.status() == StatusType::SUCCESS);
    REQUIRE(resn21.ans() == 2);

    res = obj->buy_team(10, 20);
    REQUIRE(res == StatusType::SUCCESS);

    output_t<int> resn22 = obj->num_played_games_for_player(11);
    REQUIRE(resn22.status() == StatusType::SUCCESS);
    REQUIRE(resn22.ans() == 2);

    output_t<int> resn2 = obj->get_team_points(10);
    REQUIRE(resn2.status() == StatusType::SUCCESS);
    REQUIRE(resn2.ans() == 3);

    output_t<int> resn3 = obj->get_team_points(20);
    REQUIRE(resn3.status() == StatusType::FAILURE);

    output_t<int> resn4 = obj->get_ith_pointless_ability(1);
    REQUIRE(resn4.status() == StatusType::SUCCESS);
    REQUIRE(resn4.ans() == 30);

    output_t<int> resn5 = obj->play_match(10, 30);
    REQUIRE(resn5.status() == StatusType::SUCCESS);
    REQUIRE(resn5.ans() == 1);

    output_t<int> resn23 = obj->num_played_games_for_player(11);
    REQUIRE(resn23.status() == StatusType::SUCCESS);
    REQUIRE(resn23.ans() == 3);

    obj->add_player(32, 30, perm, 1, 4, 1, true);

    output_t<int> resn6 = obj->play_match(10, 30);
    REQUIRE(resn6.status() == StatusType::SUCCESS);
    REQUIRE(resn6.ans() == 0);
    output_t<int> resn24 = obj->num_played_games_for_player(11);
    REQUIRE(resn24.status() == StatusType::SUCCESS);
    REQUIRE(resn24.ans() == 4);

    res = obj->buy_team(30, 10);
    REQUIRE(res == StatusType::SUCCESS);

    // Partial spirit is correct
    output_t<permutation_t> resn7 = obj->get_partial_spirit(31);
    REQUIRE(resn7.status() == StatusType::SUCCESS);
    REQUIRE(str(resn7.ans()) == str(perm));

    output_t<permutation_t> resn8 = obj->get_partial_spirit(11);
    REQUIRE(resn8.status() == StatusType::SUCCESS);
    REQUIRE(str(resn8.ans()) == str(perm * perm * perm));

    // Num played games is correct
    output_t<int> resn10 = obj->num_played_games_for_player(11);
    REQUIRE(resn10.status() == StatusType::SUCCESS);
    REQUIRE(resn10.ans() == 4);

    output_t<int> resn11 = obj->num_played_games_for_player(21);
    REQUIRE(resn11.status() == StatusType::SUCCESS);
    REQUIRE(resn11.ans() == 4);

    output_t<int> resn12 = obj->num_played_games_for_player(31);
    REQUIRE(resn12.status() == StatusType::SUCCESS);
    REQUIRE(resn12.ans() == 3);

    output_t<int> resn13 = obj->num_played_games_for_player(32);
    REQUIRE(resn13.status() == StatusType::SUCCESS);
    REQUIRE(resn13.ans() == 2);
}