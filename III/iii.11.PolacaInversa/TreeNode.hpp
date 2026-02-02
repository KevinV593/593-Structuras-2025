#include <string>
using namespace std;

struct TreeNode {
    string valor;     // Puede ser número "3" u operador "+"
    TreeNode* left;
    TreeNode* right;

    TreeNode(string v) : valor(v), left(nullptr), right(nullptr) {}
};