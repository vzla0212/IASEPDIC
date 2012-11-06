
int Negamax(state_t state, int d, int alpha, int beta, int color) {
    int Player;
    if (state.terminal() || d == 0) {
        return color * state.value();
    }
    //array to store the possible moves that can be done
    std::vector<int> valid_moves;
    if (color == 1) {
        Player = 1;
        //get possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                valid_moves.push_back(pos);
            }
        }
        //if no moves can be done the state is his own son
        if (valid_moves.size() == 0) {
            valid_moves.push_back(36); //a move to pos 36 produces the same state
        }
    }
    if (color == -1) {
        Player = 0;
        //get possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                valid_moves.push_back(pos);
            }
        }
        //if no moves can be done the state is his own son
        if (valid_moves.size() == 0) {
            valid_moves.push_back(36); //a move to pos 36 produces the same state
        }

    }
    for (int i = 0; i < valid_moves.size(); i++) {
        int val = -Negamax(state.move(Player, valid_moves[i]), d - 1, -beta, -alpha, -color);

        if (val >= beta) {
            return val;
        }
        if (val >= alpha) {
            alpha = val;
        }
    }
    return alpha;
}



hash_table_t pp;

void insert_hash_aux(state_t state, int value, int option)
 {
    stored_info_t info;
    info.value = value;
    info.option=option;
    pp.insert(std::make_pair(state, info)) ;
 }



int Negamax_TT(state_t state, int d, int alpha, int beta, int color) {
    int Player;
    color == -1 ? Player = 0 : Player = 1;
    if (state.terminal() || d == 0) {
        return color * state.value();
    }
    if (Player == 0) {
        hash_table_t::iterator it = dd.find(state);
        if (it != dd.end()) {
            if ((it->second).option == 0) {
                return getValue(it->second);
            }
            if (((it->second).option == 1) && !Player) {
                if (alpha < getValue(it->second)) {
                    alpha = getValue(it->second);
                }
            }
            if (((it->second).option == 2) && Player) {
                if (beta > getValue(it->second)) {
                    beta = getValue(it->second);
                }
            }
        }
    } else {

        hash_table_t::iterator it = pp.find(state);
        if (it != pp.end()) {
            if ((it->second).option == 0) {
                return getValue(it->second);
            }
            if (((it->second).option == 1) && Player) {
                if (alpha < getValue(it->second)) {
                    alpha = getValue(it->second);
                }
            }
            if (((it->second).option == 2) && !Player) {
                if (beta > getValue(it->second)) {
                    beta = getValue(it->second);
                }
            }
        }

    }

    //array to store the possible moves that can be done
    std::vector<int> valid_moves;
    if (color == 1) {
        Player = 1;
        //get possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                valid_moves.push_back(pos);
            }
        }
        //if no moves can be done the state is his own son
        if (valid_moves.size() == 0) {
            valid_moves.push_back(36); //a move to pos 36 produces the same state
        }
    }
    if (color == -1) {
        Player = 0;
        //get possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                valid_moves.push_back(pos);
            }
        }
        //if no moves can be done the state is his own son
        if (valid_moves.size() == 0) {
            valid_moves.push_back(36); //a move to pos 36 produces the same state
        }

    }
    for (int i = 0; i < valid_moves.size(); i++) {
        int val = -Negamax_TT(state.move(Player, valid_moves[i]), d - 1, -beta, -alpha, -color);
        if (Player == 0) {
            if (-beta < val && val < -alpha) {
                insert_hash(state.move(Player, valid_moves[i]), val, 0);

            }

            if (val < -beta) {
                insert_hash(state.move(Player, valid_moves[i]), val, 2);

            }

            if (-alpha < val) {
                insert_hash(state.move(Player, valid_moves[i]), val, 1);
            }

        } else {

            if (-beta < val && val < -alpha) {
                insert_hash_aux(state.move(Player, valid_moves[i]), val, 0);
            }

            if (val < -beta) {
                insert_hash_aux(state.move(Player, valid_moves[i]), val, 2);
            }

            if (-alpha < val) {
                insert_hash_aux(state.move(Player, valid_moves[i]), val, 1);
            }

        }

        if (val >= beta) {
            return val;
        }
        if (val >= alpha) {
            alpha = val;
        }
    }

    return alpha;
}
