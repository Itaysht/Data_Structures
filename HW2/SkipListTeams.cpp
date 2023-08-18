//
// Created by itayi on 21/12/2022.
//

#include "SkipListTeams.h"

StatusType SkipListTeams::insert(int teamId, Team *team) {
    if (find(teamId) != nullptr) {
        return StatusType::FAILURE;
    }
    Node *new_node = recursiveInsert(teamId, team, root);
    if (new_node == nullptr) {
        return StatusType::SUCCESS;
    }

    while (not coinToss()) {
        Node* new_root = new Node(-1, nullptr);
        Node *new_level_inserted_node = new Node(teamId, team);
        new_level_inserted_node->setDown(new_node);
        new_root->setDown(root);
        new_root->setRight(new_level_inserted_node);
        root = new_root;
        new_node = new_level_inserted_node;
    }
    return StatusType::SUCCESS;
}


bool SkipListTeams::coinToss() const {
    int randomNumber;
    randomNumber = std::rand() % 2;

    return randomNumber == 0;
}

SkipListTeams::Node *
SkipListTeams::recursiveInsert(int teamId, Team *team, SkipListTeams::Node *current_node) {
    while (current_node->right != nullptr and ((current_node->right->value->getTotalAbility() < team->getTotalAbility()) ||
            ((current_node->right->value->getTotalAbility() == team->getTotalAbility()) && (current_node->right->key < teamId)))) {
        current_node = current_node->right;
    }
    if (current_node->down == nullptr) {
        return addNodeAfter(teamId, team, current_node);
    }

    Node *deeper_node = recursiveInsert(teamId, team, current_node->down);

    if (deeper_node == nullptr or coinToss()) {
        return nullptr;
    }

    Node *new_node = addNodeAfter(teamId, team, current_node);
    new_node->setDown(deeper_node);
    return new_node;
}

SkipListTeams::Node *
SkipListTeams::addNodeAfter(int teamId, Team *team, SkipListTeams::Node *left_node) {
    Node *right_node = left_node->right;
    Node *new_node = new Node(teamId, team);
    new_node->setRight(right_node);
    left_node->setRight(new_node);
    return new_node;
}

Team *SkipListTeams::find(int teamId) const {
    Node *current_node = root;

    while (true) {
        while (current_node->right != nullptr and ((current_node->right->value->getTotalAbility() < team->getTotalAbility()) ||
                                                   ((current_node->right->value->getTotalAbility() == team->getTotalAbility()) && (current_node->right->key < teamId)))) {
            current_node = current_node->right;
        }
        if (current_node->down == nullptr) {
            break;
        }
        current_node = current_node->down;
    }

    if (current_node->key != -1 and current_node->value->getID() == teamId) {
        return current_node->value;
    }

    return nullptr;
}

bool SkipListTeams::remove(int teamId) {
    Node *current_node = root;

    bool is_deleted = false;

    while (true) {
        while (current_node->right != nullptr and current_node->right->key < teamId) {
            current_node = current_node->right;
        }


        if (current_node->right != nullptr and current_node->right->key == teamId) {
            removeNodeAfter(current_node);
            is_deleted = true;
        }

        if (current_node->down == nullptr) {
            break;
        }
        else if (root->right == nullptr) {
            Node* new_root = root->down;
            delete root;
            root = new_root;
            current_node = root;
        }
        else {
            current_node = current_node->down;
        }
    }

    return is_deleted;

}

void SkipListTeams::removeNodeAfter(SkipListTeams::Node *left_node) {
    Node* node_to_delete = left_node->right;
    left_node->setRight(node_to_delete->right);
    delete node_to_delete;
}

SkipListTeams::~SkipListTeams() {

}

int SkipListTeams::get_height() const {
    int height = 1;
    Node* current_node = root;
    while (current_node->right != nullptr and current_node->down != nullptr) {
        if (current_node->down != nullptr) {
            height++;
            current_node = current_node->down;
        }
        else {
            current_node = current_node->right;
        }
    }
    return height;
}
