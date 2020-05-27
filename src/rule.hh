#pragma once

#include <vector>
#include "position.hh"
#include "move.hh"
#include "color.hh"


namespace board
{
    class Chessboard;

    class Rule
    {
    public:
        std::vector<Move> generate_pawn_moves(Chessboard chessboard, Position position);

        std::vector<Move> generate_bishop_moves(Chessboard chessboard, Position position);

        std::vector<Move> generate_knight_moves(Chessboard chessboard, Position position);

        std::vector<Move> generate_rook_moves(Chessboard chessboard, Position position);

        std::vector<Move> generate_queen_moves(Chessboard chessboard, Position position);

        std::vector<Move> generate_king_moves(Chessboard chessboard, Position position);

        bool check_double_pawn_push(Chessboard chessboard, Position start, Position end);

        bool check_king_castling(Chessboard chessboard, Position start, Position end);

        bool check_queen_castling(Chessboard chessboard, Position start, Position end);

        bool check_en_passant(Chessboard chessboard, Position start, Position end);
    };
} //namespace board
