#include <html/html_doc.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace html;

int main()
{
    istringstream stream("<!doctype html><html><head><title>Title<!--</title>--></head></title><body><h1 align=\"center\">Hello</h1><p>Hello <p>world!<br/></body></html>");
    html_doc doc;
    stream >> doc;
    cout << doc << endl;
    for (auto& p : doc.node()["body"].back()["p"])
    {
        cout << p.front().text();
    }
}
