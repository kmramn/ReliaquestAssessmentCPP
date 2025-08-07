
#include "stdafx.h"

void setup_routes(http_listener& listener, EmployeeHandler& employeeHandler) {
    listener.support(methods::GET, [&](http_request request) {

        AuditLogger& auditLogger = AuditLogger::GetInstance();

        auto path = uri::split_path(uri::decode(request.relative_uri().path()));
        auto query = uri::split_query(request.request_uri().query());

        string szLog("method::GET - path");
        auditLogger.log(szLog);
        auditLogger.log(path);
        auditLogger.log(query);

        employeeHandler.httpGETProcess(path, query, request);

        });

    listener.support(methods::POST, [&](http_request request) {
        AuditLogger& auditLogger = AuditLogger::GetInstance();
        string szLog("method::POST");
        auditLogger.log(szLog);

        employeeHandler.httpPOSTProcess(request);

        });

    listener.support(methods::DEL, [&](http_request request) {
        AuditLogger& auditLogger = AuditLogger::GetInstance();

        auto path = uri::split_path(uri::decode(request.relative_uri().path()));

        string szLog("method::POST");
        auditLogger.log(szLog);
        auditLogger.log(path);

        employeeHandler.httpDELProcess(path, request);

        });
}

int main()
{
    AuditLogger& auditLogger = AuditLogger::GetInstance();

    web::http::experimental::listener::http_listener listener(U("http://localhost:8080/api/v1/employee"));

    EmployeeManager manager;
    EmployeeHandler employeeHandler(manager);
    setup_routes(listener, employeeHandler);

    try
    {
        auditLogger.log("The Server started listening!");
        listener.open().wait();
        std::cout << "Employee REST API C++ server is running..." << std::endl;
        std::cout << "Press Enter to stop..." << std::endl;
        std::cin.get();  // Keep alive
        listener.close().wait();
        auditLogger.log("Shutting down the server...!");
    }
    catch (const std::exception& ex) {
        string szStr;
        szStr = "Exception: ";
        szStr += ex.what();

        std::cerr << szStr << std::endl;
        auditLogger.log(szStr);
    }

    return 0;
}

/*void handle_get(http_request request)
{
    ucout << U("GET request received\n");

    // Simple HTML content as a wide string
    utility::string_t html_content =
        U("<html><head><title>Status</title></head>")
        U("<body><h1><b>C++ Web Server is running</h1></body></html>");

    // Set content type to text/html
    request.reply(status_codes::OK, html_content, U("text/html"));
}

#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/json.h> // For JSON handling, if needed

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
int main()
{
    web::http::experimental::listener::http_listener listener(U("http://localhost:8080/status"));

    listener.support(methods::GET, handle_get);

    try {
        listener.open().wait();
        ucout << U("Listening on http://localhost:8080/status\n");

        std::string line;
        std::getline(std::cin, line); // Wait for user input before shutdown

        listener.close().wait();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}*/
