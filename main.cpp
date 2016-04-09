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
