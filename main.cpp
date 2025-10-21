#include "include/httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request&, httplib::Response& res){
        res.set_content("Hello world", "text/plain");
    });

    svr.Post("/echo", [](const httplib::Request& req, httplib::Response& res){
        res.set_content(req.body, "text/plain");
    });

    std::cout << "Server listening on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
}