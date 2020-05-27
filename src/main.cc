#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <dlfcn.h>
#include <chessboard.hh>
#include "listener.hh"
#include "pgn-parser.hh"
#include "uci.hh"

using namespace std;

int main(int ac, char *av[])
{
    const std::string name = "Easily";
    auto engine = board::Chessboard();

    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "show usage")
            ("pgn", po::value<std::string>(), "path to the PGN game file")
            ("listeners,l", po::value<std::string>(),
             "list of paths to listener plugins")
            ("perft", po::value<std::string>(), "path to a preft file");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }


        if (vm.count("listeners")) {
            void* handle = dlopen(vm["listeners"].as<std::string>().c_str(),
                    RTLD_NOW);
            void* symbol = dlsym(handle, "listener_create");
            listener::Listener* listener =
                reinterpret_cast<listener::Listener*(*)()>(symbol)();
            listener->register_board(engine);
            engine.add_listener(listener);
        }

        else
        {
            void* handle = dlopen("tests/libbasic-output.so", RTLD_NOW);
            void* symbol = dlsym(handle, "listener_create");
            listener::Listener* listener =
                reinterpret_cast<listener::Listener*(*)()>(symbol)();
            listener->register_board(engine);
            engine.add_listener(listener);
        }

        if (vm.count("pgn"))
        {
            engine.init_board();
            int return_value;
            auto moves = pgn_parser::parse_pgn(vm["pgn"].as<std::string>());
            for (size_t i = 0; i < moves.size(); i++)
            {
                return_value = engine.do_move(engine.pgn_to_move(moves[i]));
//                engine.print();
                if (return_value == 1)
                    break;
            }

            return 0;
        }

        if (vm.count("perft")) {

            int depth = engine.init_perft(vm["perft"].as<std::string>());
            long long perft_nb = engine.compute_depth(depth);
            std::cout << perft_nb << "\n";
//            engine.print();
            return 0;
        }

        else
        {
            ai::init(name);

            while (true){
                ai::get_board();
           }
        }

    } catch (std::exception& e) {
        cerr << "error: " << e.what() << "\n";
    }

    return 0;
}
