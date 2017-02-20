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
using namespace std;

vector<string> parseMovesChain(string faceMovesChain) {
    regex regex("[B-U](?:2?'?)?", regex_constants::icase);
    smatch matcher;
    vector<string> moves;
    regex_iterator<string::iterator> iterator(faceMovesChain.begin(), faceMovesChain.end(), regex);
    regex_iterator<string::iterator> end;
    while (iterator != end) {
        moves.push_back(iterator -> str());
        ++iterator;
    }
    return moves;
}

void print(const vector<string>& vector){
    for (unsigned i = 0; i< vector.size(); ++i) {
        cout << vector[i] << endl;
    }
}

string computeFaceColors(string faceMovesChain) {
    vector<string> moves = parseMovesChain(faceMovesChain);
    for (string move : moves) {
        doMove(move);
    }
    return "";
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
