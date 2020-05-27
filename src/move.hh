#pragma once

#include <iostream>
#include "piece-type.hh"
#include "position.hh"

namespace board
{
    class Move
    {
    public:
        Move(Position start,
                Position destination,
                PieceType piece,
                PieceType promotion,
                PieceType capture,
                bool double_pawn_push,
                bool king_castling,
                bool queen_castling,
                bool en_passant);

        Position start_get();
        Position destination_get();
        PieceType piece_get();
        PieceType promotion_get();
        PieceType capture_get();
        bool double_pawn_push_get();
        bool king_castling_get();
        bool queen_castling_get();
        bool en_passant_get();

        bool operator==(Move other) const;
    private:
        Position start_;
        Position destination_;
        PieceType piece_;
        PieceType promotion_;
        PieceType capture_;
        bool double_pawn_push_;
        bool king_castling_;
        bool queen_castling_;
        bool en_passant_;
    };
} // namespace board
