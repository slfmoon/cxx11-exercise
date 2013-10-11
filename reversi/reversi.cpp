#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>

int count_turn_over(std::array<std::array<int, 10>, 10> board, int player, int p, int q, int d, int e);
int is_legal_move(std::array<std::array<int, 10>, 10> board, int player, int p, int q);
int exist_legal_move(std::array<std::array<int, 10>, 10> board, int player);
void get_move(std::array<std::array<int, 10>, 10> board, int player, int *p, int *q);
void print_board(std::array<std::array<int, 10>, 10> board);
void set_and_turn_over(std::array<std::array<int, 10>, 10> &board, int player, int p, int q);
void count_stone(std::array<std::array<int, 10>, 10> board, int *c1, int *c2);

int player_versus(int player){ return 3 - player; };

int init(std::array<std::array<int, 10>, 10> &board);
int game();

/*
int check(std::array<std::array<int, 10>, 10> a, int p, int q, int d, int e); // p: iterator number d: direction

int check(std::array<std::array<int, 10>, 10> a, int p, int q, int d, int e){
	int result = 0;

	// check
	auto iter_p = a.begin();
	auto iter_start = a.begin();
	auto iter_end = a.end();
	if(d == 1){
	}else if(d == -1){
		std::reverse(a.begin(), a.end());
		p = 9 - p;
	}else if(d == 0){
	}else{
		// d == 0 or other: error
		return 0;
	}
	std::advance(iter_p, p + 1);

	auto iter = a.begin();
	while(iter != a.end()){
		std::cout << *iter << " ";
		++iter;
	}
	std::cout << std::endl;
	
	std::cout << p << " " << *iter_p << std::endl;
	auto ifound_a = std::find(iter_p, iter_end, 0);
	auto ifound_b = std::find(iter_p, iter_end, 1);
	auto i_a = std::distance(a.begin(), ifound_a);
	auto i_b = std::distance(a.begin(), ifound_b);
	std::cout << i_a << " " << i_b <<  std::endl;

	if(ifound_b != a.end()) result = std::distance(--iter_p, ifound_b) - 1;
	if(ifound_a < ifound_b) result = 0;
	return result;
}
*/

int count_turn_over(std::array<std::array<int, 10>, 10> board, int player, int p, int q, int d, int e){
	int versus = player_versus(player);
	int i = 0;
	for(i = 1; board[p+i*d][q+i*e] == versus; ++i);
	if(board[p+i*d][q+i*e] == player) return --i;
	return 0;
}

int is_legal_move(std::array<std::array<int, 10>, 10> board, int player, int p, int q){
	if(p < 1 || p > 8 || q < 1 || q > 8) return 0;
	if(board[p][q] != 0) return 0;
    for (int d = -1; d <= 1; ++d) {
        for (int e = -1; e <= 1; ++e) {
            if (count_turn_over(board, player, p, q,  d, e)) return 1;        }
    }	
}

int exist_legal_move(std::array<std::array<int, 10>, 10> board, int player){

	for(int i = 1; i <= 8; ++i)
		for(int j = 1; j <= 8; ++j)
			if(is_legal_move(board, player, i, j)) return 1;
	return 0;
}

void get_move(std::array<std::array<int, 10>, 10> board, int player, int *p, int *q){
	std::string buf;
	std::cout << "Player " << player << " : " << std::endl;
	while(1){
		std::cout << "> ";
		std::cin >> buf;

		if(buf.size() < 2) continue;

		char a = buf.at(0);
		char b = buf.at(1);

		if(a > '8'){
			*q = a - 'a' + 1;
			*p = b - '1' + 1;
		}else{
			*p = a - '1' + 1;
			*q = b - 'a' + 1;
		}
		std::cout << a << "," << b << " / " << *q << "," << *p << std::endl;
		if(is_legal_move(board, player, *p, *q)) return;
		
		std::cout << "select a legal move:";
		for(int i = 1; i <= 8; ++i){
			for(int j = 1; j <= 8; ++j){
				if(is_legal_move(board, player, i, j)){
					char u = i + '1' - 1;
					char v = j + 'a' - 1;
					std::cout << " " << v << u;
				}
			}
		}
		std::cout << std::endl;
	}
}

