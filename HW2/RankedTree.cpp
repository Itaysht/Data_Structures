#include "RankedTree.h"

int RankedTree::getHeight(RankedTree::Node *node) {
    if (node == nullptr) {
        return LEAF_SON_HEIGHT;
    }
    int right_son_height = LEAF_SON_HEIGHT;
    int left_son_height = LEAF_SON_HEIGHT;

    if (node->right_son != nullptr) {
        right_son_height = node->right_son->height;
    }
    if (node->left_son != nullptr) {
        left_son_height = node->left_son->height;
    }

    if (left_son_height > right_son_height) {
        return left_son_height + 1;
    }
    return right_son_height + 1;
}

void RankedTree::stabilizeTree(RankedTree::Node *node, bool is_insert) {
    if (node == nullptr) {
        return;
    }
    int old_height = node->height;
    node->setBfValue(getBfValue(node));
    if (node->bf_value == 2) {
        if (node->left_son->bf_value == -1) {
            LRRotation(node);
        } else {
            LLRotation(node);
        }
        if (is_insert) {
            return;
        }
    } else if (node->bf_value == -2) {
        if (node->right_son->bf_value == 1) {
            RLRotation(node);
        } else {
            RRRotation(node);
        }
        if (is_insert) {
            return;
        }
    }
    node->setHeight(getHeight(node));

    if (node->father == nullptr || (is_insert && old_height == node->height)) {
        return;
    }

    stabilizeTree(node->father, is_insert);
}

int RankedTree::getBfValue(RankedTree::Node *node) {
    return getHeight(node->left_son) - getHeight(node->right_son);
}

void RankedTree::LLRotation(RankedTree::Node *node) {
    Node *right_son_of_left_son = node->left_son->right_son;
    Node *father = node->father;

    node->setFather(node->left_son);
    node->left_son->setRight(node);
    node->setLeft(right_son_of_left_son);
    if (right_son_of_left_son != nullptr) {
        right_son_of_left_son->setFather(node);
    }
    node->father->setFather(father);

    if (father != nullptr) {
        if (father->right_son->key == node->key) {
            father->setRight(node->father);
        } else {
            father->setLeft(node->father);
        }
    }

    if (root->key == node->key) {
        root = node->father;
        root->setFather(nullptr);
    }

    node->setHeight(getHeight(node));
    node->setBfValue(getBfValue(node));
    node->father->setHeight(getHeight(node->father));
    node->father->setBfValue(getBfValue(node->father));
    int subtree = 1;
    if (right_son_of_left_son != nullptr) {
        subtree += right_son_of_left_son->getSizeOfSubTree();
    }
    if (node->right_son != nullptr) {
        subtree += node->right_son->getSizeOfSubTree();
    }
    node->addToSubtree(subtree);
    subtree = 1;
    if (node->father->left_son != nullptr) {
        subtree += node->father->left_son->getSizeOfSubTree();
    }
    subtree += node->getSizeOfSubTree();
    node->father->addToSubtree(subtree);
}

void RankedTree::RRRotation(RankedTree::Node *node) {
    Node *left_son_of_right_son = node->right_son->left_son;
    Node *father = node->father;

    node->setFather(node->right_son);
    node->right_son->setLeft(node);
    node->setRight(left_son_of_right_son);
    if (left_son_of_right_son != nullptr) {
        left_son_of_right_son->setFather(node);
    }
    node->father->setFather(father);

    if (father != nullptr) {
        if (father->left_son->key == node->key) {
            father->setLeft(node->father);
        } else {
            father->setRight(node->father);
        }
    }

    if (root->key == node->key) {
        root = node->father;
        root->setFather(nullptr);
    }

    node->setHeight(getHeight(node));
    node->setBfValue(getBfValue(node));
    node->father->setHeight(getHeight(node->father));
    node->father->setBfValue(getBfValue(node->father));
    int subtree = 1;
    if (left_son_of_right_son != nullptr) {
        subtree += left_son_of_right_son->getSizeOfSubTree();
    }
    if (node->left_son != nullptr) {
        subtree += node->left_son->getSizeOfSubTree();
    }
    node->addToSubtree(subtree);
    subtree = 1;
    if (node->father->right_son != nullptr) {
        subtree += node->father->right_son->getSizeOfSubTree();
    }
    subtree += node->getSizeOfSubTree();
    node->father->addToSubtree(subtree);
}

