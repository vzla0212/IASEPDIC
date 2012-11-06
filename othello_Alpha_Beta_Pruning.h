int alpha_beta_pruning(state_t state, int d, int alpha, int beta, bool Player) {
    if (state.terminal() || d == 0) {
        //std::cout<<"hola1";
        return state.value();
    }
    bool existOne=false;

    if (Player) {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                existOne=true;
                alpha = std::max(alpha, alpha_beta_pruning(state.move(1, pos), d - 1, alpha, beta, 0));
                if (alpha >= beta) {
                    break;
                }
            }     
        }
        if(!existOne){
            alpha =std::max(alpha,alpha_beta_pruning(state, d - 1, alpha, beta, 0));
        }
        return alpha;
    } else {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                existOne=true;
                beta = std::min(beta, alpha_beta_pruning(state.move(0, pos), d - 1, alpha, beta, 1));
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if(!existOne){
            beta = std::min(beta, alpha_beta_pruning(state, d - 1, alpha, beta, 1));
        }
        return beta;
    }
}

int alpha_beta_pruning_TT(state_t state, int d, int alpha, int beta, bool Player) {
    
    hash_table_t::iterator it = dd.find(state);
    if (it != dd.end()) {
        return getValue(it->second);
    }
    
    if (state.terminal() || d == 0) {
        //std::cout<<"hola1";
        insert_hash(state, beta);        
        return state.value();
    }
    
    bool existOne=false;

    if (Player) {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                existOne=true;
                alpha = std::max(alpha, alpha_beta_pruning_TT(state.move(1, pos), d - 1, alpha, beta, 0));
                if (alpha >= beta) {
                    break;
                }
            }     
        }
        if(!existOne){
            alpha =std::max(alpha,alpha_beta_pruning(state, d - 1, alpha, beta, 0));
        }
        insert_hash(state, beta);
        return alpha;
    } else {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                existOne=true;
                beta = std::min(beta, alpha_beta_pruning_TT(state.move(0, pos), d - 1, alpha, beta, 1));
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if(!existOne){
            beta = std::min(beta, alpha_beta_pruning(state, d - 1, alpha, beta, 1));
        }
        insert_hash(state, beta);
        return beta;
    }
}
