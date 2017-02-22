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

const char FRONT = 'F';
const char RIGHT = 'R';
const char BACK = 'B';
const char LEFT = 'L';
const char UP = 'U';
const char DOWN = 'D';

const int RED = 1;
const int GREEN = 2;
const int ORANGE = 3;
const int BLUE = 4;
const int YELLOW = 5;
const int WHITE = 6;

const int SIDE_INDEXES_SIZE = 3;

class Face {
private:
    int faceStartColor;
    int fields[9];
    
    void shiftWithMemory(int to, int &memo) {
        int tmp = fields[to];
        fields[to] = memo;
        memo = tmp;
    }

public:
    Face(int faceStartColor) {
        Face::faceStartColor = faceStartColor; // also fields[4] as middle block will never change
        fill_n(fields, 9, faceStartColor);
    }
    
    void rotate() {
        int memo;
        shiftWithMemory(0, memo);
        shiftWithMemory(2, memo);
        shiftWithMemory(8, memo);
        shiftWithMemory(6, memo);
        shiftWithMemory(0, memo);
        shiftWithMemory(1, memo);
        shiftWithMemory(5, memo);
        shiftWithMemory(7, memo);
        shiftWithMemory(3, memo);
        shiftWithMemory(1, memo);
    }
    
    void pushOutAndGetInSide(int (&indexes)[SIDE_INDEXES_SIZE], int (&memo)[SIDE_INDEXES_SIZE]) {
        int tmp[SIDE_INDEXES_SIZE];
        // cout << "before: " << memo[0] << " " << memo[1] << " " << memo[2] << endl;
        for (int i = 0; i < SIDE_INDEXES_SIZE; ++i) {
            int index = indexes[i];
            tmp[i] = fields[index];
            fields[index] = memo[i];
            memo[i] = tmp[i];
        }
        // cout << "after: " << memo[0] << " " << memo[1] << " " << memo[2] << endl;
    }
    
    void print() {
        for (int i : fields) {
            cout << i << endl;
        }
        cout << endl;
    }
    
    void printNum() {
        cout << "face type: " << faceStartColor << endl;
    }
};

class Cube {

    map<char, Face> faces = {
        {FRONT, Face(RED)},
        {RIGHT, Face(GREEN)},
        {BACK, Face(ORANGE)},
        {LEFT, Face(BLUE)},
        {UP, Face(YELLOW)},
        {DOWN, Face(WHITE)}
    };
    
    void doFrontMovement() {
        int memo[SIDE_INDEXES_SIZE];
        int rightIndexes[SIDE_INDEXES_SIZE] = {0, 3, 6};
        faces.at(RIGHT).pushOutAndGetInSide(rightIndexes, memo);
        int downLeftIndexes[SIDE_INDEXES_SIZE] = {8, 5, 2};
        faces.at(DOWN).pushOutAndGetInSide(downLeftIndexes, memo);
        faces.at(LEFT).pushOutAndGetInSide(downLeftIndexes, memo);
        int upIndexes[SIDE_INDEXES_SIZE] = {2, 5, 8};
        faces.at(UP).pushOutAndGetInSide(upIndexes, memo);
        faces.at(RIGHT).pushOutAndGetInSide(rightIndexes, memo);
    }
    
    void doRightMovement() {
        
    }
    
    void doBackMovement() {
        
    }
    
    void doLeftMovement() {
        
    }
    
    void doUpMovement() {
        
    }
    
    void doDownMovement() {
        
    }
    
public: void doMove(char move, int moveValue) {
    faces.at(move).rotate();
    faces.at(move).print();
    switch (move) {
        case FRONT:
            doFrontMovement();
            break;
        case RIGHT:
            doRightMovement();
            break;
        case BACK:
            doBackMovement();
            break;
        case LEFT:
            doLeftMovement();
            break;
        case UP:
            doUpMovement();
            break;
        case DOWN:
            doDownMovement();
            break;
    }
        cout << move << " by: " << moveValue << endl;
    }
    
string toString() {
        return "";
    }
};

void print(const vector<string>& vector){
    for (unsigned i = 0; i< vector.size(); ++i) {
        cout << vector[i] << endl;
    }
}

void doMove(char move, int moveValue, Cube cube) {
    cube.doMove(move, moveValue);
}

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

string computeFaceColors(string faceMovesChain) {
    vector<pair<char, int>> moves = parseMovesChain(faceMovesChain);
    Cube cube;
    for (pair<char, int> move : moves) {
        doMove(move.first, move.second, cube);
    }
    return cube.toString();
}

int main(int argc, const char * argv[]) {
    computeFaceColors("F");
    //computeFaceColors("BRL'D'R2DLR'B'R2UB2U'DR2D2'BRL2'D'R2DLR'B'R2UB2U'DR2D2'");
    //assert(computeFaceColors("RL'") == "2 1 2 1 2 2");
//    assert(computeFaceColors("BRL'D'R2DLR'B'R2UB2U'DR2D2'BRL2'D'R2DLR'B'R2UB2U'DR2D2'") == "4 4 5 4 4 4");
//    assert(computeFaceColors("R2L2U2D2F2B2") == "2 2 2 2 2 2");
//    assert(computeFaceColors("RRRRLLLLUUUUDDDDFFFFBBBB") == "1 1 1 1 1 1");
//    assert(computeFaceColors("URU2R'F'F'U'R2URFUF2U'R'") == "3 5 5 3 2 3");
    return 0;
}
