#include "move.hh"

namespace board
{
    Move::Move(Position start,
                Position destination,
                PieceType piece,
                PieceType promotion,
                PieceType capture,
                bool double_pawn_push,
                bool king_castling,
                bool queen_castling,
                bool en_passant)
    {
        start_ = Position(start.file_get(), start.rank_get());
        destination_ = Position(destination.file_get(),
                destination.rank_get());
        piece_ = piece;
        promotion_ = promotion;
        capture_ = capture;
        double_pawn_push_ = double_pawn_push;
        king_castling_ = king_castling;
        queen_castling_ = queen_castling;
        en_passant_ = en_passant;
    }

    /*
    Move::Move(PgnMove move, Chessboard chessboard)
    {
        start_ = move.start_get();
        destination_ = move.end_get();
        piece_ = move.piece_get();
        promotion_ = move.promotion_get().value();
        capture_ = chessboard[destination_];
        double_pawn_push_ = null;
        king_castling_ = null;
        queen_castling_ = null;
        en_passant_ = null;
    }
    */

    Position Move::start_get()
    {
        return start_;
    }

    Position Move::destination_get()
    {
        return destination_;
    }

    PieceType Move::piece_get()
    {
        return piece_;
    }

    PieceType Move::promotion_get()
    {
        return promotion_;
    }

    PieceType Move::capture_get()
    {
        return capture_;
    }

    bool Move::double_pawn_push_get()
    {
        return double_pawn_push_;
    }

    bool Move::king_castling_get()
    {
        return king_castling_;
    }

    bool Move::queen_castling_get()
    {
        return queen_castling_;
    }

    bool Move::en_passant_get()
    {
        return en_passant_;
    }

    bool Move::operator==(Move other) const
    {
        if (start_ != other.start_get())
        {
//            std::cout << "start\n";
            return false;
        }
        if (destination_ != other.destination_get())
        {
//            std::cout << "destination\n";
//            std::cout << destination_.convert_rank() << "-"
//            << destination_.convert_file() << "\n";
//            std::cout << other.destination_get().convert_rank() << "-"
//            << other.destination_get().convert_file() << "\n";
            return false;
        }
        if (piece_ != other.piece_get())
        {
//            std::cout << "piece\n";
            return false;
        }
        if (promotion_ == PieceType::NONE
                && other.promotion_get() != PieceType::NONE)
        {
//           std::cout << "promo\n";
//           std::cout << (int) other.promotion_get()
//           << "  " << (int) promotion_ << "\n";
            return false;
        }
        if (capture_ != other.capture_get())
        {
//            std::cout << "capture\n";
            return false;
        }
        if (double_pawn_push_ != other.double_pawn_push_get())
        {
//            std::cout << "double\n";
            return false;
        }
        if (king_castling_ != other.king_castling_get())
        {
//            std::cout << "king castling\n";
            return false;
        }
        if (queen_castling_ != other.queen_castling_get())
        {
//            std::cout << "queen castling\n";
            return false;
        }
        if (en_passant_ != other.en_passant_get())
        {
//            std::cout << "en passant\n";
            return false;
        }
        return true;
    }
}
