#include "main_window.hpp"

#include "vcl/command_line.hpp"

int main(int argc, const char* argv[])
{
    vcl::Application app{argc, argv};
    app.start<MainWindow>();
}
