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

int Negamax_TT(state_t state, int d, int alpha, int beta, int color) {
    int Player;
    if (state.terminal() || d == 0) {
        insert_hash(state,state.value());
        return color * state.value();
    }

    hash_table_t::iterator it = dd.find(state);
    if (it != dd.end()) {
        //  std::cout << "HASH SE USO"<< std::endl;
        return getValue(it->second);          
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

            return val;
        }
        if (val >= alpha) {
            alpha = val;
        }
    }
    return alpha;
}
