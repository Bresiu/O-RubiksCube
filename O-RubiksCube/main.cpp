//
//  main.cpp
//  O-RubiksCube
//
//  Created by Michał Brewczak on 19/02/2017.
//  Copyright © 2017 Michał Brewczak. All rights reserved.
//

#include <iostream>
#include <vector>
#include <regex>
#include <assert.h>
#include <algorithm>
#include <map>

using namespace std;

class Face {
private:
    int faceType;
    int fields[9];
public:
    Face(int faceType) {
        Face::faceType = faceType;
        fill_n(fields, 9, faceType);
    }
};

class Cube {
    map<char, Face> faces = {
        pair<char, Face> ('F', Face(6)),
        pair<char, Face> ('B', Face(5)),
        pair<char, Face> ('R', Face(4)),
        pair<char, Face> ('L', Face(3)),
        pair<char, Face> ('U', Face(2)),
        pair<char, Face> ('D', Face(1))
    };
public: void doMove(char move, int moveValue) {
    switch (move) {
        case 'F':
            
            break;
        case 'B':
            
            break;
        case 'R':
            
            break;
        case 'L':
            
            break;
        case 'U':
            
            break;
        case 'D':
            
            break;
        default:
            break;
    }
        cout << move << " by: " << moveValue << endl;
    }
    
public: string toString() {
        return "";
    }
};

pair<char, int> parseMoveValue(string move) {
    if (move.length() == 1) {
        return make_pair(move[0], 1);
    } else if (move[1] == '2') {
        return make_pair(move[0], 2);
    } else {
        return make_pair(move[0], 3);
    }
}

vector<pair<char, int>> parseMovesChain(string faceMovesChain) {
    regex regex("[B-U](?:2?'?)?", regex_constants::icase);
    smatch matcher;
    vector<pair<char, int>> moves;
    regex_iterator<string::iterator> iterator(faceMovesChain.begin(), faceMovesChain.end(), regex);
    regex_iterator<string::iterator> end;
    while (iterator != end) {
        moves.push_back(parseMoveValue(iterator -> str()));
        ++iterator;
    }
    return moves;
}

void print(const vector<string>& vector){
    for (unsigned i = 0; i< vector.size(); ++i) {
        cout << vector[i] << endl;
    }
}

void doMove(char move, int moveValue, Cube cube) {
    cube.doMove(move, moveValue);
}

string computeFaceColors(string faceMovesChain) {
    vector<pair<char, int>> moves = parseMovesChain(faceMovesChain);
    Cube cube;
    for (pair<char, int> move : moves) {
        doMove(move.first, move.second, cube);
    }
    return cube.toString();
}

int main(int argc, const char * argv[]) {
    computeFaceColors("BRL'D'R2DLR'B'R2UB2U'DR2D2'BRL2'D'R2DLR'B'R2UB2U'DR2D2'");
    //assert(computeFaceColors("RL'") == "2 1 2 1 2 2");
//    assert(computeFaceColors("BRL'D'R2DLR'B'R2UB2U'DR2D2'BRL2'D'R2DLR'B'R2UB2U'DR2D2'") == "4 4 5 4 4 4");
//    assert(computeFaceColors("R2L2U2D2F2B2") == "2 2 2 2 2 2");
//    assert(computeFaceColors("RRRRLLLLUUUUDDDDFFFFBBBB") == "1 1 1 1 1 1");
//    assert(computeFaceColors("URU2R'F'F'U'R2URFUF2U'R'") == "3 5 5 3 2 3");
    return 0;
}
