#include <iostream>
#include <string>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/asio.hpp>




using namespace boost::asio;
ip::tcp::socket server_socket(io_context);

struct Session : std::enable_shared_from_this < Session > {
	explicit Session(ip::tcp::socket socket) : socket{ std::move(socket) } {}
	void read() {
		async_read_until(socket, dynamic_buffer(message), "\n", [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
			if (ec || self->message == "\n") return;
			//^ here we recieve an encrypted message from a session

			//then we broadcast the message across every session
			self->write();
			});
	}

	void write() {
		async_write(socket, buffer(message), [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
			if (ec) return;

			self->message.clear();
			self->read();
			});
	}
private:
	ip::tcp::socket socket;
	std::string message;
};

void serve(ip::tcp::acceptor& acceptor){
	acceptor.async_accept([&acceptor](boost::system::error_code ec, ip::tcp::socket socket) {
		serve(acceptor);
		if (ec)return;
		std::shared_ptr<Session> session = std::make_shared<Session>(std::move(socket));
		std::cout << "new session!" << std::endl;
		session->read();
		});
}

int main()
{
	try {
		io_context io_context;
		ip::tcp::acceptor acceptor{ io_context, ip::tcp::endpoint(ip::tcp::v4(), 6969) };
		serve(acceptor);
		io_context.run();
		
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
