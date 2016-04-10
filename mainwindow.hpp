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
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>

class MainWindow: public Gtk::Window
{
public:
    MainWindow(BaseObjectType* base, const Glib::RefPtr<Gtk::Builder>& builder);
    virtual ~MainWindow();

protected:
    void openBtnClicked();
    void aboutBtnClicked();

    const Glib::RefPtr<Gtk::Builder>& builder;

    Gtk::ToolButton* openFile;
    Gtk::ToolButton* saveFile;
    Gtk::ToolButton* saveAsFile;
    Gtk::ToolButton* about;
    Gtk::AboutDialog* aboutDlg;
};

#endif
