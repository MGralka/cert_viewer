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
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>

#include "certificate.hpp"
#include "certificatecolumns.hpp"

class MainWindow: public Gtk::Window
{
public:
    MainWindow(BaseObjectType* base, const Glib::RefPtr<Gtk::Builder>& builder);
    virtual ~MainWindow();

protected:
    void getWidgets();
    void connectSignals();
    void addFilters(Gtk::FileChooserDialog* d);
    void openBtnClicked();
    void aboutBtnClicked();
    void quitItemClicked();
    void aboutDialogResponse(int responseId);
    void fileChooserResponse(int responseId);
    void displayCertificate(const Certificate& c);

    const Glib::RefPtr<Gtk::Builder>& builder;

    Gtk::ToolButton* openFile;
    Gtk::ToolButton* saveAsFile;
    Gtk::ToolButton* about;
    Gtk::ImageMenuItem* openItem;
    Gtk::ImageMenuItem* aboutItem;
    Gtk::ImageMenuItem* quitItem;

    Gtk::AboutDialog* aboutDlg;
    Gtk::FileChooserDialog* fileChooserDlg;

    Gtk::TreeView* listView;
    Glib::RefPtr<Gtk::ListStore> listStore;
    CertificateColumns certColumns;
};

#endif
