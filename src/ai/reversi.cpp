#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

const int DEPTH = 2;

const int DIRECTIONS = 8;
const int BOARD_SIZE = 64, BOARD_LEN = 8;

const int ROW[DIRECTIONS] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int COL[DIRECTIONS] = {0, +1, +1, +1, 0, -1, -1, -1};

const pair < int, int > CORNERS[4] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};

int CELL_SCORE[BOARD_LEN][BOARD_LEN] = {
        {20, -3, 11,  8,  8,  11, -3,  20},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {11, -4,  2,  2,  2,  2,  -4 , 11},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {8,   1,  2, -3, -3,  2,   1,  8},
        {11, -4,  2,  2,  2,  2,  -4,  11},
        {-3, -7, -4,  1,  1, -4,  -7, -3},
        {20, -3, 11,  8,  8,  11, -3,  20}};

class State {
public:

	int all_moves = 0;

    bool player[BOARD_LEN][BOARD_LEN];          
    bool opponent[BOARD_LEN][BOARD_LEN];     

    State(bool starting = false) { reset(starting); }

    void reset(bool starting) {
	    all_moves = 0;
        for(int i = 0; i < BOARD_LEN; i++) {
            for(int j = 0; j < BOARD_LEN; j++) {
                player[i][j] = opponent[i][j] = false;
            }
        }
        player[3][4] = player[4][3] = true;   
        opponent[3][3] = opponent[4][4] = true;

        if(!starting) swap_players();
    }

    inline void set_player_cell(int row, int col, bool value) {
        if(good_position(row, col)) player[row][col] = value;
    }

    inline bool get_player_cell(int row, int col) const {
        return good_position(row, col) & player[row][col];
    }

    inline void set_opponent_cell(int row, int col, bool value) {
        if(good_position(row, col)) opponent[row][col] = value;
    }

    inline bool get_opponent_cell(int row, int col) const {
        return good_position(row, col) & opponent[row][col];
    }
    
    void swap_players() {
        swap(player, opponent);
    }

    void make_move(int row, int col) {
	    all_moves++;
        set_player_cell(row, col, true);
        for(int d = 0; d < DIRECTIONS; d++) {
            if(!possible_move(row, col, d)) continue;
            int new_row = row + ROW[d];
            int new_col = col + COL[d];
            while(get_opponent_cell(new_row, new_col)) {
                set_player_cell(new_row, new_col, true);
                set_opponent_cell(new_row, new_col, false);
                new_row += ROW[d];
                new_col += COL[d];
            }
        }
    }

    inline bool good_position(int row, int col) const {
        return (row >= 0 && row < 8) && (col >= 0 && col < 8);
    } 

    bool possible_move(int row, int col, int d) const {
        row += ROW[d], col += COL[d];
        if(!good_position(row, col) || !get_opponent_cell(row, col)) return false;
        while(good_position(row, col) && get_opponent_cell(row, col)) {
            row += ROW[d];
            col += COL[d];
        }
        return (good_position(row, col) && get_player_cell(row, col));
    }

    vector < pair < int, int > > get_actions() const {
        vector < pair < int, int > > res;
        for(int row = 0; row < BOARD_LEN; row++) {
            for(int col = 0; col < BOARD_LEN; col++) {
                if(get_player_cell(row, col) || get_opponent_cell(row, col)) continue;
                for(int d = 0; d < DIRECTIONS; d++) {
                    if(possible_move(row, col, d)) {
                        res.push_back({row, col});
                        break;
                    }
                }
            }
        }
        return res;
    }

    int utility() const {
        int res = 0;
        for(int i = 0; i < BOARD_LEN; i++) {
            for(int j = 0; j < BOARD_LEN; j++) {
                if(get_player_cell(i, j)) res++;
                else if(get_opponent_cell(i, j)) res--;
            }
        }
        return res;
    }

