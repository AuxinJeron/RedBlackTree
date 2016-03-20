//
//  main.cpp
//  RedBlackTree
//
//  Created by Leon on 3/15/16.
//  Copyright © 2016 Leon. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include "rbTree.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cout << "Please input the correct path of the file." << endl;
        return 0;
    }
    
    // init the red-black tree
    clock_t start = clock();
    
    vector<pair<long, long>> sortArray;
    string filename = argv[1];
    fstream fs;
    fs.open(filename);
    if (fs.is_open() == false) {
        cout << "Unable to open the file " << filename << endl;
    }
    int id = 0;
    int count = 0;
    int lineNum = 0;
    fs >> lineNum;
    while (-- lineNum >= 0) {
        fs >> id;
        fs >> count;
        sortArray.push_back(make_pair(id, count));
    }
    fs.close();
    
//    RBTree<int, int> counterTree;
    RBTree<long, long> counterTree(sortArray);
//    for (int i = 1; i <= 18; i ++) {
//        counterTree.insert(i, i);
//    }
    
    cout << "Has built the red-black tree, input your command[" << (clock() - start) / (double)CLOCKS_PER_SEC << "s]: " << counterTree.verifyRBTree() << endl;
    // interactive part
    cout << ">>>";
    string line;
    while (getline(cin, line)) {
        istringstream strStream(line);
        string command;
        long parameter1;
        long parameter2;
        strStream >> command;
        if (command == "quit") break;
        else if (command == "insert") {
            strStream >> parameter1; // id
            strStream >> parameter2; // value
            counterTree.insert(parameter1, parameter2);
        }
        else if (command == "delete") {
            strStream >> parameter1; // id
            counterTree.erase(parameter1);
            cout << counterTree.verifyRBTree() << endl;
        }
        else if (command == "increase") {
            strStream >> parameter1; // id
            strStream >> parameter2; // value
            cout << counterTree.increase(parameter1, parameter2) << endl;
            cout << counterTree.verifyRBTree() << endl;
        }
        else if (command == "reduce") {
            strStream >> parameter1; // id
            strStream >> parameter2; // value
            cout << counterTree.reduce(parameter1, parameter2) << endl;
            cout << counterTree.verifyRBTree() << endl;
        }
        else if (command == "count") {
            strStream >> parameter1; // id
            cout << counterTree.getValue(parameter1) << endl;
        }
        else if (command == "inrange") {
            strStream >> parameter1; // id1
            strStream >> parameter2; // id2
            cout << counterTree.inRange(parameter1, parameter2) << endl;
        }
        else if (command == "next") {
            strStream >> parameter1; // id
            cout << counterTree.getNext(parameter1) << endl;
        }
        else if (command == "previous") {
            strStream >> parameter1; // id
            cout << counterTree.getPrevious(parameter1) << endl;
        }
        else if (command == "display") {
            counterTree.display();
        }
        else if (command == "verify") {
            cout << counterTree.verifyRBTree() << endl;
        }
        cout << ">>>";
    }
    
    return 0;
}
