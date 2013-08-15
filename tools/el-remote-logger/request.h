#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    Request(const std::string& originalRequest);
private:
    std::string m_originalRequest;
};

#endif // REQUEST_H
