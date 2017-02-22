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

const int RED = 1;
const int GREEN = 2;
const int ORANGE = 3;
const int BLUE = 4;
const int YELLOW = 5;
const int WHITE = 6;

class Face {
private:
    int faceStartColor;
    int fields[9] = {1,2,3,4,5,6,7,8,9}; // todo: fill with faceStartColor
    
    void shiftWithMemory(int *array, int to, int &memo) {
        int tmp = array[to];
        array[to] = memo;
        memo = tmp;
    }

public:
    Face(int faceStartColor) {
        Face::faceStartColor = faceStartColor; // also fields[4] as middle block will never change
        //fill_n(fields, 9, faceStartColor);
    }
    
    void rotate() {
        int memo;
        shiftWithMemory(fields, 0, memo);
        shiftWithMemory(fields, 2, memo);
        shiftWithMemory(fields, 8, memo);
        shiftWithMemory(fields, 6, memo);
        shiftWithMemory(fields, 0, memo);
        shiftWithMemory(fields, 1, memo);
        shiftWithMemory(fields, 5, memo);
        shiftWithMemory(fields, 7, memo);
        shiftWithMemory(fields, 3, memo);
        shiftWithMemory(fields, 1, memo);
    }
    
    void pushOutAndGetInSide() {
        
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
        {'F', Face(RED)},
        {'R', Face(GREEN)},
        {'B', Face(ORANGE)},
        {'L', Face(BLUE)},
        {'U', Face(YELLOW)},
        {'D', Face(WHITE)}
    };
    
public: void doMove(char move, int moveValue) {
    faces.at(move).rotate();
    faces.at(move).print();
    switch (move) {
        case 'F': // Front Red 1
            break;
        case 'B': // Back Blue 2
            
            break;
        case 'R': // Right
            
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
