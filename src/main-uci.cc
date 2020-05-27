#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <dlfcn.h>

#include "chessboard.hh"
#include "listener.hh"
#include "pgn-parser.hh"
#include "uci.hh"

using namespace std;

int main()
{
    std::string name = "Jarvis v1";
    std::string str = "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::cout << ai::get_fen_str(str);
    return 0;
}
