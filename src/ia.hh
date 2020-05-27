#pragma once

#include "chessboard.hh"
#include "move.hh"

namespace ia
{
    std::string move_to_string(board::Move move);
    board::Move search(board::Chessboard chessboard);
    board::Move string_to_move(board::Chessboard board, std::string string_move);

    float evaluate(board::Chessboard chessboard);
}
