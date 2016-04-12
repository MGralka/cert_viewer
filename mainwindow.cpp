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

MainWindow::MainWindow(BaseObjectType* base,
        const Glib::RefPtr<Gtk::Builder>& b): Gtk::Window(base), builder(b),
        openFile(nullptr), saveFile(nullptr), saveAsFile(nullptr),
        about(nullptr), aboutDlg(nullptr)
{
    getWidgets();
    connectSignals();
}

MainWindow::~MainWindow()
{

}

void MainWindow::getWidgets()
{
    builder->get_widget("open_button", openFile);
    builder->get_widget("save_button", saveFile);
    builder->get_widget("save_as_button", saveAsFile);
    builder->get_widget("about_button", about);
    builder->get_widget("aboutdialog", aboutDlg);
}

void MainWindow::connectSignals()
{
    if(openFile)
        openFile->signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::openBtnClicked));

    if(about)
        about->signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::aboutBtnClicked));

    if(aboutDlg)
        aboutDlg->signal_response().connect(sigc::mem_fun(*this,
            &MainWindow::aboutDialogResponse));
}

void MainWindow::openBtnClicked()
{
    std::cout << "Open Clicked from class!" << std::endl;
}

void MainWindow::aboutBtnClicked()
{
    if(aboutDlg)
        aboutDlg->show();
}

void MainWindow::aboutDialogResponse(int responseId)
{
    aboutDlg->hide();
}
