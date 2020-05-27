#include "ia.hh"

namespace ia
{
    int string_to_int_file(char file)
    {
        switch (std::tolower(file))
        {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return 0;
        }
    }

    board::Move string_to_move(board::Chessboard board,
            std::string string_move)
    {
        board::PieceType piecetype = board::PieceType::NONE;
        board::PieceType capture = board::PieceType::NONE;
        board::PieceType promotion = board::PieceType::NONE;

        board::File f = board::File(string_to_int_file(string_move[0]));
        board::Rank r = board::Rank(string_move[1] - '0');

        board::Position pos = board::Position(f, r);


        auto color = std::get<1>(board[pos].value());
        auto piece = std::get<0>(board[pos].value());
        std::vector<board::Move> moves;

        int file = pos.convert_file();
        int rank = pos.convert_rank();

        std::string destination = "";

        if (color == board::Color::WHITE && piece == board::PieceType::PAWN)
        {
            if (rank == 1
                    && board[board::Position(board::File(file),
                        board::Rank(rank + 2))] == std::nullopt
                    && board[board::Position(board::File(file),
                        board::Rank(rank + 1))] == std::nullopt)
            {
                        return board::Move(pos,
                                board::Position(board::File(file),
                                    board::Rank(rank + 2)),
                                piece, board::PieceType::NONE,
                                board::PieceType::NONE,
                                true, false, false, false);
            }

            if (rank == 4) //pour le en passant
            {
                if (board.en_passant_get().has_value())
                {
                    if (file > 0
                            && board.en_passant_get().value()
                            .convert_file() == file - 1
                            && !board[board::Position(board::File(file - 1),
                                board::Rank(5))].has_value())
                    {
                            return board::Move(pos,
                                board::Position(board::File(file - 1),
                                    board::Rank(5)),
                                piece, board::PieceType::NONE,
                                board::PieceType::PAWN,
                                false, false, false, true);
                    }

                    if (file < 7
                            && board.en_passant_get().value()
                            .convert_file() == file + 1
                            && !board[board::Position(board::File(file + 1),
                                board::Rank(5))].has_value())
                    {
                            return board::Move(pos,
                                board::Position(board::File(file + 1),
                                    board::Rank(5)),
                                piece, board::PieceType::NONE,
                                board::PieceType::PAWN,
                                false, false, false, true);
                    }
                }
            }
        }

        else if (color == board::Color::BLACK && piece == board::PieceType::PAWN)
        {
            if (rank == 6
                    && board[board::Position(board::File(file),
                        board::Rank(rank - 1))] == std::nullopt
                    && board[board::Position(board::File(file),
                        board::Rank(rank - 2))] == std::nullopt)
            {
                        return board::Move(pos,
                            board::Position(board::File(file),
                                board::Rank(rank - 2)),
                                piece, board::PieceType::NONE,
                                board::PieceType::NONE,
                                true, false, false, false);
            }

            if (rank == 3) //pour le en passant
            {
                if (board.en_passant_get().has_value())
                {
                    if (file > 0 && board.en_passant_get().value()
                            .convert_file() == file - 1
                            && !board[board::Position(board::File(file - 1),
                                board::Rank(2))].has_value())
                    {
                                return board::Move(pos,
                                    board::Position(board::File(file - 1),
                                        board::Rank(2)),
                                    piece, board::PieceType::NONE,
                                    board::PieceType::PAWN,
                                    false, false, false, true);
                    }

                    if (file < 7 && board.en_passant_get().value()
                            .convert_file() == file + 1
                            && !board[board::Position(board::File(file + 1),
                                board::Rank(2))].has_value())
                    {
                                return board::Move(pos,
                                    board::Position(board::File(file + 1),
                                        board::Rank(2)),
                                    piece, board::PieceType::NONE,
                                    board::PieceType::PAWN,
                                    false, false, false, true);
                    }
                }
            }
        }

        piecetype = std::get<0>(board[pos].value());

        if (string_move[2] == 'x')
        {
            capture =
                std::get<0>(board[board::Position(board::File(string_to_int_file(string_move[3])),
                        board::Rank(string_move[4] - '0'))].value());

            destination += string_move[3];
            destination += string_move[4];
        }

        else
        {
            destination += string_move[2];
            destination += string_move[3];
        }

        if (string_move.length() == 6)
        {
            char piece = string_move[5];

            if (piece == 'N')
                promotion = board::PieceType::KNIGHT;
            else if (piece == 'B')
                promotion = board::PieceType::BISHOP;
            else if (piece == 'R')
                promotion = board::PieceType::ROOK;
            else if (piece == 'Q')
                promotion = board::PieceType::QUEEN;

            else if (piece == 'n')
                promotion = board::PieceType::KNIGHT;
            else if (piece == 'b')
                promotion = board::PieceType::BISHOP;
            else if (piece == 'r')
                promotion = board::PieceType::ROOK;
            else if (piece == 'q')
                promotion = board::PieceType::QUEEN;

        }

        board::Position s =
            board::Position(board::File(string_to_int_file(string_move[0])),
                    board::Rank(string_move[1] - '0'));
        board::Position d =
            board::Position(board::File(string_to_int_file(destination[0])),
                    board::Rank(destination[1] - '0'));

        return board::Move(s, d, piecetype, promotion, capture,
                false, false, false, false);
    }

