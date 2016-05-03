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

#include "certificate.hpp"

#include <iostream>

MainWindow::MainWindow(BaseObjectType* base,
        const Glib::RefPtr<Gtk::Builder>& b): Gtk::Window(base), builder(b),
        openFile(nullptr), saveAsFile(nullptr),
        about(nullptr), aboutDlg(nullptr), fileChooserDlg(nullptr)
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
    builder->get_widget("save_as_button", saveAsFile);
    builder->get_widget("about_button", about);
    builder->get_widget("aboutdialog", aboutDlg);
    builder->get_widget("filechooserdialog", fileChooserDlg);
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

    if(fileChooserDlg)
    {
        fileChooserDlg->add_button("Anuluj", Gtk::RESPONSE_CANCEL);
        fileChooserDlg->add_button("OK", Gtk::RESPONSE_OK);
        fileChooserDlg->signal_response().connect(sigc::mem_fun(*this,
            &MainWindow::fileChooserResponse));
        addFilters(fileChooserDlg);
    }
}

void MainWindow::addFilters(Gtk::FileChooserDialog* d)
{
    auto certFilter = Gtk::FileFilter::create();
    certFilter->set_name("Plik certyfikatu");
    certFilter->add_pattern("*.pem");
    certFilter->add_pattern("*.crt");
    certFilter->add_pattern("*.cer");
    certFilter->add_pattern("*.der");

    auto crlFilter = Gtk::FileFilter::create();
    crlFilter->set_name("Plik CRL");
    crlFilter->add_pattern("*.crl");

    auto allFilesFilter = Gtk::FileFilter::create();
    allFilesFilter->set_name("Wszystkie pliki");
    allFilesFilter->add_pattern("*");

    d->add_filter(certFilter);
    d->add_filter(crlFilter);
    d->add_filter(allFilesFilter);
}

void MainWindow::openBtnClicked()
{
    if(fileChooserDlg)
        fileChooserDlg->show();
}

void MainWindow::aboutBtnClicked()
{
    if(aboutDlg)
        aboutDlg->show();
}

void MainWindow::aboutDialogResponse(int responseId)
{
    switch(responseId)
    {
        default:
            aboutDlg->hide();
            break;
    }
}

void MainWindow::fileChooserResponse(int responseId)
{
    fileChooserDlg->hide();
    switch(responseId)
    {
        case Gtk::RESPONSE_OK:
            std::cout << "Chosen file: " << fileChooserDlg->get_filename() << std::endl;
        break;
        case Gtk::RESPONSE_CANCEL:
        break;
        default:
        break;
    }
    Certificate c(fileChooserDlg->get_filename());
}
