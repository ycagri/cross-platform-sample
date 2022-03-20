#ifndef _HTTP_CLIENT_
#define _HTTP_CLIENT_
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <string>
#include <map>

namespace beast = boost::beast;

namespace client {

	class HttpClient {

		public:
			HttpClient();
			virtual ~HttpClient();

			virtual std::string getRequest(const char* host, const char* path, const char* port);
			virtual std::string getRequest(const char* host, const char* path, const char* port, const std::map<std::string, std::string> headerMap);
			virtual std::string postRequest(const char* host, const char* path, const char* port,const char* contentType, const char* body);

		private:
			beast::ssl_stream<beast::tcp_stream> createStream(const char* host, const char* port);
	};
}
#endif