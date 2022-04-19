#include "HttpClient.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/locale.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

using namespace boost;
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

using namespace client;

HttpClient::HttpClient() {
	
}

HttpClient::~HttpClient() {
	
}

std::string HttpClient::getRequest(const char* host, const char* path, const char* port) {
	beast::ssl_stream<beast::tcp_stream> stream = this->createStream(host, port);
	http::request<http::string_body> req{http::verb::get, path, 11};
	req.set(http::field::host, host);
	http::write(stream, req);

	beast::flat_buffer buffer;
	http::response<http::dynamic_body> res;
	http::read(stream, buffer, res);

	beast::error_code ec;
	stream.shutdown(ec);
	if(ec && ec != beast::errc::not_connected)
		throw beast::system_error{ec};
 
	return boost::beast::buffers_to_string(res.body().data());
}


std::string HttpClient::getRequest(const char* host, const char* path, const char* port, std::map<std::string, std::string> headerMap) {
	beast::ssl_stream<beast::tcp_stream> stream = this->createStream(host, port);
	http::request<http::string_body> req{http::verb::get, path, 11};
	req.set(http::field::host, host);
	std::map<std::string, std::string>::iterator it = headerMap.begin();
	while (it != headerMap.end()) {
		req.set(it->first, it->second);
		it++;
	}
	http::write(stream, req);

	beast::flat_buffer buffer;
	http::response<http::dynamic_body> res;
	http::read(stream, buffer, res);

	beast::error_code ec;
	//stream.shutdown(ec);
	if(ec && ec != beast::errc::not_connected)
		throw beast::system_error{ec};
 
	return boost::beast::buffers_to_string(res.body().data());
}

std::string HttpClient::postRequest(const char* host, const char* path, const char* port, const char* contentType, const char* body) {
	beast::ssl_stream<beast::tcp_stream> stream = this->createStream(host, port);
	http::request<http::string_body> req{http::verb::post, path, 11};
	req.set(http::field::host, host);
	req.set(http::field::content_type, contentType);
	req.body() = body;
	req.prepare_payload();
	http::write(stream, req);

	beast::flat_buffer buffer;
	http::response<http::dynamic_body> res;
	http::read(stream, buffer, res);

	beast::error_code ec;
	stream.shutdown(ec);
	if(ec && ec != beast::errc::not_connected)
		throw beast::system_error{ec};
 
	return boost::beast::buffers_to_string(res.body().data());
}

beast::ssl_stream<beast::tcp_stream> HttpClient::createStream(const char* host, const char* port) {
	net::io_context ioc;
    ssl::context ctx(ssl::context::tlsv12_client);
    ctx.set_verify_mode(ssl::verify_none);

	tcp::resolver resolver(ioc);
	beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);
	auto const results = resolver.resolve(host, port);
	beast::get_lowest_layer(stream).connect(results);
	stream.handshake(ssl::stream_base::client);
	return stream;
}

