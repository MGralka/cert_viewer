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
#include "certificate.hpp"

#include <iostream>
#include <stdexcept>

#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

Certificate::Certificate(const std::string& file): cert(nullptr)
{
    FILE* f = std::fopen(file.c_str(), "r");
    if(f == nullptr)
        throw std::runtime_error("error while opening file");

    if(!PEM_read_X509(f, &cert, nullptr, nullptr))
        throw std::runtime_error("certificate reading failed");

    readCertificateData(cert);
}

Certificate::Certificate(X509* c): cert(c)
{
}

Certificate::~Certificate()
{

}

void Certificate::readCertificateData(X509* x)
{
    BUF_MEM* buffer = nullptr;

    BIO* memBio = BIO_new(BIO_s_mem());
    //Don't free the buffer when freeing the BIO
    int ret = BIO_set_close(memBio, BIO_NOCLOSE);
    int numRead = X509_NAME_print_ex(memBio, X509_get_subject_name(x),
           0, XN_FLAG_ONELINE);
    if(ret && numRead > 0)
        BIO_get_mem_ptr(memBio, &buffer);

    std::string subject(buffer->data);
    BIO_free(memBio);

    std::cout << "Subject: " << subject << std::endl;
}
