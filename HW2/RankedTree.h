#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "Team.h"

const int LEAF_HEIGHT = 0;
const int LEAF_SON_HEIGHT = -1;

class RankedTree {
public:
    RankedTree(bool is_id) : root(nullptr), length(0), is_sorted_by_id(is_id) {};

    ~RankedTree() = default;

    StatusType insert(int key, Team *value);

    StatusType remove(Team *value);

    Team *find(int key);

    int find_ith(int key);

    void destroyNodes();

    void destroyNodesAndContent();

private:

    class Node {
    public:
        Node(int key, Team *value, Node *father) : key(key), value(value), father(father),
                                                   left_son(nullptr), right_son(nullptr), bf_value(0),
                                                   height(LEAF_HEIGHT), num_of_teams_in_subtree(1) {}

        Node(const Node &node) = default;

        Node &operator=(const Node &node) = default;

        ~Node() = default;

        void setLeft(Node *left) { left_son = left; }

        void setRight(Node *right) { right_son = right; }

        void setFather(Node *fat) { father = fat; }

        void setKey(int other_key) { key = other_key; }

        void setValue(Team *other_value) { value = other_value; }

        void setHeight(int new_height) { height = new_height; }

        void setBfValue(int new_bf_value) { bf_value = new_bf_value; }

        void addToSubtree(int added) { num_of_teams_in_subtree = added; }

        int getSizeOfSubTree() const { return num_of_teams_in_subtree; }

        int key;
        Team *value;
        Node *father;
        Node *left_son;
        Node *right_son;
        int bf_value;
        int height;
        int num_of_teams_in_subtree;
    };

    Node *root;
    int length;
    bool is_sorted_by_id;

    void stabilizeTree(Node *node, bool is_insert = true);

    int getBfValue(Node *node);

    void LLRotation(Node *node);

    void RRRotation(Node *node);

    void RLRotation(Node *node);

    void LRRotation(Node *node);

    void UpdateTilRoot(Node *start);

    StatusType insertValue(int key, Team *value);

    StatusType InsertKey(int key, Team *value);

    void innerDestroyNodes(Node *current_node);

    void innerDestroyNodesAndContent(Node *current_node);

    int getHeight(Node *node);

    Node *findNodeByTheSameId(Node *current_root, int key) {
        if (current_root == nullptr) {
            return nullptr;
        }
        Team *temp = current_root->value;
        if (temp->getID() == key) {
            return current_root;
        }
        if (temp->getID() > key) {
            if (current_root->left_son == nullptr) {
                return current_root;
            }
            return findNodeByTheSameId(current_root->left_son, key);
        }
        if (current_root->right_son == nullptr) {
            return current_root;
        }
        return findNodeByTheSameId(current_root->right_son, key);
    }

    Node *findNodeWithHighestID(Node *current_root, int ability) {
        if (current_root == nullptr) {
            return nullptr;
        }
        int temp_ability = current_root->value->getTotalAbility();
        if (temp_ability == ability) {
            while (current_root->right_son != nullptr) {
                if (current_root->right_son->value->getTotalAbility() == ability) {
                    current_root = current_root->right_son;
                    continue;
                }
                if ((current_root->right_son->left_son != nullptr) &&
                    (current_root->right_son->left_son->value->getTotalAbility() == ability)) {
                    current_root = current_root->right_son->left_son;
                    continue;
                }
                return current_root;
            }
            return current_root;
        }
        if (temp_ability < ability) {
            if (current_root->right_son == nullptr) {
                return current_root;
            }
            return findNodeWithHighestID(current_root->right_son, ability);
        }
        if (current_root->left_son == nullptr) {
            return current_root;
        }
        return findNodeWithHighestID(current_root->left_son, ability);
    }

    Node *findNodeByValue(Node *current_root, Team *value_to_find) {
        if (current_root == nullptr) {
            return nullptr;
        }

        Team *temp = current_root->value;
        if (*temp == *value_to_find) {
            return current_root;
        }
        if (*temp > *value_to_find) {
            if (current_root->left_son == nullptr) {
                return current_root;
            }
            return findNodeByValue(current_root->left_son, value_to_find);
        }
        if (current_root->right_son == nullptr) {
            return current_root;
        }
        return findNodeByValue(current_root->right_son, value_to_find);
    }

    void removeNode(Node *ro) {
        if (ro == nullptr) {
            return;
        }
        if ((ro->left_son == nullptr) && (ro->right_son == nullptr)) {
            if (ro->father == nullptr) {
                root = nullptr;
                delete ro;
                length -= 1;
                return;
            }
            if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                ro->father->setLeft(nullptr);
            } else {
                ro->father->setRight(nullptr);
            }
            UpdateTilRoot(ro->father);
            stabilizeTree(ro->father, false);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->left_son == nullptr) {
            if (ro->father == nullptr) {
                ro->right_son->setFather(nullptr);
                root = ro->right_son;
            } else {
                if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                    ro->father->setLeft(ro->right_son);
                    ro->right_son->setFather(ro->father);
                } else {
                    ro->father->setRight(ro->right_son);
                    ro->right_son->setFather(ro->father);
                }
            }
            UpdateTilRoot(ro->father);
            stabilizeTree(ro->father, false);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->right_son == nullptr) {
            if (ro->father == nullptr) {
                ro->left_son->setFather(nullptr);
                root = ro->left_son;
            } else {
                if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                    ro->father->setLeft(ro->left_son);
                    ro->left_son->setFather(ro->father);
                } else {
                    ro->father->setRight(ro->left_son);
                    ro->left_son->setFather(ro->father);
                }
            }
            UpdateTilRoot(ro->father);
            stabilizeTree(ro->father, false);
            //log(n) + log(n), maybe a problem with complexity
            delete ro;
            length -= 1;
            return;
        }
        Node *nearest = ro->right_son;
        while (nearest->left_son != nullptr) {
            nearest = nearest->left_son;
        }
        int temp_key = ro->key;
        Team *temp_value = ro->value;
        ro->setKey(nearest->key);
        ro->setValue(nearest->value);
        nearest->setKey(temp_key);
        nearest->setValue(temp_value);
        removeNode(nearest);
    }
};

#endif //EX1_DICTIONARY_H