void RankedTree::RLRotation(RankedTree::Node *node) {
    LLRotation(node->right_son);
    RRRotation(node);
}

void RankedTree::LRRotation(RankedTree::Node *node) {
    RRRotation(node->left_son);
    LLRotation(node);
}

void RankedTree::UpdateTilRoot(RankedTree::Node *start) {
    int subtree = 1;
    while (start != nullptr) {
        if (start->right_son != nullptr) {
            subtree += start->right_son->getSizeOfSubTree();
        }
        if (start->left_son != nullptr) {
            subtree += start->left_son->getSizeOfSubTree();
        }
        start->addToSubtree(subtree);
        start = start->father;
        subtree = 1;
    }
}

StatusType RankedTree::InsertKey(int key, Team *value) {
    Node *optional_father = findNodeByTheSameId(root, value->getID());
    if (optional_father->key == key) {
        return StatusType::FAILURE;
    }
    Node *son = new Node(key, value, optional_father);
    if (key < optional_father->key) {
        optional_father->setLeft(son);
    } else {
        optional_father->setRight(son);
    }
    UpdateTilRoot(optional_father);
    stabilizeTree(optional_father);
    length += 1;
    return StatusType::SUCCESS;
}

StatusType RankedTree::insertValue(int key, Team *value) {
    Node *optional_father = findNodeByValue(root, value);
    if (optional_father->key == key) {
        return StatusType::FAILURE;
    }
    Node *son = new Node(key, value, optional_father);

    if (*value < *optional_father->value) {
        optional_father->setLeft(son);
    } else {
        optional_father->setRight(son);
    }
    UpdateTilRoot(optional_father);
    stabilizeTree(optional_father);
    length += 1;
    return StatusType::SUCCESS;
}

void RankedTree::innerDestroyNodes(RankedTree::Node *current_node) {
    if (current_node == nullptr) {
        return;
    }
    innerDestroyNodes(current_node->left_son);
    Node *right_son = current_node->right_son;
    delete current_node;
    innerDestroyNodes(right_son);
}

void RankedTree::innerDestroyNodesAndContent(RankedTree::Node *current_node) {
    if (current_node == nullptr) {
        return;
    }
    innerDestroyNodesAndContent(current_node->left_son);
    Node *right_son = current_node->right_son;
    delete current_node->value;
    delete current_node;
    innerDestroyNodesAndContent(right_son);
}

void RankedTree::destroyNodesAndContent() {
    innerDestroyNodesAndContent(root);
}

void RankedTree::destroyNodes() {
    innerDestroyNodes(root);
}

StatusType RankedTree::insert(int key, Team *value) {
    try {
        if (root == nullptr) {
            root = new Node(key, value, nullptr);
            length++;
            return StatusType::SUCCESS;
        } else {
            if (is_sorted_by_id) {
                return InsertKey(key, value);
            }
            return insertValue(key, value);
        }
    }
    catch (std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType RankedTree::remove(Team *value) {
    Node *temp = nullptr;
    if (is_sorted_by_id) {
        temp = findNodeByTheSameId(root, value->getID());
    } else {
        temp = findNodeByValue(root, value);
    }
    if (*temp->value != *value) {
        return StatusType::FAILURE;
    }
    removeNode(temp);
    return StatusType::SUCCESS;
}

Team *RankedTree::find(int key) {
    if (is_sorted_by_id) {
        Node *temp = findNodeByTheSameId(root, key);
        if (temp == nullptr) {
            return nullptr;
        }
        if (temp->key == key) {
            return temp->value;
        }
    }
    return nullptr;
}

int RankedTree::find_ith(int i) {
    Node *search = root;
    Team *ans = nullptr;
    while (search != nullptr) {
        if ((search->left_son != nullptr) && (search->left_son->getSizeOfSubTree() == i)) {
            ans = search->value;
            break;
        }
        if ((search->left_son != nullptr) && (search->left_son->getSizeOfSubTree() > i)) {
            search = search->left_son;
        } else {
            if (i == 0) {
                ans = search->value;
                break;
            }
            if (search->left_son != nullptr) {
                i -= (search->left_son->getSizeOfSubTree() + 1);
            } else {
                i -= 1;
            }
            search = search->right_son;
        }
    }
    if (is_sorted_by_id) {
        return ans->getID();
    }
    return ans->getID();
}