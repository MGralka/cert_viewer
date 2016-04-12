/*
Cert Viewer, Gtk+3 based application for viewing SSL/TLS certificates
Copyright (C) 2016 Mateusz Gralka

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mainwindow.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "com.app.certview");
    try
    {
        Glib::RefPtr<Gtk::Builder> builder =
            Gtk::Builder::create_from_file("ui/cert_viewer.glade");
        MainWindow* main = nullptr;
        builder->get_widget_derived("main_window", main);
        if(main)
            app->run(*main);

        delete main;
        return 0;
    }
    catch(const Glib::FileError& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(const Glib::MarkupError& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(const Gtk::BuilderError& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 1;
}
