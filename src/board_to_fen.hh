#include "chessboard.hh"

#include <string>

std::string board_to_fen(board::Chessboard chessboard);

std::string fen_piece_placement(board::Chessboard chessboard);

std::string piece_to_fen(std::optional<std::pair<board::PieceType, board::Color>> piece);
