#include "chessboard.hh"
#include "rule.hh"

namespace board
{
    std::vector<Move>
        Rule::generate_pawn_moves(Chessboard chessboard, Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());
        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        if (color == Color::WHITE)
        {
            if (rank == 1
                    && chessboard[Position(File(file),
                        Rank(rank + 2))] == std::nullopt
                    && chessboard[Position(File(file),
                        Rank(rank + 1))] == std::nullopt)
            {
                moves.push_back(Move(position,
                            Position(File(file), Rank(rank + 2)),
                                piece, PieceType::NONE, PieceType::NONE,
                                true, false, false, false));
            }

            if (rank == 4) //pour le en passant
            {
                if (chessboard.en_passant_get().has_value())
                {
                    if (file > 0
                            && chessboard.en_passant_get().value()
                            .convert_file() == file - 1
                            && !chessboard[Position(File(file - 1),
                                Rank(5))].has_value())
                    {
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(5)),
                                    piece, PieceType::NONE, PieceType::PAWN,
                                    false, false, false, true));
                    }

                    if (file < 7
                            && chessboard.en_passant_get().value()
                            .convert_file() == file + 1
                            && !chessboard[Position(File(file + 1),
                                Rank(5))].has_value())
                    {
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(5)),
                                    piece, PieceType::NONE, PieceType::PAWN,
                                    false, false, false, true));
                    }
                }
            }

            if (rank < 7)
            {
                if (chessboard[Position(File(file), Rank(rank + 1))]
                        == std::nullopt)
                {
                    if (rank + 1 == 7)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank + 1)),
                                    piece, PieceType::QUEEN, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank + 1)),
                                    piece, PieceType::ROOK, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank + 1)),
                                    piece, PieceType::KNIGHT, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank + 1)),
                                    piece, PieceType::BISHOP, PieceType::NONE,
                                    false, false, false, false));
                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank + 1)),
                                    piece, PieceType::NONE, PieceType::NONE,
                                    false, false, false, false));
                }

                auto rightdiag_cell = chessboard[Position(File(file + 1),
                        Rank(rank + 1))];
                if (file < 7
                        && rightdiag_cell.has_value()
                        && std::get<1>(rightdiag_cell.value()) == Color::BLACK)
                {
                    if (rank + 1 == 7)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank + 1)),
                                    piece, PieceType::QUEEN,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank + 1)),
                                    piece, PieceType::ROOK,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank + 1)),
                                    piece, PieceType::KNIGHT,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank + 1)),
                                    piece, PieceType::BISHOP,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank + 1)),
                                    piece, PieceType::NONE,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                }

                auto leftdiag_cell = chessboard[Position(File(file - 1),
                        Rank(rank + 1))];
                if (file > 0
                        && leftdiag_cell.has_value()
                        && std::get<1>(leftdiag_cell.value()) == Color::BLACK)
                {
                    if (rank + 1 == 7)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank + 1)),
                                    piece, PieceType::QUEEN,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank + 1)),
                                    piece, PieceType::ROOK,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank + 1)),
                                    piece, PieceType::KNIGHT,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank + 1)),
                                    piece, PieceType::BISHOP,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank + 1)),
                                    piece, PieceType::NONE,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                }
            }
        }
        else
        {
            if (rank == 6
                    && chessboard[Position(File(file),
                        Rank(rank - 1))] == std::nullopt
                    && chessboard[Position(File(file),
                        Rank(rank - 2))] == std::nullopt)
            {
                moves.push_back(Move(position,
                            Position(File(file), Rank(rank - 2)),
                                piece, PieceType::NONE, PieceType::NONE,
                                true, false, false, false));
            }

            if (rank == 3) //pour le en passant
            {
                if (chessboard.en_passant_get().has_value())
                {
                    if (file > 0 && chessboard.en_passant_get().value()
                            .convert_file() == file - 1
                            && !chessboard[Position(File(file - 1),
                                Rank(2))].has_value())
                    {
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(2)),
                                    piece, PieceType::NONE, PieceType::PAWN,
                                    false, false, false, true));
                    }

                    if (file < 7 && chessboard.en_passant_get().value()
                            .convert_file() == file + 1
                            && !chessboard[Position(File(file + 1),
                                Rank(2))].has_value())
                    {
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(2)),
                                    piece, PieceType::NONE, PieceType::PAWN,
                                    false, false, false, true));
                    }
                }
            }


            if (rank > 0)
            {
                if (chessboard[Position(File(file),
                            Rank(rank - 1))] == std::nullopt)
                {
                    if (rank - 1 == 0)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank - 1)),
                                    piece, PieceType::QUEEN, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank - 1)),
                                    piece, PieceType::KNIGHT, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank - 1)),
                                    piece, PieceType::ROOK, PieceType::NONE,
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank - 1)),
                                    piece, PieceType::BISHOP, PieceType::NONE,
                                    false, false, false, false));
                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file), Rank(rank - 1)),
                                    piece, PieceType::NONE, PieceType::NONE,
                                    false, false, false, false));
                }

                auto rightdiag_cell = chessboard[Position(File(file + 1),
                        Rank(rank - 1))];
                if (file < 7
                        && rightdiag_cell != std::nullopt
                        && std::get<1>(rightdiag_cell.value()) == Color::WHITE)
                {
                    if (rank - 1 == 0)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank - 1)),
                                    piece, PieceType::QUEEN,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                    moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank - 1)),
                                    piece, PieceType::ROOK,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                    moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank - 1)),
                                    piece, PieceType::BISHOP,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                    moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank - 1)),
                                    piece, PieceType::KNIGHT,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file + 1), Rank(rank - 1)),
                                    piece, PieceType::NONE,
                                    std::get<0>(rightdiag_cell.value()),
                                    false, false, false, false));
                }

                auto leftdiag_cell = chessboard[Position(File(file - 1),
                        Rank(rank - 1))];
                if (file > 0
                        && leftdiag_cell != std::nullopt
                        && std::get<1>(leftdiag_cell.value()) == Color::WHITE)
                {
                    if (rank - 1 == 0)
                    {
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank - 1)),
                                    piece, PieceType::QUEEN,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank - 1)),
                                    piece, PieceType::ROOK,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank - 1)),
                                    piece, PieceType::BISHOP,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank - 1)),
                                    piece, PieceType::KNIGHT,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));

                    }
                    else
                        moves.push_back(Move(position,
                                    Position(File(file - 1), Rank(rank - 1)),
                                    piece, PieceType::NONE,
                                    std::get<0>(leftdiag_cell.value()),
                                    false, false, false, false));
                }
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_bishop_moves(Chessboard chessboard,
            Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());

        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        int f = file - 1;
        int r = rank - 1;
        while (f >= 0 && r >= 0)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f--;
            r--;
        }

        f = file + 1;
        r = rank - 1;
        while (f <= 7 && r >= 0)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f++;
            r--;
        }

        f = file + 1;
        r = rank + 1;
        while (f <= 7 && r <= 7)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f++;
            r++;
        }

        f = file - 1;
        r = rank + 1;
        while (f >= 0 && r <= 7)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f--;
            r++;
        }
        return moves;
    }

    std::vector<Move> Rule::generate_knight_moves(Chessboard chessboard,
            Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());

        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        if (file + 1 <= 7 && rank + 2 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file + 1),
                    Rank(rank + 2))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 1), Rank(rank + 2)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 1), Rank(rank + 2)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file + 2 <= 7 && rank + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file + 2),
                    Rank(rank + 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 2), Rank(rank + 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 2), Rank(rank + 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file - 1 >= 0 && rank + 2 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file - 1),
                    Rank(rank + 2))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 1), Rank(rank + 2)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 1), Rank(rank + 2)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file - 2 >= 0 && rank + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file - 2),
                    Rank(rank + 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 2), Rank(rank + 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 2), Rank(rank + 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file - 1 >= 0 && rank - 2 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file - 1),
                    Rank(rank - 2))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 1), Rank(rank - 2)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 1), Rank(rank - 2)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file - 2 >= 0 && rank - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file - 2),
                    Rank(rank - 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 2), Rank(rank - 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 2), Rank(rank - 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file + 1 <= 7 && rank - 2 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file + 1),
                    Rank(rank - 2))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 1), Rank(rank - 2)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 1), Rank(rank - 2)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        if (file + 2 <= 7 && rank - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file + 2),
                    Rank(rank - 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 2), Rank(rank - 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 2), Rank(rank - 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        return moves;
    }

    std::vector<Move> Rule::generate_rook_moves(Chessboard chessboard,
            Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());

        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        int k = file - 1;
        while (k >= 0)
        {
            auto dest_cell = chessboard[Position(File(k), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(k), Rank(rank)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(k), Rank(rank)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));

            k--;
        }
        k = file + 1;
        while (k <= 7)
        {
            auto dest_cell = chessboard[Position(File(k), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(k), Rank(rank)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(k), Rank(rank)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));

            k++;
        }
        k = rank - 1;
        while (k >= 0)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(k))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(file), Rank(k)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(file), Rank(k)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k--;
        }
        k = rank + 1;
        while (k <= 7)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(k))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(file), Rank(k)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(file), Rank(k)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k++;
        }

        return moves;
    }

    std::vector<Move> Rule::generate_queen_moves(Chessboard chessboard,
            Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());

        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        int k = file - 1;
        while (k >= 0)
        {
            auto dest_cell = chessboard[Position(File(k), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(k), Rank(rank)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(k), Rank(rank)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k--;
        }
        k = file + 1;
        while (k <= 7)
        {
            auto dest_cell = chessboard[Position(File(k), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(k), Rank(rank)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(k), Rank(rank)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k++;
        }
        k = rank - 1;
        while (k >= 0)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(k))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(file), Rank(k)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(file), Rank(k)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k--;
        }
        k = rank + 1;
        while (k <= 7)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(k))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(file), Rank(k)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(file), Rank(k)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            k++;
        }

        int f = file - 1;
        int r = rank - 1;
        while (f >= 0 && r >= 0)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f--;
            r--;
        }

        f = file + 1;
        r = rank - 1;
        while (f <= 7 && r >= 0)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f++;
            r--;
        }

        f = file + 1;
        r = rank + 1;
        while (f <= 7 && r <= 7)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f++;
            r++;
        }

        f = file - 1;
        r = rank + 1;
        while (f >= 0 && r <= 7)
        {
            auto dest_cell = chessboard[Position(File(f), Rank(r))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) == color)
                    break;

                moves.push_back(Move(position,
                            Position(File(f), Rank(r)),
                            piece, PieceType::NONE,
                            std::get<0>(dest_cell.value()),
                            false, false, false, false));

                break;
            }
            moves.push_back(Move(position,
                        Position(File(f), Rank(r)),
                        piece, PieceType::NONE, PieceType::NONE,
                        false, false, false, false));
            f--;
            r++;
        }

        return moves;
    }

    std::vector<Move> Rule::generate_king_moves(Chessboard chessboard,
            Position position)
    {
        auto color = std::get<1>(chessboard[position].value());
        auto piece = std::get<0>(chessboard[position].value());

        std::vector<Move> moves;

        int file = position.convert_file();
        int rank = position.convert_rank();

        if (color == Color::WHITE)
        {
            if (chessboard.white_queen_castling_get())
            {
                if (!chessboard[Position(File(1), Rank(0))].has_value()
                        && !chessboard[Position(File(2), Rank(0))].has_value()
                        && !chessboard[Position(File(3), Rank(0))].has_value())
                {
                    moves.push_back(Move(position,
                                Position(File(2), Rank(0)),
                                piece, PieceType::NONE, PieceType::NONE,
                                false, false, true, false));
                }
            }

            if (chessboard.white_king_castling_get())
            {
                if (!chessboard[Position(File(5), Rank(0))].has_value()
                        && !chessboard[Position(File(6), Rank(0))])
                {
                    moves.push_back(Move(position,
                                Position(File(6), Rank(0)),
                                piece, PieceType::NONE, PieceType::NONE,
                                false, true, false, false));
                }
            }
        }

        else
        {
            if (chessboard.black_queen_castling_get())
            {
                if (!chessboard[Position(File(1), Rank(7))].has_value()
                        && !chessboard[Position(File(2), Rank(7))].has_value()
                        && !chessboard[Position(File(3), Rank(7))].has_value())
                {
                    moves.push_back(Move(position,
                                Position(File(2), Rank(7)),
                                piece, PieceType::NONE, PieceType::NONE,
                                false, false, true, false));
                }
            }

            if (chessboard.black_king_castling_get())
            {
                if (!chessboard[Position(File(5), Rank(7))].has_value()
                        && !chessboard[Position(File(6), Rank(7))])
                {
                    moves.push_back(Move(position,
                                Position(File(6), Rank(7)),
                                piece, PieceType::NONE, PieceType::NONE,
                                false, true, false, false));
                }
            }
        }

        if (file + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file + 1), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 1), Rank(rank)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 1), Rank(rank)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (file - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file - 1), Rank(rank))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 1), Rank(rank)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 1), Rank(rank)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (rank + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(rank + 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file), Rank(rank + 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file), Rank(rank + 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (rank - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file), Rank(rank - 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file), Rank(rank - 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file), Rank(rank - 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (file + 1 <= 7 && rank + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file + 1),
                    Rank(rank + 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 1), Rank(rank + 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 1), Rank(rank + 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (file - 1 >= 0 && rank + 1 <= 7)
        {
            auto dest_cell = chessboard[Position(File(file - 1),
                    Rank(rank + 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 1), Rank(rank + 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 1), Rank(rank + 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (file + 1 <= 7 && rank - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file + 1),
                    Rank(rank - 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file + 1), Rank(rank - 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file + 1), Rank(rank - 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }
        if (file - 1 >= 0 && rank - 1 >= 0)
        {
            auto dest_cell = chessboard[Position(File(file - 1),
                    Rank(rank - 1))];
            if (dest_cell != std::nullopt)
            {
                if (std::get<1>(dest_cell.value()) != color)
                {
                    moves.push_back(Move(position,
                                Position(File(file - 1), Rank(rank - 1)),
                                piece, PieceType::NONE,
                                std::get<0>(dest_cell.value()),
                                false, false, false, false));
                }

            }
            else
            {
                moves.push_back(Move(position,
                            Position(File(file - 1), Rank(rank - 1)),
                            piece, PieceType::NONE, PieceType::NONE,
                            false, false, false, false));
            }
        }

        return moves;

    }

    bool Rule::check_double_pawn_push(Chessboard chessboard, Position start,
            Position end)
    {
        if (chessboard[start] == std::nullopt)
            return false;

        auto color = std::get<1>(chessboard[start].value());
        auto piece = std::get<0>(chessboard[start].value());

        if (piece != PieceType::PAWN)
            return false;

        if (color == Color::WHITE)
        {
            if (start.convert_rank() != 1)
                return false;

            if (end.convert_rank() != 3)
                return false;
        }
        else
        {
            if (start.convert_rank() != 6)
                return false;

            if (end.convert_rank() != 4)
                return false;
        }

        return true;
    }

    bool Rule::check_king_castling(Chessboard chessboard, Position start,
            Position end)
    {
        if (chessboard[start] == std::nullopt)
            return false;

        auto color = std::get<1>(chessboard[start].value());
        auto piece = std::get<0>(chessboard[start].value());

        if (piece != PieceType::KING)
            return false;

        if (color == Color::WHITE)
        {
            if (start.convert_rank() != 0)
                return false;

            if (start.convert_file() != 4)
                return false;

            if (end.convert_rank() != 0)
                return false;

            if (end.convert_file() != 6)
                return false;
        }
        else
        {
            if (start.convert_rank() != 7)
                return false;

            if (start.convert_file() != 4)
                return false;

            if (end.convert_rank() != 7)
                return false;

            if (end.convert_file() != 6)
                return false;
        }

        return true;
    }

    bool Rule::check_queen_castling(Chessboard chessboard, Position start,
            Position end)
    {
        if (chessboard[start] == std::nullopt)
            return false;

        auto color = std::get<1>(chessboard[start].value());
        auto piece = std::get<0>(chessboard[start].value());

        if (piece != PieceType::KING)
            return false;

        if (color == Color::WHITE)
        {
            if (start.convert_rank() != 0)
                return false;

            if (start.convert_file() != 4)
                return false;

            if (end.convert_rank() != 0)
                return false;

            if (end.convert_file() != 2)
                return false;
        }
        else
        {
            if (start.convert_rank() != 7)
                return false;

            if (start.convert_file() != 4)
                return false;

            if (end.convert_rank() != 7)
                return false;

            if (end.convert_file() != 2)
                return false;
        }

        return true;
    }


    bool Rule::check_en_passant(Chessboard chessboard, Position start,
            Position end)
    {
        if (chessboard[start] == std::nullopt)
            return false;

        auto color = std::get<1>(chessboard[start].value());
        auto piece = std::get<0>(chessboard[start].value());

        if (piece != PieceType::PAWN)
            return false;

        if (color == Color::WHITE)
        {
            if (start.convert_rank() != 3)
                return false;

            if (end.convert_rank() != 4)
                return false;
        }
        else
        {
            if (start.convert_rank() != 4)
                return false;

            if (end.convert_rank() != 3)
                return false;
        }

        if (end.convert_file() != start.convert_file() - 1
                && end.convert_file() != start.convert_file() + 1)
            return false;

        return true;
    }
}
