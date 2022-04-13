namespace client
{

    template <class T>
    class Response
    {
    public:
        static Response<T> success(T *data)
        {
            return Response(data, "", true);
        }

        static Response<T> error(const char *message)
        {
            return Response(nullptr, message, false);
        }

        ~Response()
        {
            delete this->data;
        }

        T *getData()
        {
            return this->data;
        }

        std::string getError()
        {
            return this->message;
        }

        bool isSuccessful()
        {
            return this->successful;
        }

    private:
        Response(T *data, const char *message, bool successful)
        {
            this->data = data;
            this->message = std::string(message);
            this->successful = successful;
        }

        T *data;
        std::string message;
        bool successful;
    };
}