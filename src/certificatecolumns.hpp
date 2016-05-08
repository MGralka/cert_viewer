#ifndef CERTIFICATECOLUMNS_HPP
#define CERTIFICATECOLUMNS_HPP

#include <gtkmm.h>

class CertificateColumns: public Gtk::TreeModelColumnRecord
{
public:
    CertificateColumns()
    {
        add(name);
        add(value);
    }

    Gtk::TreeModelColumn<Glib::ustring> name;
    Gtk::TreeModelColumn<Glib::ustring> value;
};

#endif

