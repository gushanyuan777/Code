#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm> // 为了使用std::max

// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree {
public:
    // 默认构造函数
    BinarySearchTree() : root{ nullptr } {}

    // 拷贝构造函数
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    // 移动构造函数
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    // 析构函数
    ~BinarySearchTree() {
        makeEmpty();
    }

    // 查找并返回树中的最小元素
    const Comparable &findMin() const {
        if (isEmpty())
            throw UnderflowException();
        return findMin(root)->element;
    }

    // 查找并返回树中的最大元素
    const Comparable &findMax() const {
        if (isEmpty())
            throw UnderflowException();
        return findMax(root)->element;
    }

    // 检查树中是否包含指定的元素
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    // 检查树是否为空
    bool isEmpty() const {
        return root == nullptr;
    }

    // 打印树的结构
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    // 清空树中的所有元素
    void makeEmpty() {
        makeEmpty(root);
    }

    // 插入一个常量引用元素到树中
    void insert(const Comparable &x) {
        insert(const_cast<Comparable &&>(x), root);
        balance(root);
    }

    // 插入一个右值引用元素到树中
    void insert(Comparable &&x) {
        insert(std::move(x), root);
        balance(root);
    }

    // 从树中移除指定的元素
    void remove(const Comparable &x) {
        remove(x, root);
        balance(root);
    }

    // 拷贝赋值运算符
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    // 移动赋值运算符
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    // 首先定义BinaryNode结构体
    struct BinaryNode {
        Comparable element;  
        BinaryNode *left;    
        BinaryNode *right;   
        int height;

        BinaryNode(const Comparable &theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 1)
            : element{ theElement }, left{ lt }, right{ rt }, height{ h } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 1)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ h } {}
    };

    BinaryNode *root;  

    // 然后定义所有成员函数
    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

void insert(Comparable &&x, BinaryNode * &t) {
    if (t == nullptr) {
        t = new BinaryNode{std::move(x), nullptr, nullptr, 1};
    } else if (x < t->element) {
        if (t->left == nullptr) {
            t->left = new BinaryNode{std::move(x), nullptr, nullptr, 1};
        } else {
            insert(std::move(x), t->left);
        }
    } else if (x > t->element) {
        if (t->right == nullptr) {
            t->right = new BinaryNode{std::move(x), nullptr, nullptr, 1};
        } else {
            insert(std::move(x), t->right);
        }
    } else {
        // 如果元素已存在，则不进行插入
    }
    updateHeight(t);
    balance(t);
}

    void updateHeight(BinaryNode *node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    int getHeight(BinaryNode *node) const {
        return node ? node->height : 0;
    }

    BinaryNode* rotateRight(BinaryNode *y) {
        BinaryNode *x = y->left;
        BinaryNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    BinaryNode* rotateLeft(BinaryNode *x) {
        BinaryNode *y = x->right;
        BinaryNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    int getBalance(BinaryNode *node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void remove(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            return;
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else {
            if (t->left == nullptr) {
                BinaryNode *oldNode = t;
                t = t->right;
                delete oldNode;
            } else if (t->right == nullptr) {
                BinaryNode *oldNode = t;
                t = t->left;
                delete oldNode;
            } else {
                BinaryNode *successor = findMin(t->right);
                t->element = std::move(successor->element); // 使用std::move来避免复制
                remove(successor->element, t->right);
            }
        }
        if (t != nullptr) {
            updateHeight(t);
            balance(t);
        }
    }
    
    void balance(BinaryNode * &node) {
        if (node == nullptr) return;
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) {
            node = rotateRight(node);
        } else if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        } else if (balance < -1 && getBalance(node->right) <= 0) {
            node = rotateLeft(node);
        } else if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }
    return new BinaryNode(t->element, clone(t->left), clone(t->right), t->height);
}

    // 获取根节点
    BinaryNode* getRootElement() const {
        return root;
    }
};

#endif // BST_H