    inline int calculate_ratio(int player, int opponent) const {
        return 100 * ((double)(player - opponent)) / (player + opponent);
    }

    int heuristic_value() const {
        int board_bilans = 0;
        int player_cells = 0;
        int opponent_cells = 0;
        for(int i = 0; i < BOARD_LEN; i++) {
            for(int j = 0; j < BOARD_LEN; j++) {
                if(get_player_cell(i, j)) {
                    board_bilans += CELL_SCORE[i][j];
                    player_cells++;
                }else if(get_opponent_cell(i, j)) {
                    board_bilans -= CELL_SCORE[i][j];
                    opponent_cells++;
                }
            }
        }

        int ratio = calculate_ratio(player_cells, opponent_cells);

        int player_corners = 0;
        int opponent_corners = 0;

        for(pair < int, int > p : CORNERS) {
            int row = p.X, col = p.Y;
            if(get_player_cell(row, col)) player_corners++;
            else if(get_opponent_cell(row, col)) opponent_corners++;
        }

        int corner_ratio = 0;
        if(player_corners + opponent_corners)
            corner_ratio = calculate_ratio(player_corners, opponent_corners);


        int player_close_corners = 0;
        int opponent_close_corners = 0;
        for(pair < int, int > p : CORNERS) {
            int row = p.X, col = p.Y;
            if((get_player_cell(row, col) || get_opponent_cell(row, col))) continue;
            for(int d = 0; d < DIRECTIONS; d++) {
                int new_row = row + ROW[d], new_col = col + COL[d];
                if(good_position(new_row, new_col)) {
                    if(get_player_cell(new_row, new_col)) player_close_corners++;
                    else if(get_opponent_cell(new_row, new_col)) opponent_close_corners++;
                }
            }
        }

        int corners_heura = (player_close_corners - opponent_close_corners);
        
        return ((10 * ratio) + (800 * corner_ratio) + (-4560 * corners_heura) + (80 * board_bilans));
    }

    bool terminal() const {
        auto act = get_actions();
        // cout << "rozmiar = ";
        // cout << act.size() << "\n";
        return act.empty();
    }

    bool REAL_TERMINAL() const {
        return all_moves >= 60;
    }

    inline bool terminal(vector < pair < int, int > > actions) const {
        return actions.empty();
    }

    void make_action(int row, int col) {
        if(row != -1 && col != -1) make_move(row, col);
        swap_players();
    }

    State make_new_state(int row, int col) {
        State res = *this;
        res.make_action(row, col);
        return res;
    }

};

class AI {

    const int MAX_DEPTH = DEPTH;
    const int MAXI = 1, MINI = 0;
    const int INF = 1e9;

public:

    pair < int, int > get_bets_action(State *state) {
        return AlphaBetaRoot(state);
    }
    
    pair < int, int > AlphaBetaRoot(State *state) {   
        int best_value = -INF;
        pair < int, int > best_move = {-1, -1};
        vector<pair < int, int > > actions = state->get_actions();

        for(pair < int, int > p : actions) {
            int row = p.X, col = p.Y;
            State new_state = state->make_new_state(row, col);
            int value = AlphaBeta(&new_state, MAX_DEPTH, MINI, -INF, +INF);
            if(value > best_value) {
                best_value = value;
                best_move = {row, col};
            }
        }

        return best_move;
    }

