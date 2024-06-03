#include "include/webserver/router.h"
#include "include/webserver/webserver.h"
#include <iostream>

using namespace std;

int main() {
  cout << "out\n";
  Router router;
  router.Get("/home", [](HttpRequest) -> HttpResponse {
    HttpResponse resp("text_html", "index.html");
    return resp;
  });
  router.Get("/login", [](HttpRequest) -> HttpResponse {
    HttpResponse resp("text_html", "login.html");
    return resp;
  });
  router.Get("/login", [](HttpRequest) -> HttpResponse {
    HttpResponse resp("text_html", "login.html");
    return resp;
  });
  router.Post("/login", [](HttpRequest req) -> HttpResponse {
    cout << req.getBody() << endl;
    cout << req.getHeaders()["Content-Type"] << endl;
    HttpResponse resp("application_json", R"({"message":"success"})");

    cout << "this post handle was played" << endl;
    return resp;
  });

  Webserver server(8081, router);
}