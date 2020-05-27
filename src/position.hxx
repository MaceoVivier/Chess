#include <iostream>

namespace board
{
    inline Position::Position(File file, Rank rank)
        : file_(file)
        , rank_(rank)
    {}

    inline bool Position::operator==(const Position& pos) const
    {
        return file_get() == pos.file_get() && rank_get() == pos.rank_get();
    }

    inline bool Position::operator!=(const Position& pos) const
    {
        return !(*this == pos);
    }

    inline File Position::file_get() const
    {
        return file_;
    }

    inline Rank Position::rank_get() const
    {
        return rank_;
    }

    inline int Position::convert_rank() const
    {
        switch (rank_)
        {
        case Rank::ONE:
            return 0;
        case Rank::TWO:
            return 1;
        case Rank::THREE:
            return 2;
        case Rank::FOUR:
            return 3;
        case Rank::FIVE:
            return 4;
        case Rank::SIX:
            return 5;
        case Rank::SEVEN:
            return 6;
        case Rank::EIGHT:
            return 7;
        default:
            return 0;
        }
    }

    inline int Position::convert_file() const
    {
        switch (file_)
        {
        case File::A:
            return 0;
        case File::B:
            return 1;
        case File::C:
            return 2;
        case File::D:
            return 3;
        case File::E:
            return 4;
        case File::F:
            return 5;
        case File::G:
            return 6;
        case File::H:
            return 7;
        default:
            return 0;
        }
    }

    inline std::string Position::to_string()
    {
        std::string res = "";

        if (file_ == File::A)
            res += 'a';

        if (file_ == File::B)
            res += 'b';

        if (file_ == File::C)
            res += 'c';

        if (file_ == File::D)
            res += 'd';

        if (file_ == File::E)
            res += 'e';

        if (file_ == File::F)
            res += 'f';

        if (file_ == File::G)
            res += 'g';

        if (file_ == File::H)
            res += 'h';


        std::string s = std::to_string(convert_rank());
        res += s.c_str();

        return res;
    }
} // namespace board
