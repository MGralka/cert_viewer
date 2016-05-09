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
#ifndef CERTIFICATE_HPP
#define CERTIFICATE_HPP

#include <string>

typedef struct x509_st X509;

class Certificate
{
public:
    explicit Certificate(const std::string& file);
    Certificate(X509* x);
    ~Certificate();

    std::string getSubject() const {return subject;}
    std::string getIssuer() const {return issuer;}
    std::string getVersion() const {return version;}
    std::string getSerial() const {return serial;}

protected:
    void readCertificateData(X509* x);
    void readSubject(X509* x);
    void readIssuer(X509* x);
    void readVersion(X509* x);
    void readSerial(X509* x);

    std::string subject;
    std::string issuer;
    std::string version;
    std::string serial;

    X509* cert;
};

#endif

