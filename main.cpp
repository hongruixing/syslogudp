#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <regex>
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "port contain string")
            ("port", po::value<int>(), "set listen port")
            ("regex", po::value<std::string>(), "set regex string")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    int port = 3303;
    if (vm.count("port")) {
        port =vm["port"].as<int>();
    }

    try
    {
        boost::asio::io_service io_context;
        for (;;)
        {
            boost::asio::ip::udp::socket socket(
                    io_context,
                    boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), port});
            boost::asio::ip::udp::endpoint client;
            char recv_str[1024] = {};
            socket.receive_from(
                    boost::asio::buffer(recv_str),
                    client);

            std::cout << recv_str <<std::endl;


        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}