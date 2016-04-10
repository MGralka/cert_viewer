/*
Cert Viewer, Gtk+3 based application for viewing SSL/TLS certificates
Copyright (C) 2016  Mateusz Gralka

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

#include <gtkmm.h>
#include <iostream>

void openButtonClicked()
{
    std::cout << "Open button clicked" << std::endl;
}

void aboutButtonClicked()
{
    std::cout << "About button clicked" << std::endl;
}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "com.app.certview");
    try
    {
        Glib::RefPtr<Gtk::Builder> builder =
            Gtk::Builder::create_from_file("ui/cert_viewer.glade");
        Gtk::Window* main = nullptr;
        builder->get_widget("main_window", main);
        if(main)
        {
            Gtk::ToolButton* openFile = nullptr;
            Gtk::ToolButton* saveFile = nullptr;
            Gtk::ToolButton* saveAsFile = nullptr;
            Gtk::ToolButton* about  = nullptr;

            builder->get_widget("open_button", openFile);
            builder->get_widget("save_button", saveFile);
            builder->get_widget("save_as_button", saveAsFile);
            builder->get_widget("about_button", about);

            if(openFile)
                openFile->signal_clicked().connect(sigc::ptr_fun(openButtonClicked));

            if(about)
                about->signal_clicked().connect(sigc::ptr_fun(aboutButtonClicked));

            return app->run(*main);
        }
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

    return -1;
}
