#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

std::stringstream board;

char checkFullCross(std::string board){
    if (//first row matches
                board.at(0) != '-' && (
                        board.at(0) == (board.at(1) & board.at(2)) ||
                                board.at(0) == (board.at(4) & board.at(8)) ||
                                board.at(0) == (board.at(5) & board.at(10)))) {
            return board.at(0);
        }
        if (board.at(1) != '-' &&
                (board.at(1) == (board.at(5) & board.at(9)))) {
            return board.at(1);
        }
        if (board.at(2) != '-' &&
                (board.at(2) == (board.at(6) & board.at(10)) ||
                        board.at(2) == (board.at(5) & board.at(8)))) {
            return board.at(2);
        }
        //second row matches
        if (board.at(4) != '-' &&
                (board.at(4) == (board.at(5) & board.at(6)))) {
            return board.at(4);
        }
        //third row matches
        if (board.at(8) != '-' &&
                (board.at(8) == (board.at(9) & board.at(10)))
        ) {
            return board.at(8);
        }

    return '-';
}

void onDrawBoard(std::map<int, std::vector<int>> & coords){
    int coords_counter=0;

    int r=1;

    for(int c=1;c<=(3*3);c++){
        if(coords.size()>coords_counter&&(coords.at(coords_counter)[0]==r&
        coords.at(coords_counter)[1]==(c-(3*(r-1))))){
            board<<(char)coords.at(coords_counter)[2];
            coords_counter++;
        }
        else{
            board<<'-';
        }

        if(c%3==0){
            r++;
            board<<'\n';
        }
    }
}

void onUpdateBoard(std::string curr_board, std::vector <int> coords, std::string agent){
    //Si = |r|*(ir-1) + (ic-1)
    int board_str_update_idx=(4*(coords[0]-1))+(coords[1]-1);

    curr_board.replace(board_str_update_idx,1,agent);

    std::cout<<curr_board<<std::endl;

    board.str("");

    board<<curr_board;
    char possible_winner=checkFullCross(board.str());

    if(possible_winner!='-'){
        std::cout<<"Agent "<<possible_winner<<" has won"<<std::endl;
        exit(0);
    }
}


int main(){

    //init board, resume game session
    std::map<int, std::vector<int>> check_point{{0, {1,1,'o'}},{1,{2,1,'x'}},{2,{2,2,'o'}}};

    onDrawBoard(check_point);

    std::cout<<board.str()<<std::endl;

    //sequence of play moves
    onUpdateBoard(board.str(),{1,2},"x");
    onUpdateBoard(board.str(),{3,3},"o");
    onUpdateBoard(board.str(),{3,2},"x");
}