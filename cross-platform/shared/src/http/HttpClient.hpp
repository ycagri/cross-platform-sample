#ifndef _HTTP_CLIENT_
#define _HTTP_CLIENT_
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <string>
#include <map>

namespace beast = boost::beast;

namespace http_client {

	class HttpClient {

		public:
			HttpClient();
			~HttpClient();

			std::string getRequest(const char* host, const char* path, const char* port);
			std::string getRequest(const char* host, const char* path, const char* port, const std::map<std::string, std::string> headerMap);
			std::string postRequest(const char* host, const char* path, const char* port,const char* contentType, const char* body);

		private:
			beast::ssl_stream<beast::tcp_stream> createStream(const char* host, const char* port);
	};
}
#endif