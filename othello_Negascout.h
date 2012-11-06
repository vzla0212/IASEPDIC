int NegascoutG(state_t state, int d, int alpha, int beta); //Para poder realizar la doble llamada recursiva

int NegascoutF(state_t state, int d, int alpha, int beta)
{
    if (d == 0 || state.terminal()) {
        return state.value();
    }

    int m = -1000000000;
    std::vector<int> valid_moves;
    for (int pos = 0; pos < DIM; ++pos) {
        if ((state.is_black_move(pos))) {
            valid_moves.push_back(pos);
        }
    }
    if (valid_moves.size() == 0) {
        valid_moves.push_back(36);
    }
    m = MAX(m, NegascoutG(state.move(1, valid_moves[0]), d - 1, alpha, beta));
    //std::cout<<"g"<<std::endl; 
    if (m >= beta) {
        return m;
    }
    for (int i = 1; i < valid_moves.size(); i++) {
        int t = NegascoutG(state.move(1, valid_moves[i]), d - 1, m, m + 1);
        if (t > m) {
            if (t >= beta) {
                m = t;
            } else {
                m = NegascoutG(state.move(1, valid_moves[i]), d - 1, t, beta);
            }
        }
        if (m >= beta) {
            return m;
        }
    }
    return m;

}

int NegascoutG(state_t state, int d, int alpha, int beta) {
    if (d == 0 || state.terminal()) {
        return state.value();
    }

    int m = 1000000000;
    std::vector<int> valid_moves;
    for (int pos = 0; pos < DIM; ++pos) {
        if ((state.is_white_move(pos))) {
            valid_moves.push_back(pos);
        }
    }
    
    
    
    
    
    
    
    if (valid_moves.size() == 0) {
        valid_moves.push_back(36);
    }
    m = MIN(m, NegascoutF(state.move(0, valid_moves[0]), d - 1, alpha, beta));
    if (m <= alpha) {
        return m;
    }
    
    
    
    for (int i = 1; i < valid_moves.size(); i++) {
        int t = NegascoutF(state.move(0, valid_moves[i]), d - 1, m, m + 1);
        if (t <= m) {
            if (t <= alpha) {
                m = t;
            } else {
                m = NegascoutF(state.move(0, valid_moves[i]), d - 1, alpha, t);
            }
        }
        if (m <= alpha) {
            return m;
        }
    }
    return m;
}

//NEGASCOUT CON TABLAS

int NegascoutG_TT(state_t state, int d, int alpha, int beta); //Para poder realizar la doble llamada recursiva

int NegascoutF_TT(state_t state, int d, int alpha, int beta) {
    if (d == 0 || state.terminal()) {
        
        return state.value();
    }

    hash_table_t::iterator it = dd.find(state);
    if (it != dd.end()) {
        //  std::cout << "HASH SE USO"<< std::endl;
        return getValue(it->second);
    }



    int m = -1000000000;
    std::vector<int> valid_moves;
    for (int pos = 0; pos < DIM; ++pos) {
        if ((state.is_black_move(pos))) {
            valid_moves.push_back(pos);
        }
    }
    if (valid_moves.size() == 0) {
        valid_moves.push_back(36);
    }
    m = MAX(m, NegascoutG_TT(state.move(1, valid_moves[0]), d - 1, alpha, beta));
    //std::cout<<"g"<<std::endl; 
    if (m >= beta) {
        return m;
    }
    for (int i = 1; i < valid_moves.size(); i++) {
        int t = NegascoutG_TT(state.move(1, valid_moves[i]), d - 1, m, m + 1);
        if (t > m) {
            if (t >= beta) {
                m = t;
            } else {
                m = NegascoutG_TT(state.move(1, valid_moves[i]), d - 1, t, beta);
            }
        }
        if (m >= beta) {
            return m;
        }
    }
    return m;

}

int NegascoutG_TT(state_t state, int d, int alpha, int beta) {
    if (d == 0 || state.terminal()) {
        return state.value();
    }

    hash_table_t::iterator it = dd.find(state);
    if (it != dd.end()) {
        //  std::cout << "HASH SE USO"<< std::endl;
        return getValue(it->second);
    }

    int m = 1000000000;
    std::vector<int> valid_moves;
    for (int pos = 0; pos < DIM; ++pos) {
        if ((state.is_white_move(pos))) {
            valid_moves.push_back(pos);
        }
    }
    if (valid_moves.size() == 0) {
        valid_moves.push_back(36);
    }
    m = MIN(m, NegascoutF_TT(state.move(0, valid_moves[0]), d - 1, alpha, beta));
    if (m <= alpha) {
        return m;
    }
    for (int i = 1; i < valid_moves.size(); i++) {
        int t = NegascoutF_TT(state.move(0, valid_moves[i]), d - 1, m, m + 1);
        if (t <= m) {
            if (t <= alpha) {
                m = t;
            } else {
                m = NegascoutF_TT(state.move(0, valid_moves[i]), d - 1, alpha, t);
            }
        }
        if (m <= alpha) {
            return m;
        }
    }
    return m;
}