void set_and_turn_over(std::array<std::array<int, 10>, 10> &board, int player, int p, int q){
	int count = 0;
	for(int d = -1; d <= 1; ++d){ //ã‰º•ûŒü
		for(int e = -1; e <= 1; ++e){
			if(d == 0 && e == 0) continue;
			count = count_turn_over(board, player, p, q, d, e);
			for(int i = 1; i <= count; i++)
				board[p+i*d][q+i*e] = player;
		}
	}
	board[p][q] = player;
}

void count_stone(std::array<std::array<int, 10>, 10> board, int *c1, int *c2){
    int i, j;
	
    *c1 = 0;
    *c2 = 0;
    for (i = 1; i <= 8; i++) {
        for (j = 1; j <= 8; j++) {
            switch (board[i][j]) {
                case 1 : 
                    (*c1)++; 
                    break;
                case 2 : 
                    (*c2)++; 
                    break;
            }
        }
    }
}
void print_board(std::array<std::array<int, 10>, 10> board){
	auto bx_iter = board.begin();

	std::cout << "   a b c d e f g h" << std::endl;
	std::cout << "  ----------------- " << std::endl;

	while( bx_iter != board.end() )	{
		auto by_iter = (*bx_iter).begin();
		auto bx_num = std::distance(board.begin(), bx_iter);
//			auto bx_num = bx_iter - board.begin(); ‚à‚±‚Ìê‡‚Í“¯‚¶
		if(bx_num < 1 || bx_num > 8){
			++bx_iter;
			continue;
		}
		
		std::cout << bx_num << "|";
		
		while(by_iter != (*bx_iter).end()){
			if(*by_iter != -1)
				std::cout << " " << *by_iter;
			++by_iter;
		}
		std::cout << " |"<< std::endl;
		++bx_iter;
	}

	std::cout << "  ----------------- " << std::endl;

}

int init(std::array<std::array<int, 10>, 10> &board){
	// -1: range out / 0: no stone / 1 : white / 2: black
	static const std::array<std::array<int, 10>, 10> initboard = 
		{{ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  2,  1,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  1,  2,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1,  0,  0,  0,  0,  0,  0,  0,  0, -1}},
		  {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}} }};
	board = initboard;

}

int game(){

	std::array<std::array<int, 10>, 10> board;
	init(board);

	int p = 0, q = 0, player = 1, c1 = 0, c2 = 0;
	while(1){
		print_board(board);
		if(!exist_legal_move(board, player)){
			std::cout << "Player " << player << " has no legal moves > PASS" << std::endl;
			player = player_versus(player);
			if(!exist_legal_move(board, player)){
				std::cout << "Player " << player << " has no legal moves > PASS" << std::endl;
				break;
			}
		}
		get_move(board, player, &p, &q);
		set_and_turn_over(board, player, p, q);
		player = player_versus(player);
	}
	count_stone(board, &c1, &c2);
	std::cout << "Game Over" << std::endl;
	std::cout << "Player 1: " << c1 << std::endl << "Player 2: " << c2 << std::endl;
	return c1 - c2;
}

int main(){

	std::string buf;
	std::cout << "Reversi Game" << std::endl;
	do{
		game();
		std::cout << "again? (y/n) > ";
		while(1){
			std::cin >> buf;
			if(buf.size() != 0) break;
			std::cout << " > ";
		}
		if(buf.at(0) != 'y') break;
	}while(1);

//	std::array<int, 10> testarr = {-1, 0, 1, 2, 2, 2, 1, 1, 0, -1};
//	auto res = check(board, 3, 3, 1, 1);
//	std::cout << res << std::endl;
}
