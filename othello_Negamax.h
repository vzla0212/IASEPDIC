
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

void insert_hash_aux(state_t state, int value, int option) {
    stored_info_t info;
    info.value = value;
    info.option = option;
    pp.insert(std::make_pair(state, info));
}

int Negamax_TT(state_t state, int d, int alpha, int beta, int color) {
    int Player;
    color == 1 ? Player = 1 : Player = 0;

    if (Player == 1) {
        hash_table_t::iterator it = dd.find(state);
        if (it != dd.end()) {
            if ((it->second).option == 0) {
                return getValue(it->second);
            }
            if ((it->second).option == 1) {
                alpha = std::max(alpha, getValue(it->second));

            }
            if ((it->second).option == 2) {
                beta = std::min(beta, getValue(it->second));
            }
        }
    } else {
        hash_table_t::iterator it = pp.find(state);
        if (it != pp.end()) {
            if ((it->second).option == 0) {
                return getValue(it->second);
            }
            if (((it->second).option == 1)) {
                alpha = std::max(alpha, getValue(it->second));

            }
            if (((it->second).option == 2)) {
                beta = std::min(beta, getValue(it->second));
            }
        }
    }

    if (state.terminal()) {
        
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
        int val = -Negamax_TT(state.move(Player, valid_moves[i]), d - 1, -beta, -alpha, -color);

        if (val >= beta) {
            if (Player == 1) {
                insert_hash(state, beta, 1);
            } else {
                insert_hash_aux(state, beta, 1);
            }
            return val;
        }
        if (val >= alpha) {
            alpha = val;
        }
    }
    if (Player == 1) {
        insert_hash(state, alpha, 2);
    } else {
        insert_hash_aux(state, alpha, 2);
    }
    return alpha;
}