    int AlphaBeta(State *state, int depth, int player, int alpha, int beta) {
        vector < pair < int, int > > actions = state->get_actions();

        // if(depth == MAX_DEPTH && state.terminal(actions)) { powinno działać, ale nie przetestowane, tzn jeśli ruch, któy wykonam pozbawi przeciwnika ruchu to chce go wykonać
            // return INF;
        // }

        if(state->terminal(actions)) {
            State next = state->make_new_state(-1, -1);
            if(next.terminal()) return state->utility() * (player == MAXI ? 1 : -1);
            else return AlphaBeta(&next, depth, 1 - player, alpha, beta);
        }

        if(depth == 0) return state->heuristic_value() * (player == MAXI ? 1 : -1);

        int best_value = (player == MAXI ? -INF : +INF);
        for(pair < int, int > p : actions) {
            int row = p.X, col = p.Y;
            State new_state = state->make_new_state(row, col);
            int value = AlphaBeta(&new_state, depth - 1, 1 - player, alpha, beta);
            if(player == MAXI) {
                best_value = max(best_value, value);
                alpha = max(alpha, value);
            }
            else {
                best_value = min(best_value, value);
                beta = min(beta, value);
            }
            if(alpha >= beta) break;
        }
        return best_value;
    }
};


void todo(string s) {
    cout << s << "\n";
    fflush(stdout);
}

void todo(int row, int col) {
    swap(row, col);
    cout << "IDO" << " " << row << " " << col << "\n";
    fflush(stdout);
}

#define Move pair < int, int >

class Random {

public: 

    Random() { srand(time(NULL)); }

    Move generate_next_move(State* state) {            
        vector < Move > moves = state->get_actions();
        if(state->terminal(moves)) return {-1, -1};
        return moves[rand() % moves.size()];
    }
};

void loop() {

    State Game;
    Random Losowy;
    AI Ai;

    int GAMES = 1e3;

    int bilans[3] = {0, 0, 0};
    
    for(int game = 0; game < GAMES; game++) {
        int turn = (game < GAMES / 2 ? 1 : 0);
        int ile_ruchow = 0;
        Game.reset(turn);
        Move pre_move = {-1, -1};
        while(!(Game.REAL_TERMINAL())) {
            Move move = {-1, -1};
            // cout << turn << "\n";
            if(!turn) {
                move = Ai.get_bets_action(&Game);
                // move = Losowy.generate_next_move(&Game);
                // cout << turn << " " << move.first << " " << move.second << "\n";

            } else {
                // move = Ai.get_bets_action(&Game);
                move = Losowy.generate_next_move(&Game);
                // cout << turn << " " << move.first << " " << move.second << "\n";
            }
            // cout << turn << "\n";
            // cout << move.first << " " << move.second << "\n";
            ile_ruchow++;
            Game.make_action(move.first, move.second); // tutaj zła nazwa była
            // cout << turn << "\n";
            turn = 1 - turn;
            if(pre_move == move && move == make_pair(-1, -1)) break;
            pre_move = move;
        }
        // cout << "ile ruchów: " << ile_ruchow << "\n";
        // cout << Game.all_moves << "\n";
        int wynik = Game.utility();
        cout << "Game " << game << ": ";
        if(wynik == 0) {
            bilans[2]++; // remis
            cout << "DRAW\n";
        } else {
            int who = (wynik > 0 ? turn : 1 - turn);
            bilans[who]++;
            cout << "P" << char((who) + '0') << " WIN\n";
        }
        // cout << bilans[0] << " " << bilans[1] << " " << bilans[2] << "\n";
    }
    cout << bilans[0] << " " << bilans[2]<< " " << bilans[1] << "\n";

}

int Xmain() {

    State Game(true);
    AI Ai;
    double t0, t1;

    todo("RDY");

    while(true) {

        string str;
        cin >> str;

        if(str == "BYE") break;
        if(str == "UGO") {
            cin >> t0 >> t1;

            auto p = Ai.get_bets_action(&Game);

            todo(p.Y, p.X);

            Game.make_action(p.X, p.Y);

        } else if(str == "HEDID") {
            cin >> t0 >> t1;

            int row, col; cin >> col >> row;
            swap(row, col);

            Game.make_action(row, col);
            
            auto p = Ai.get_bets_action(&Game);

            todo(p.Y, p.X);

            Game.make_action(p.X, p.Y);

        } else if(str == "ONEMORE") {
            Game.reset(true);
            todo("RDY");
        }

    }
    return 0;
}

int main() {
    loop();
}

 
