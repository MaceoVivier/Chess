std::string board_to_fen(board::Chessboard chessboard)
{
    std::string fen = fen_piece_placement(chessboard) + " ";

    if (chessboard.white_turn())
        fen += "w ";
    else
        fen += "b ";

    if (chessboard.white_king_castling_get()
            || chessboard.white_queen_castling_get()
            || chessboard.black_king_castling_get()
            || chessboard.black_queen_castling_get())
    {
        if (chessboard.white_king_castling_get())
            fen += 'K';
        if (chessboard.white_queen_castling_get())
            fen += 'Q';
        if (chessboard.black_king_castling_get())
            fen += 'k';
        if (chessboard.black_queen_castling_get())
            fen += 'q';

    }
    else
        fen += '-';
    fen += ' ';

    if (chessboard.en_passant_get() == std::nullopt)
        fen += '-';
    else
    {
        int file = chessboard.en_passant_get().convert_file();
        if (file == 0)
            fen += 'a';
        else if (file == 1)
            fen += 'b';
        else if (file == 2)
            fen += 'c';
        else if (file == 3)
            fen += 'd';
        else if (file == 4)
            fen += 'e';
        else if (file == 5)
            fen += 'f';
        else if (file == 6)
            fen += 'g';
        else if (file == 7)
            fen += 'h';

        fen += chessboard.en_passant_get().convert_rank();
    }
    fen += ' ';

    fen += "halfmove ";

    fen += "fullmove ";

    return fen;
}

std::string fen_piece_placement(board::Chessboard chessboard)
{
    std::string fen = "";
    size_t empty = 0;
    for (size_t r = 7; r >= 0; r--)
    {
        for (size_t f = 0; f < 8; f++)
        {
            if (chessboard.board_[r][f] == std::nullopt)
                empty++;
            else
            {
                if (empty != 0)
                    fen += empty;
                fen += piece_to_fen(chessboard.board_[r][f]);
                empty = 0;
            }
        }
        if (empty != 0)
        {
            fen += empty;
            empty = 0;
        }
        if (r != 0)
            fen += '/';
    }
    return fen;
}

std::string piece_to_fen(
        std::optional<std::pair<board::PieceType, board::Color>> piece)
{
    if (std::get<1>(board_[i][j].value()) == Color::WHITE)
    {
        if (std::get<0>(piece.value()) == PieceType::PAWN)
            return "P";
        if (std::get<0>(piece.value()) == PieceType::KNIGHT)
            return "N";
        if (std::get<0>(piece.value()) == PieceType::BISHOP)
            return "B";
        if (std::get<0>(piece.value()) == PieceType::ROOK)
            return "R";
        if (std::get<0>(piece.value()) == PieceType::QUEEN)
            return "Q";
        if (std::get<0>(piece.value()) == PieceType::KING)
            return "K";
    }
    else
    {
        if (std::get<0>(piece.value()) == PieceType::PAWN)
            return "p";
        if (std::get<0>(piece.value()) == PieceType::KNIGHT)
            return "p";
        if (std::get<0>(piece.value()) == PieceType::BISHOP)
            return "p";
        if (std::get<0>(piece.value()) == PieceType::ROOK)
            return "p";
        if (std::get<0>(piece.value()) == PieceType::QUEEN)
            return "p";
        if (std::get<0>(piece.value()) == PieceType::KING)
            return "p";
    }
    return "";
}
