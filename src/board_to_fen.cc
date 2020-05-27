#include "board_to_fen.hh"

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
        size_t file = chessboard.en_passant_get().value().convert_file();
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

        fen += chessboard.en_passant_get().value().convert_rank();
    }
    fen += ' ';

    return fen;
}

std::string fen_piece_placement(board::Chessboard chessboard)
{
    std::string fen = "";
    size_t e;
    size_t r;
    for (size_t k = 0; k < 8; k++)
    {
        e = 0;
        r = 7 - k;
        for (size_t f = 0; f < 8; f++)
        {
            if (chessboard.board_[r][f] == std::nullopt)
                e++;
            else
            {
                if (e != 0)
                    fen += e + '0';
                fen += piece_to_fen(chessboard.board_[r][f]);
                e = 0;
            }
        }
        if (e != 0)
            fen += e + '0';
        if (k != 7)
            fen += '/';
    }
    return fen;
}

std::string piece_to_fen(
        std::optional<std::pair<board::PieceType, board::Color>> piece)
{
    if (std::get<1>(piece.value()) == board::Color::WHITE)
    {
        if (std::get<0>(piece.value()) == board::PieceType::PAWN)
            return "P";
        if (std::get<0>(piece.value()) == board::PieceType::KNIGHT)
            return "N";
        if (std::get<0>(piece.value()) == board::PieceType::BISHOP)
            return "B";
        if (std::get<0>(piece.value()) == board::PieceType::ROOK)
            return "R";
        if (std::get<0>(piece.value()) == board::PieceType::QUEEN)
            return "Q";
        if (std::get<0>(piece.value()) == board::PieceType::KING)
            return "K";
    }
    else
    {
        if (std::get<0>(piece.value()) == board::PieceType::PAWN)
            return "p";
        if (std::get<0>(piece.value()) == board::PieceType::KNIGHT)
            return "n";
        if (std::get<0>(piece.value()) == board::PieceType::BISHOP)
            return "b";
        if (std::get<0>(piece.value()) == board::PieceType::ROOK)
            return "r";
        if (std::get<0>(piece.value()) == board::PieceType::QUEEN)
            return "q";
        if (std::get<0>(piece.value()) == board::PieceType::KING)
            return "k";
    }
    return "";
}
