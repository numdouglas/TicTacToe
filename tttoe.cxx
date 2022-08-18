#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

std::stringstream board;
bool state_end=false;

char checkFullCross(std::string board){
    if (//first row matches
                board.at(0) != '-' && (
                        board.at(0) == (board.at(1) & board.at(2)) ||
                                board.at(0) == (board.at(3) & board.at(6)) ||
                                board.at(0) == (board.at(4) & board.at(8)))) {
            return board.at(0);
        }
        if (board.at(1) != '-' &&
                (board.at(1) == (board.at(4) & board.at(7)))) {
            return board.at(1);
        }
        if (board.at(2) != '-' &&
                (board.at(2) == (board.at(5) & board.at(8)) ||
                        board.at(2) == (board.at(4) & board.at(6)))) {
            return board.at(2);
        }
        //second row matches
        if (board.at(3) != '-' &&
                (board.at(3) == (board.at(4) & board.at(5)))) {
            return board.at(3);
        }
        //third row matches
        if (board.at(6) != '-' &&
                (board.at(6) == (board.at(7) & board.at(8)))
        ) {
            return board.at(6);
        }

    return '-';
}

std::string getDisplayableBoardString(std::string items){
	std::string displayable_board;
	
	for(int i=0;i<9;i=i+3){
		displayable_board.append(items,i,3);
		displayable_board.append("\n");
	}
	return displayable_board;
}

void onDrawBoard(std::map<int, std::vector<int>> & coords){
    int coords_counter=0;

    int r=1;

    for(int c=1;r<=3;c++){
		
        if(coords.size()>coords_counter&&coords.at(coords_counter)[0]==r&&
        coords.at(coords_counter)[1]==c){
            board<<(char)coords.at(coords_counter)[2];
            coords_counter++;
        }
        else{
            board<<'-';
        }

        if(c%3==0){
            r++;
			c=0;
        }
    }

	//std::cout<<"Board is : \n"<<board.str()<<std::endl<<"Displayable board is :\n"<<getDisplayableBoardString(board.str())<<std::endl;
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
        state_end=true;
    }
}


void onUpdateBoard(int board_pos, std::string agent){
	/*SBi=(UBi-1)+((UBi-1)mod 3)/3 where CBi is board string index and UBi is natural
	counted position on 3x3 board from players' perspectives*/
	//int board_str_update_idx=(board_pos-1)+(((board_pos-1)-(board_pos-1)%3)/3);
	std::string curr_board_str= board.str();
	
	curr_board_str.replace(board_pos-1,1,agent);

    std::cout<<getDisplayableBoardString(curr_board_str)<<std::endl;

    board.str("");

    board<<curr_board_str;
	
    char possible_winner=checkFullCross(curr_board_str);

    if(possible_winner!='-'){
        std::cout<<"Agent "<<possible_winner<<" has won"<<std::endl;
        state_end=true;
    }	
}


int main(){

    //init board, resume game session
    std::map<int, std::vector<int>> check_point{{0, {1,1,'o'}},{1,{2,1,'x'}},{2,{2,2,'o'}}};

    std::cout<<"Begin ..."<<std::endl<<std::endl;
	onDrawBoard(check_point);

	std::cout<<getDisplayableBoardString(board.str())<<std::endl;
	
	int turns=(int)check_point.size();
	int move_input;
	
	std::string current_player="x";
	
	
	while(!state_end){
		if(++turns>(3*3)){
			std::cout<<"Game ends in a Draw."<<std::endl;
			state_end=true;
			continue;
		}

		std::cout<<"Enter coords  for player "<<current_player<<": ";
		std::cin>>move_input;
	
		onUpdateBoard(move_input,current_player);
		current_player=current_player=="x"?"o":"x";
	}
    //sequence of play moves
    //onUpdateBoard(board.str(),{1,2},"x");
    //onUpdateBoard(board.str(),{3,3},"o");
    //onUpdateBoard(board.str(),{3,2},"x");
}