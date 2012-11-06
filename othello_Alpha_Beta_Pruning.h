int alpha_beta_pruning(state_t state, int d, int alpha, int beta, bool Player) {
    generados++;
    if (state.terminal()) {
        insert_hash(state, state.value(), 0);
        return state.value();
    }
    bool existOne = false;

    if (Player) {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                expandidos++;
                existOne = true;
                alpha = std::max(alpha, alpha_beta_pruning(state.move(1, pos), d - 1, alpha, beta, 0));
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if (!existOne) {
            alpha = std::max(alpha, alpha_beta_pruning(state, d - 1, alpha, beta, 0));
        }
        return alpha;
    } else {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                expandidos++;
                existOne = true;
                beta = std::min(beta, alpha_beta_pruning(state.move(0, pos), d - 1, alpha, beta, 1));
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if (!existOne) {
            beta = std::min(beta, alpha_beta_pruning(state, d - 1, alpha, beta, 1));
        }
        return beta;
    }
}

int alpha_beta_pruning_TT(state_t state, int d, int alpha, int beta, bool Player) {
    generados++;
    if (state.terminal()) {
        //insert_hash(state, state.value(), 0);
        return state.value();
    }

    hash_table_t::iterator it = dd.find(state);
    if (it != dd.end()) {
        if ((it->second).option == 0) {
            return getValue(it->second);
        }
        if (((it->second).option == 1) && Player) {
            alpha = std::max(alpha, getValue(it->second));
        }
        if (((it->second).option == 2) && !Player) {
            beta = std::min(beta, getValue(it->second));
        }
    }

    bool existOne = false;

    if (Player) {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_black_move(pos))) {
                existOne = true;
                int abp = alpha_beta_pruning_TT(state.move(1, pos), d - 1, alpha, beta, 0);
                if (alpha < abp && abp < beta) {
                    insert_hash(state.move(1, pos), abp, 0);
                }
                if (abp < alpha) {
                    insert_hash(state.move(1, pos), abp, 2);
                }
                if (beta < abp) {
                    insert_hash(state.move(1, pos), abp, 1);
                }
                alpha = std::max(alpha, abp);
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if (!existOne) {
            alpha = std::max(alpha, alpha_beta_pruning(state, d - 1, alpha, beta, 0));
        }
        return alpha;
    } else {
        //gather possible moves for succersors
        for (int pos = 0; pos < DIM; ++pos) {
            if ((state.is_white_move(pos))) {
                existOne = true;
                int abp = alpha_beta_pruning_TT(state.move(0, pos), d - 1, alpha, beta, 1);

                if (alpha < abp && abp < beta) {
                    insert_hash(state.move(0, pos), abp, 0);
                }
                if (abp < alpha) {
                    insert_hash(state.move(0, pos), abp, 2);
                }
                if (beta < abp) {
                    insert_hash(state.move(0, pos), abp, 1);
                }

                beta = std::min(beta, abp);
                if (alpha >= beta) {
                    break;
                }
            }
        }
        if (!existOne) {
            beta = std::min(beta, alpha_beta_pruning(state, d - 1, alpha, beta, 1));
        }
        return beta;
    }
}
