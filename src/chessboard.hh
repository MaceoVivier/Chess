#pragma once

#include "chessboard-interface.hh"
#include "move.hh"
#include "rule.hh"
#include "listener.hh"
#include "pgn-move.hh"
#include <iostream>
#include <vector>

namespace board
{
    class Chessboard : public ChessboardInterface
    {
    public:
        void init_board();

        void init_fenstr(std::string s);

        std::vector<Move> generate_legal_moves();

        std::vector<Move> simply_generate_legal_moves();

        void print();

        int do_move(Move move);

        void simply_do_move(Move move); //sert pour check le échec et mat

        bool is_move_legal(Move move); //sert à savoir si on disqualifie le joueur ou non

        bool is_check(); //renvoie vrai si le coup qui vient d'être mis met en échec l'adversaire

        Position find_king(Color king_color);

        bool is_checkmate();

        bool is_pat();

        bool is_draw();

        int init_perft(const std::string& file);

        std::optional<Position> en_passant_get();
        bool white_king_castling_get();
        bool white_queen_castling_get();
        bool black_king_castling_get();
        bool black_queen_castling_get();

        long long compute_depth(int d);

        void undo_move(Move move, bool wkc, bool wqc, bool bkc, bool bqc,
                std::optional<Position> ep);

        Move pgn_to_move(PgnMove m);

        opt_piece_t operator[](const Position& position) const;

        void add_listener(listener::Listener* listener);

        opt_piece_t board_[8][8];

        void change_turn();

        bool white_turn();

    private:
        Rule rules;
        bool white_turn_;
        bool white_king_castling_; //si les tours et le roi n'ont pas bougé, pas s'il y a la place
        bool white_queen_castling_;
        bool black_king_castling_;
        bool black_queen_castling_;
        std::optional<Position> en_passant_;
        unsigned int turn_;
        unsigned int last_fifty_turn_;

        std::vector<listener::Listener*> listeners_vec;
    };
} // namespace board
