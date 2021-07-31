#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Node {
    string response;
    bool isQuestion;
    Node* left;
    Node* right;
};
struct BinarySearchTree {
    Node* root;
};
Node* newNodeBST(string response) {
    Node* p = new Node;
    if (response[1] == 'Q')
        p->isQuestion = true;
    else
        p->isQuestion = false;
    p->left = nullptr;
    p->right = nullptr;
    p->response = response.substr(3, response.length() - 1 - 3 + 1);
    return p;
}
Node* fillBST(Node* p, fstream& fi) {
    string response;
    getline(fi, response);
    // cout << response << endl;
    p = newNodeBST(response);
    if (p->isQuestion) {
        p->left = fillBST(p->left, fi);
        p->right = fillBST(p->right, fi);
    }
    return p;
}
void printTree(Node* p) {
    if (!p)
        return; 
    cout << p->response << "\t\t|";
    if (p->left) {
        cout << "Left child : " << p->left->response << "\t\t|";
    }
    if (p->right) {
        cout << "Right child : " << p->right->response;
    }
    cout << endl;
    printTree(p->left);
    printTree(p->right);

}
void playGame(Node* p) {
    char cmd;
    cout << p->response << " (y/n)" << endl;
    cin >> cmd;
    if (p->isQuestion == false) {
        if (cmd == 'y')
            cout << "Aha I knew it !\n";
        else if (cmd == 'n')
            cout << "Oh no I guessed wrongly !(extend the tree, new feature comming soon)\n";
        return;
    }
    else {
        if (cmd == 'y')
            playGame(p->left);
        else
            playGame(p->right);
    }
}
Node* deleteTree(Node* p) {
    if (p->left)
        p->left = deleteTree(p->left);
    else if (p->right)
        p->right = deleteTree(p->right); 
    delete p; 
    p = nullptr; 
    return p; 
}
void saveFileGame(Node* p, fstream &fo) {
    if (!p) return; 
    if (p->isQuestion)
        fo << "#Q ";
    else
        fo << "#A "; 
    fo << p->response << endl;
    saveFileGame(p->left, fo);
    saveFileGame(p->right, fo); 
}
int main() {
    fstream fi("dataset.txt", ios::in);
    fstream fo("savefile.txt", ios::out); 
    BinarySearchTree bst;
    bst.root = nullptr; 
    bst.root = fillBST(bst.root, fi);

    int cmd = 0;

    while (true) {
        cout << "Welcome to Machine Learning Application Guess Game!\n";
        cout << "The rule is simple, just think about an realistic application and check the \"AI\" is true\n"; 
        cout << "0) Print the tree\n"; 
        cout << "1) Play the game\n";
        cout << "2) Save the game file\n";
        cout << "3) Quit\n";
        cout << "Please make your selection (0-3), to answer each question, y for yes, n for no\n>>";
        cin >> cmd;
        if (cmd == 0) {
            printTree(bst.root);
        }
        if (cmd == 1) {
            playGame(bst.root);
        }
        if (cmd == 2) {
            saveFileGame(bst.root, fo); 
        }
        else if (cmd == 3) {
            bst.root = deleteTree(bst.root); 
            break;
        }
    }

    fi.close();
    return 0;
}