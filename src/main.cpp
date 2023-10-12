#include "main_window.hpp"

int main(int argc, const char* argv[])
{
    vcl::Application app{argc, argv};
    app.start<MainWindow>();
}
