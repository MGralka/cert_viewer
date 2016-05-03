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

#include <stdexcept>

#include <openssl/x509.h>
#include <openssl/pem.h>

Certificate::Certificate(const std::string& file): cert(nullptr)
{
FILE* f = std::fopen(file.c_str(), "r");
if(!PEM_read_X509(f, &cert, nullptr, nullptr))
	throw std::runtime_error("certificate reading failed");
}

Certificate::Certificate(X509* c): cert(c)
{
}

Certificate::~Certificate()
{

}
