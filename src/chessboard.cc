#include "chessboard.hh"

#include <fstream>

namespace board
{
    void Chessboard::init_fenstr(std::string s)
    {
        char piece;
        int i = 7;
        int j = 0;
        int k = 0;

        while (s[k] != ' ')
        {
            piece = s[k];
            if (piece == '/')
            {
                i--;
                j = 0;
                k++;
                continue;
            }

            else if (piece == 'P')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::PAWN, Color::WHITE));
            else if (piece == 'N')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KNIGHT, Color::WHITE));
            else if (piece == 'B')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::BISHOP, Color::WHITE));
            else if (piece == 'R')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::ROOK, Color::WHITE));
            else if (piece == 'Q')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::QUEEN, Color::WHITE));
            else if (piece == 'K')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KING, Color::WHITE));

            else if (piece == 'p')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::PAWN, Color::BLACK));
            else if (piece == 'n')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KNIGHT, Color::BLACK));
            else if (piece == 'b')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::BISHOP, Color::BLACK));
            else if (piece == 'r')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::ROOK, Color::BLACK));
            else if (piece == 'q')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::QUEEN, Color::BLACK));
            else if (piece == 'k')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KING, Color::BLACK));

            if (piece > '8')
                j++;

            else
            {
                for (int l = 0; l < piece - '0'; l++)
                {
                    board_[i][j] = std::nullopt;
                    j++;
                }
            }

            k++;
        }

        k++;

        white_turn_ = false;

        if (s[k] == 'w')
            white_turn_ = true;

        k += 2;

        white_queen_castling_ = false;
        white_king_castling_ = false;
        black_queen_castling_ = false;
        black_king_castling_ = false;

        if (s[k] == '-')
            k += 2;


        while (s[k] != ' ')
        {
            if (s[k] == 'K')
                white_king_castling_ = true;
            else if (s[k] == 'Q')
                white_queen_castling_ = true;
            else if (s[k] == 'k')
                black_king_castling_ = true;
            else if (s[k] == 'q')
                black_queen_castling_ = true;
            k++;
        }

        k++;

        if (s[k] == '-')
            en_passant_ = std::nullopt;

        else
        {
            if (s[k + 1] == '3')
                en_passant_ =
                    std::optional<Position>(Position(File(s[k] - 'a'),
                                Rank(3)));
            else
                en_passant_ =
                    std::optional<Position>(Position(File(s[k] - 'a'),
                                Rank(4)));
        }
    }

    int Chessboard::init_perft(const std::string& file)
    {
        std::ifstream perft(file);
        std::string token;
        perft >> token;

        char piece;
        int i = 7;
        int j = 0;
        for (size_t k = 0; k < token.length(); k++)
        {
            piece = token[k];
            if (piece == '/')
            {
                i--;
                j = 0;
                continue;
            }

            else if (piece == 'P')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::PAWN, Color::WHITE));
            else if (piece == 'N')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KNIGHT, Color::WHITE));
            else if (piece == 'B')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::BISHOP, Color::WHITE));
            else if (piece == 'R')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::ROOK, Color::WHITE));
            else if (piece == 'Q')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::QUEEN, Color::WHITE));
            else if (piece == 'K')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KING, Color::WHITE));

            else if (piece == 'p')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::PAWN, Color::BLACK));
            else if (piece == 'n')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KNIGHT, Color::BLACK));
            else if (piece == 'b')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::BISHOP, Color::BLACK));
            else if (piece == 'r')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::ROOK, Color::BLACK));
            else if (piece == 'q')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::QUEEN, Color::BLACK));
            else if (piece == 'k')
                board_[i][j] = std::optional<side_piece_t>(
                        std::make_pair(PieceType::KING, Color::BLACK));

            if (piece > '8')
                j++;

            else
            {
                for (int l = 0; l < piece - '0'; l++)
                {
                    board_[i][j] = std::nullopt;
                    j++;
                }
            }
        }

        perft >> token;

        white_turn_ = false;

        if (token[0] == 'w')
            white_turn_ = true;

        perft >> token;

        white_queen_castling_ = false;
        white_king_castling_ = false;
        black_queen_castling_ = false;
        black_king_castling_ = false;

        for (size_t i = 0; i < token.length(); i++)
        {
            if (token[i] == 'K')
                white_king_castling_ = true;
            else if (token[i] == 'Q')
                white_queen_castling_ = true;
            else if (token[i] == 'k')
                black_king_castling_ = true;
            else if (token[i] == 'q')
                black_queen_castling_ = true;
        }

        perft >> token;

        if (token[0] == '-')
            en_passant_ = std::nullopt;

        else
        {
            if (token[1] == '3')
                en_passant_ =
                    std::optional<Position>(Position(File(token[0] - 'a'),
                                Rank(3)));
            else
                en_passant_ =
                    std::optional<Position>(Position(File(token[0] - 'a'),
                                Rank(4)));
        }

        for (auto i = 0; i < 3; i++)
            perft >> token;

        return atoi(token.c_str());
    }

    long long Chessboard::compute_depth(int d)
    {
        white_turn_ = !white_turn_;
        if (is_check())
        {
            if (white_turn_)
            {
                black_king_castling_ = false;
                black_queen_castling_ = false;
            }

            else
            {
                white_king_castling_ = false;
                white_queen_castling_ = false;
            }
        }

        white_turn_ = !white_turn_;
        auto moves = this->generate_legal_moves();
        long long size = moves.size();
        long long copy = size;

        if (d != 1)
        {
            for (auto m : moves)
            {
                bool wkc = this->white_king_castling_;
                bool wqc = this->white_queen_castling_;
                bool bkc = this->black_king_castling_;
                bool bqc = this->black_queen_castling_;
                std::optional<Position> ep = this->en_passant_;
                this->simply_do_move(m);
                last_fifty_turn_ = 0;
                size += this->compute_depth(d - 1);
                this->undo_move(m, wkc, wqc, bkc, bqc, ep);
            }
        }

        if (d != 1)
            size -= copy;

        return size;
    }

    std::vector<Move> Chessboard::simply_generate_legal_moves()
    {
        std::vector<Move> final_moves;

        if (white_turn_)
        {
            for (auto i = 0; i < 8; i++)
            {
                for (auto j = 0; j < 8; j++)
                {
                    std::vector<Move> moves;

                    if (!board_[i][j].has_value())
                        continue;

                    if (std::get<1>(board_[i][j].value()) == Color::WHITE)
                    {
                        if (std::get<0>(board_[i][j].value())
                                == PieceType::KING)
                            moves = rules.generate_king_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::QUEEN)
                            moves = rules.generate_queen_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::ROOK)
                        {
                            moves = rules.generate_rook_moves(*this,
                                    Position(File(j), Rank(i)));
                        }

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::BISHOP)
                        {
                            moves = rules.generate_bishop_moves(*this,
                                    Position(File(j), Rank(i)));
                        }

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::KNIGHT)
                            moves = rules.generate_knight_moves(*this,
                                    Position(File(j), Rank(i)));

                        else
                            moves = rules.generate_pawn_moves(*this,
                                    Position(File(j), Rank(i)));
                    }

                    for (auto k : moves)
                        final_moves.push_back(k);
                }
            }
        }

        else
        {
            for (auto i = 0; i < 8; i++)
            {
                for (auto j = 0; j < 8; j++)
                {
                    std::vector<Move> moves;
                    if (board_[i][j] == std::nullopt)
                        continue;

                    if (std::get<1>(board_[i][j].value()) == Color::BLACK)
                    {
                        if (std::get<0>(board_[i][j].value())
                                == PieceType::KING)
                            moves = rules.generate_king_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::QUEEN)
                            moves = rules.generate_queen_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::ROOK)
                            moves = rules.generate_rook_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::BISHOP)
                            moves = rules.generate_bishop_moves(*this,
                                    Position(File(j), Rank(i)));

                        else if (std::get<0>(board_[i][j].value())
                                == PieceType::KNIGHT)
                            moves = rules.generate_knight_moves(*this,
                                    Position(File(j), Rank(i)));

                        else
                            moves = rules.generate_pawn_moves(*this,
                                    Position(File(j), Rank(i)));
                    }


                    for (auto k : moves)
                        final_moves.push_back(k);
                }
            }
        }

        return final_moves;
    }

    std::vector<Move> Chessboard::generate_legal_moves()
    {
        std::vector<Move> moves = this->simply_generate_legal_moves();


        std::vector<Move> corrected_moves;
        Chessboard copy = (*this);

        for (auto m : moves)
        {
            copy.simply_do_move(m);

            if (!copy.is_check())
                corrected_moves.push_back(m);
            copy = (*this);
        }

        return corrected_moves;
    }

    void Chessboard::change_turn()
    {
        white_turn_ = !white_turn_;
    }

    std::optional<Position> Chessboard::en_passant_get()
    {
        return en_passant_;
    }

    bool Chessboard::white_king_castling_get()
    {
        return white_king_castling_;
    }

    bool Chessboard::white_queen_castling_get()
    {
        return white_queen_castling_;
    }

    bool Chessboard::black_king_castling_get()
    {
        return black_king_castling_;
    }

    bool Chessboard::black_queen_castling_get()
    {
        return black_queen_castling_;
    }

    bool Chessboard::is_move_legal(Move move)
    {
        std::vector<Move> moves = this->generate_legal_moves();


        for (auto m : moves)
        {
            if (m == move)
            {
                return true;
            }
        }

        return false;
    }

    void Chessboard::undo_move(Move move, bool wkc,
            bool wqc, bool bkc,
            bool bqc, std::optional<Position> ep)
    {
        Position start = move.start_get();
        Position destination = move.destination_get();

        white_king_castling_ = wkc;
        white_queen_castling_ = wqc;
        black_king_castling_ = bkc;
        black_queen_castling_ = bqc;

        Color color = std::get<1>((*this)[destination].value());

        if (move.king_castling_get())
        {
            if (color == Color::WHITE)
            {
                this->board_[0][7] = this->board_[0][5];
                this->board_[0][5] = std::nullopt;
                this->board_[0][4] = this->board_[0][6];
                this->board_[0][6] = std::nullopt;
            }

            else if (color == Color::BLACK)
            {
                this->board_[7][7] = this->board_[7][5];
                this->board_[7][5] = std::nullopt;
                this->board_[7][4] = this->board_[7][6];
                this->board_[7][6] = std::nullopt;
            }
        }

        if (move.queen_castling_get())
        {
            if (color == Color::WHITE)
            {
                this->board_[0][0] = this->board_[0][3];
                this->board_[0][3] = std::nullopt;
                this->board_[0][4] = this->board_[0][2];
                this->board_[0][2] = std::nullopt;
            }

            else
            {
                this->board_[7][0] = this->board_[7][3];
                this->board_[7][3] = std::nullopt;
                this->board_[7][4] = this->board_[7][2];
                this->board_[7][2] = std::nullopt;
            }
        }

        if (!move.queen_castling_get()
                && !move.king_castling_get()
                && move.promotion_get() == PieceType::NONE)
        {
            this->board_[start.convert_rank()][start.convert_file()] =
                (*this)[destination];
        }

        if (move.en_passant_get())
        {
            if (color == Color::WHITE)
                this->board_[ep.value().convert_rank()]
                    [ep.value().convert_file()] = std::optional<side_piece_t>(
                            std::make_pair(PieceType::PAWN, Color::BLACK));
            else
                this->board_[ep.value().convert_rank()]
                    [ep.value().convert_file()] = std::optional<side_piece_t>(
                            std::make_pair(PieceType::PAWN, Color::WHITE));

            this->board_[destination.convert_rank()]
                [destination.convert_file()] = std::nullopt;
        }



        if (move.capture_get() != PieceType::NONE && !move.en_passant_get())
        {
            if (color == Color::WHITE)
                this->board_[destination.convert_rank()]
                    [destination.convert_file()] = std::optional<side_piece_t>(
                            std::make_pair(move.capture_get(), Color::BLACK));
            else
                this->board_[destination.convert_rank()]
                    [destination.convert_file()] = std::optional<side_piece_t>(
                            std::make_pair(move.capture_get(), Color::WHITE));
        }

        else
            this->board_[destination.convert_rank()]
                [destination.convert_file()] = std::nullopt;

        en_passant_ = ep;

        if (move.promotion_get() != PieceType::NONE)
            this->board_[start.convert_rank()][start.convert_file()] =
                std::optional<side_piece_t>(std::make_pair(PieceType::PAWN,
                            color));

        white_turn_ = !white_turn_;
        turn_--;
    }

    int Chessboard::do_move(Move move)
    {
        Position start = move.start_get();
        Position destination = move.destination_get();

        if (!this->is_move_legal(move))
        {
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                if (white_turn_)
                    listeners_vec[i]->on_player_disqualified(Color::WHITE);
                else
                    listeners_vec[i]->on_player_disqualified(Color::BLACK);
            }

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_game_finished();
            }

            return 1;
        }

        /*        std::cout << move.start_get().convert_file()
                  << move.start_get().convert_rank() + 1 << "-"
                  << move.destination_get().convert_file()
                  << move.destination_get().convert_rank() + 1;
                  */

        Color color = std::get<1>((*this)[start].value());

        for (size_t i = 0; i < listeners_vec.size(); i++)
        {
            listeners_vec[i]->on_piece_moved(move.piece_get(),
                    move.start_get(),
                    move.destination_get());
        }

        if (move.king_castling_get())
        {
            if (color == Color::WHITE)
            {
                white_king_castling_ = false;
                white_queen_castling_ = false;

                this->board_[0][5] = this->board_[0][7];
                this->board_[0][7] = std::nullopt;
                this->board_[0][6] = this->board_[0][4];
                this->board_[0][4] = std::nullopt;
            }

            else if (color == Color::BLACK)
            {
                black_king_castling_ = false;
                black_queen_castling_ = false;

                this->board_[7][5] = this->board_[7][7];
                this->board_[7][7] = std::nullopt;
                this->board_[7][6] = this->board_[7][4];
                this->board_[7][4] = std::nullopt;
            }

            last_fifty_turn_++;

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_kingside_castling(color);
            }
        }

        if (move.queen_castling_get())
        {
            if (color == Color::WHITE)
            {
                white_king_castling_ = false;
                white_queen_castling_ = false;

                this->board_[0][3] = this->board_[0][0];
                this->board_[0][0] = std::nullopt;
                this->board_[0][2] = this->board_[0][4];
                this->board_[0][4] = std::nullopt;
            }

            else if (color == Color::BLACK)
            {
                black_king_castling_ = false;
                black_queen_castling_ = false;

                this->board_[7][3] = this->board_[7][0];
                this->board_[7][0] = std::nullopt;
                this->board_[7][2] = this->board_[7][4];
                this->board_[7][4] = std::nullopt;
            }

            last_fifty_turn_++;

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_queenside_castling(color);
            }
        }

        if (en_passant_ != std::nullopt && move.en_passant_get() == false)
            en_passant_ = std::nullopt;

        if (move.double_pawn_push_get())
            en_passant_ = std::optional<Position>(destination);

        if (move.en_passant_get() && en_passant_ != std::nullopt)
        {
            this->board_[en_passant_.value().convert_rank()]
                [en_passant_.value().convert_file()] = std::nullopt;
            en_passant_ = std::nullopt;
        }

        if (move.capture_get() != PieceType::NONE)
        {
            last_fifty_turn_ = 0;
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_piece_taken(move.capture_get(),
                        move.destination_get());
            }
        }

        if (!move.queen_castling_get() && !move.king_castling_get())
        {
            if (move.piece_get() != PieceType::PAWN)
                last_fifty_turn_++;
            else
                last_fifty_turn_ = 0;

            this->board_[destination.convert_rank()]
                [destination.convert_file()] = (*this)[start];
            this->board_[start.convert_rank()]
                [start.convert_file()] = std::nullopt;
        }

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(0), Rank(0)))
            white_queen_castling_ = false;

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(7), Rank(0)))
            white_king_castling_ = false;

        if (move.piece_get() == PieceType::KING
                && color == Color::WHITE)
        {
            white_queen_castling_ = false;
            white_king_castling_ = false;
        }

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(0), Rank(7)))
            black_queen_castling_ = false;

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(7), Rank(7)))
            black_king_castling_ = false;

        if (move.piece_get() == PieceType::KING && color == Color::BLACK)
        {
            black_queen_castling_ = false;
            black_king_castling_ = false;
        }

        if (move.promotion_get() != PieceType::NONE)
        {
            this->board_[destination.convert_rank()]
                [destination.convert_file()] = std::optional<side_piece_t>(
                        std::make_pair(move.promotion_get(), color));

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_piece_promoted(move.promotion_get(),
                        move.destination_get());
            }
        }

        if (this->is_checkmate())
        {
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                if (white_turn_)
                    listeners_vec[i]->on_player_mat(Color::BLACK);
                else
                    listeners_vec[i]->on_player_mat(Color::WHITE);
            }

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_game_finished();
            }

            return 1;
        }

        if (this->is_check())
        {
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                if (white_turn_)
                    listeners_vec[i]->on_player_check(Color::BLACK);
                else
                    listeners_vec[i]->on_player_check(Color::WHITE);
            }
        }

        if (this->is_pat())
        {
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                if (white_turn_)
                    listeners_vec[i]->on_player_pat(Color::BLACK);
                else
                    listeners_vec[i]->on_player_pat(Color::WHITE);
            }

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_draw();
            }

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_game_finished();
            }

            return 1;
        }

        if (last_fifty_turn_ == 50)
        {
            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_draw();
            }

            for (size_t i = 0; i < listeners_vec.size(); i++)
            {
                listeners_vec[i]->on_game_finished();
            }

            return 1;
        }

        turn_++;
        white_turn_ = !white_turn_;

        return 0;
    }

    void Chessboard::simply_do_move(Move move)
    {
        Position start = move.start_get();
        Position destination = move.destination_get();

        Color color = std::get<1>((*this)[start].value());

        if (move.king_castling_get())
        {
            if (color == Color::WHITE)
            {
                white_king_castling_ = false;
                white_queen_castling_ = false;

                this->board_[0][5] = this->board_[0][7];
                this->board_[0][7] = std::nullopt;
                this->board_[0][6] = this->board_[0][4];
                this->board_[0][4] = std::nullopt;
            }

            else if (color == Color::BLACK)
            {
                black_king_castling_ = false;
                black_queen_castling_ = false;

                this->board_[7][5] = this->board_[7][7];
                this->board_[7][7] = std::nullopt;
                this->board_[7][6] = this->board_[7][4];
                this->board_[7][4] = std::nullopt;
            }
        }

        if (move.queen_castling_get())
        {
            if (color == Color::WHITE)
            {
                white_king_castling_ = false;
                white_queen_castling_ = false;

                this->board_[0][3] = this->board_[0][0];
                this->board_[0][0] = std::nullopt;
                this->board_[0][2] = this->board_[0][4];
                this->board_[0][4] = std::nullopt;
            }

            else if (color == Color::BLACK)
            {
                black_king_castling_ = false;
                black_queen_castling_ = false;

                this->board_[7][3] = this->board_[7][0];
                this->board_[7][0] = std::nullopt;
                this->board_[7][2] = this->board_[7][4];
                this->board_[7][4] = std::nullopt;
            }
        }

        if (en_passant_ != std::nullopt && move.en_passant_get() == false)
            en_passant_ = std::nullopt;

        if (move.double_pawn_push_get())
            en_passant_ = std::optional<Position>(destination);

        if (move.en_passant_get() && en_passant_ != std::nullopt)
        {
            this->board_[en_passant_.value().convert_rank()]
                [en_passant_.value().convert_file()] = std::nullopt;
            en_passant_ = std::nullopt;
        }

        if (!move.queen_castling_get() && !move.king_castling_get())
        {
            this->board_[destination.convert_rank()]
                [destination.convert_file()] = (*this)[start];
            this->board_[start.convert_rank()]
                [start.convert_file()] = std::nullopt;
        }

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(0), Rank(0)))
            white_queen_castling_ = false;

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(7), Rank(0)))
            white_king_castling_ = false;

        if (move.piece_get() == PieceType::KING
                && color == Color::WHITE)
        {
            white_queen_castling_ = false;
            white_king_castling_ = false;
        }

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(0), Rank(7)))
            black_queen_castling_ = false;

        if (move.piece_get() == PieceType::ROOK
                && start == Position(File(7), Rank(7)))
            black_king_castling_ = false;

        if (move.piece_get() == PieceType::KING && color == Color::BLACK)
        {
            black_queen_castling_ = false;
            black_king_castling_ = false;
        }

        if (move.promotion_get() != PieceType::NONE)
        {
            this->board_[destination.convert_rank()]
                [destination.convert_file()] = std::optional<side_piece_t>(
                        std::make_pair(move.promotion_get(), color));
        }

        white_turn_ = !white_turn_;
    }

    Position Chessboard::find_king(Color king_color)
    {
        for (auto i = 0; i < 8; i++)
        {
            for (auto j = 0; j < 8; j++)
            {
                if (!board_[i][j].has_value())
                    continue;

                if (std::get<0>(board_[i][j].value()) == PieceType::KING
                        && std::get<1>(board_[i][j].value()) == king_color)
                {
                    return Position(File(j), Rank(i));
                }
            }
        }

        return Position(File(0), Rank(0));
    }

    bool Chessboard::is_check()
    {
        std::vector<Move> moves = this->simply_generate_legal_moves();

        Color king_color = Color::WHITE;
        if (white_turn_)
            king_color = Color::BLACK;

        Position king_position = this->find_king(king_color);

        for (auto m : moves)
        {
            if (m.destination_get() == king_position)
                return true;
        }

        return false;
    }

    bool Chessboard::is_checkmate()
    {
        if (!is_check())
            return false;

        white_turn_ = !white_turn_;

        Chessboard copy = (*this);

        std::vector<Move> moves = this->generate_legal_moves();

        for (auto m : moves)
        {
            copy.simply_do_move(m);
            if (!copy.is_check())
            {
                white_turn_ = !white_turn_;
                return false;
            }

            copy = (*this);
        }

        white_turn_ = !white_turn_;
        return true;
    }

    bool Chessboard::is_pat()
    {
        white_turn_ = !white_turn_;

        Chessboard copy = (*this);

        std::vector<Move> moves = this->generate_legal_moves();

        for (auto m : moves)
        {
            copy.simply_do_move(m);
            if (!copy.is_check())
            {
                white_turn_ = !white_turn_;
                return false;
            }

            copy = (*this);
        }

        white_turn_ = !white_turn_;
        return true;

    }

    void Chessboard::init_board()
    {
        last_fifty_turn_ = 0;
        turn_ = 0;
        white_turn_ = true;
        white_king_castling_ = true;
        white_queen_castling_ = true;
        black_king_castling_ = true;
        black_queen_castling_ = true;
        for (auto i = 0; i < 8; i++)
        {
            for (auto j = 0; j < 8; j++)
            {
                board_[i][j] = std::nullopt;
            }
        }

        for (auto i = 0; i < 8; i++)
        {
            board_[1][i] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::PAWN, Color::WHITE));
            board_[6][i] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::PAWN, Color::BLACK));
        }

        auto color = Color::WHITE;
        for (auto i = 0; i < 8; i += 7)
        {
            board_[i][0] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::ROOK, color));
            board_[i][1] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::KNIGHT, color));
            board_[i][2] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::BISHOP, color));
            board_[i][3] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::QUEEN, color));
            board_[i][4] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::KING, color));
            board_[i][5] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::BISHOP, color));
            board_[i][6] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::KNIGHT, color));
            board_[i][7] = std::optional<side_piece_t>(
                    std::make_pair(PieceType::ROOK, color));
            color = Color::BLACK;
        }
    }

    Move Chessboard::pgn_to_move(PgnMove m)
    {
        board::PieceType promotion = PieceType::NONE;
        if (m.promotion_get())
        {
            promotion = m.promotion_get().value();
        }

        auto capture = m.capture_get();
        PieceType captured = PieceType::NONE;

        bool double_pawn_push = false;
        bool en_passant = false;

        if (m.piece_get() == PieceType::PAWN)
        {
            double_pawn_push = rules.check_double_pawn_push(*this,
                    m.start_get(), m.end_get());

            if (en_passant_.has_value() && capture)
            {
                Color pawn_color = std::get<1>((*this)[en_passant_.value()]
                        .value());
                int file = en_passant_.value().convert_file();

                if (pawn_color == Color::WHITE)
                {
                    if (m.end_get().convert_rank() == 2
                            && file == m.end_get().convert_file())
                    {
                        captured = PieceType::PAWN;
                        en_passant = true;
                    }
                }
                else
                {
                    if (m.end_get().convert_rank() == 5
                            && file == m.end_get().convert_file())
                    {
                        captured = PieceType::PAWN;
                        en_passant = true;
                    }
                }
            }
        }

        if (capture && !en_passant)
        {
            if ((*this)[m.end_get()].has_value())
                captured = std::get<0>((*this)[m.end_get()].value());

            else
                std::cout << "Error: no capture is possible\n";
        }


        bool king_castling = false;
        bool queen_castling = false;
        if (m.piece_get() == PieceType::KING)
        {
            king_castling = rules.check_king_castling(*this,
                    m.start_get(), m.end_get());
            queen_castling = rules.check_queen_castling(*this,
                    m.start_get(), m.end_get());
        }

        auto new_move = Move(m.start_get(),
                m.end_get(),
                m.piece_get(),
                promotion,
                captured,
                double_pawn_push,
                king_castling,
                queen_castling,
                en_passant);

        return new_move;
    }

    Chessboard::opt_piece_t
        Chessboard::operator[](const Position& position) const
        {
            return board_[position.convert_rank()][position.convert_file()];
        }

    void Chessboard::add_listener(listener::Listener* listener)
    {
        listeners_vec.push_back(listener);
    }

    void Chessboard::print()
    {
        for (int i = 7; i >= 0; i--)
        {
            std::cout << "||";
            for (int j = 0; j < 8; j++)
            {
                if (this->board_[i][j] == std::nullopt)
                    std::cout << '-';
                else if (std::get<1>(this->board_[i][j].value())
                        == Color::WHITE)
                {
                    if (std::get<0>(this->board_[i][j].value())
                            == PieceType::PAWN)
                        std::cout << 'P';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::ROOK)
                        std::cout << 'R';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::KNIGHT)
                        std::cout << 'N';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::BISHOP)
                        std::cout << 'B';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::KING)
                        std::cout << 'K';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::QUEEN)
                        std::cout << 'Q';
                    else
                        std::cout << '-';
                }

                else if (std::get<1>(this->board_[i][j].value())
                        == Color::BLACK)
                {
                    if (std::get<0>(this->board_[i][j].value())
                            == PieceType::PAWN)
                        std::cout << 'p';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::ROOK)
                        std::cout << 'r';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::KNIGHT)
                        std::cout << 'n';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::BISHOP)
                        std::cout << 'b';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::KING)
                        std::cout << 'k';
                    else if (std::get<0>(this->board_[i][j].value())
                            == PieceType::QUEEN)
                        std::cout << 'q';
                    else
                        std::cout << '-';
                }
                if (j != 7)
                    std::cout << "|";
            }
            std::cout << "||\n";
        }
    }

    bool Chessboard::white_turn()
    {
        return this->white_turn_;
    }

}