    std::string move_to_string(board::Move move)
    {
        std::string res = "";
        res += move.start_get().to_string();

        if (move.capture_get() != board::PieceType::NONE)
            res += "x";

        res += move.destination_get().to_string();

        if (move.promotion_get() != board::PieceType::NONE)
            res += piece_to_char(move.promotion_get());

        return res;
    }


    float white_pawn_position_val(board::Position pos)
    {
        float values[8][8] = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
                              {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
                              {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
                              {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
                              {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
                              {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
                              {0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
                              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float white_king_position_val(board::Position pos)
    {
        float values[8][8] = {{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                              {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                              {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                              {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                              {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
                              {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
                              {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
                              {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}};

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float white_rook_position_val(board::Position pos)
    {
        float values[8][8] = {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
                              {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
                              {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
                              {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
                              {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
                              {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
                              {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
                              {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}};

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float white_knight_position_val(board::Position pos)
    {
        float values[8][8] = {{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
                              {-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
                              {-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
                              {-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
                              {-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
                              {-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
                              {-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
                              {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0,-5.0}
        };

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float white_bishop_position_val(board::Position pos)
    {
        float values[8][8] = {{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
                              {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
                              {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
                              {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
                              {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
                              {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
                              {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
                              {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
        };

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float white_queen_position_val(board::Position pos)
    {
        float values[8][8] = {{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
                              {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
                              {-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
                              {-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
                              {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
                              {-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
                              {-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
                              {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
        };

        return values[pos.convert_rank()][pos.convert_file()];
    }

    float compute_val(board::PieceType type, board::Position pos,
            board::Color c)
    {
        if (type == board::PieceType::KING)
        {
            if (c == board::Color::WHITE)
                return 900 + white_king_position_val(pos);
            else
                return 900 + white_king_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }
        if (type == board::PieceType::PAWN)
        {
            if (c == board::Color::WHITE)
                return 10 + white_pawn_position_val(pos);
            else
                return 10 + white_pawn_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }

        if (type == board::PieceType::ROOK)
        {
            if (c == board::Color::WHITE)
                return 50 + white_rook_position_val(pos);
            else
                return 50 + white_rook_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }

        if (type == board::PieceType::KNIGHT)
        {
            if (c == board::Color::WHITE)
                return 30 + white_knight_position_val(pos);
            else
                return 30 + white_knight_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }

        if (type == board::PieceType::BISHOP)
        {
            if (c == board::Color::WHITE)
                return 30 + white_bishop_position_val(pos);
            else
                return 30 + white_bishop_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }

        if (type == board::PieceType::QUEEN)
        {
            if (c == board::Color::WHITE)
                return 90 + white_queen_position_val(pos);
            else
                return 90 + white_queen_position_val(board::Position(
                            pos.file_get(),
                            board::Rank(7 - pos.convert_rank())));
        }

        return 0;
    }

    float evaluate(board::Chessboard chessboard)
    {
        float total = 0;

        for (auto i = 0; i < 8; i++)
        {
            for (auto j = 0; j < 8; j++)
            {
                auto pos = board::Position(board::File(j),board::Rank(i));
                auto cell = chessboard[pos];

                if (!cell.has_value())
                    continue;

                auto color = std::get<1>(cell.value());
                float val = compute_val(std::get<0>(cell.value()), pos, color);

                if (color == board::Color::WHITE)
                    total += val;

                else
                    total -= val;
            }
        }
        return total;
    }

    float min_max(board::Chessboard chessboard, int depth, bool is_min)
    {
        if (depth == 0)
            return evaluate(chessboard);

        auto moves = chessboard.generate_legal_moves();
        float min = 1000;
        float max = -1000;

        for (size_t i = 0; i < moves.size(); i++)
        {
            chessboard.do_move(moves[i]);
            auto next_val = min_max(chessboard, depth - 1, !is_min);

            if (next_val < min)
                min = next_val;

            if (next_val > max)
                max = next_val;

            chessboard.undo_move(moves[i],
                    chessboard.white_king_castling_get(),
                    chessboard.white_queen_castling_get(),
                    chessboard.black_king_castling_get(),
                    chessboard.black_queen_castling_get(),
                    chessboard.en_passant_get());
        }

        if (is_min)
            return max;

        return min;
    }

    board::Move search(board::Chessboard chessboard)
    {
        auto moves = chessboard.generate_legal_moves();
        auto bestmove = moves[0];
        auto bestval = -1000;

        for (size_t i = 0; i < moves.size(); i++)
        {
            chessboard.do_move(moves[i]);
            auto next_val = min_max(chessboard, 1, false);

            if (next_val > bestval)
            {
                bestval = next_val;
                bestmove = moves[i];
            }
            chessboard.undo_move(moves[i],
                    chessboard.white_king_castling_get(),
                    chessboard.white_queen_castling_get(),
                    chessboard.black_king_castling_get(),
                    chessboard.black_queen_castling_get(),
                    chessboard.en_passant_get());
        }

        return bestmove;
    }
}
