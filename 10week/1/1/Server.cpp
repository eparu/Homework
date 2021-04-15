#include <iostream>

#include <boost/asio.hpp>


void read_data_until(boost::asio::ip::tcp::socket & socket)
{
    boost::asio::streambuf buffer;
    std::string message;

    do
    {
        boost::asio::read_until(socket, buffer, '\n');

        std::istream input_stream(&buffer);
        std::getline(input_stream, message, '\n');

        std::cout << message << std::endl;
    }
    while (message != "Chat ended");


}

void write_data(boost::asio::ip::tcp::socket& socket, const std::string& user_name)
{

    std::string message;

    std::getline(std::cin, message);
    while (message != "exit")
    {
        boost::asio::write(socket, boost::asio::buffer(user_name + " : " + message + "\n"));
        std::getline(std::cin, message);
    }

    message = "Chat ended\n";

    boost::asio::write(socket, boost::asio::buffer(message));

}

int main(int argc, char** argv)
{

    const std::size_t size = 30;

    auto port = 3333;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

    boost::asio::io_service io_service;

    std::string user_name = "Server";

    try
    {
        boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

        acceptor.bind(endpoint);

        acceptor.listen(size);

        boost::asio::ip::tcp::socket socket(io_service);

        acceptor.accept(socket);
        auto reader = std::thread(read_data_until, std::ref(socket));
        write_data(socket, user_name);
        reader.join();

    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

        system("pause");

        return e.code().value();
    }


    return 0;
}
