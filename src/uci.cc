#include "uci.hh"

#include <fnmatch.h>
#include <iostream>
#include <sstream>

namespace ai
{
    namespace
    {
        std::string get_input(const std::string& expected = "*")
        {
            // Get a command following the expected globbing
            // Ignoring all unrecognized commands
            std::string buffer;
            do {
                std::getline(std::cin, buffer);
                if ("quit" == buffer || "stopuci" == buffer)
                    exit(0);
            } while (fnmatch(expected.c_str(), buffer.c_str(), 0));
            return buffer;
        }
    } // namespace

    void init(const std::string& name)
    {
        get_input("uci");
        std::cout << "id name " << name << '\n';
        std::cout << "id author " << name << '\n';
        std::cout << "uciok" << std::endl;
        get_input("isready");
        std::cout << "readyok" << std::endl;
    }

    void play_move(const std::string& move)
    {
        // Send the computed move
        std::cout << "bestmove " << move << std::endl;

    }

    bool search_occ(std::string str, std::string tok)
    {

        std::istringstream position(str);

        while (position)
        {
            std::string token;
            position >> token;

            if (token.compare(tok) == 0)
                return true;
        }

        return false;
    }

    std::string get_fen_str(std::string str)
    {
        std::string token;
        std::istringstream position(str);
        while (position)
        {
            position >> token;

            if (token.compare("fen") == 0)
            {
                position >> token;
                break;
            }
        }

        std::string fenstr;

        for (size_t i = 0; i < 6; i++)
        {
            fenstr += token;
            fenstr += " ";

            position >> token;
        }

        return fenstr;
    }

    std::string get_all_moves(std::string str)
    {
        std::string token;
        std::string all_moves;
        std::istringstream position(str);

        bool past_move = false;

        while (position)
        {

            position >> token;

            if (!position)
                break;

            if (token.compare("moves") == 0)
            {
                past_move = true;
                position >> token;

            }

            if (past_move)
            {
                all_moves += token;
                all_moves += " ";
            }
        }

        return all_moves;
    }

    board::Chessboard generate_board(std::string position)
    {
        board::Chessboard board;

        if (search_occ(position, "startpos"))
        {
            board.init_board();
        }

        else
        {
            std::string fenstr = get_fen_str(position);
            board.init_fenstr(fenstr);
        }

        return board;
    }

    std::string get_board()
    {
        auto board = get_input("position *"); // Get the board

        //auto board = "position fen rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNB"
        //+ "QKBNR b KQkq - 0 1 moves f7f5";

        //auto board = "position startpos moves b0c2";

        bool ime = search_occ(board, "moves");
        board::Chessboard chessboard = generate_board(board);

        if (ime)
        {
            std::string moves = get_all_moves(board);
            std::istringstream all_moves(moves);

            while (all_moves)
            {
                std::string move;
                all_moves >> move;

                if (!all_moves)
                   break;

                board::Move m = ia::string_to_move(chessboard, move);
                chessboard.do_move(m);

            }
        }

        get_input("go *"); // Wait for a go from GUI
        board::Move bestmove = ia::search(chessboard);

        play_move(ia::move_to_string(bestmove));
        chessboard.do_move(bestmove);

        std::string fenchessboard = board_to_fen(chessboard);

        return board_to_fen(chessboard);
    }
} // namespace ai
