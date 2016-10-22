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

#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/bn.h>

Certificate::Certificate(const std::string& file): cert(nullptr)
{
    FILE* f = std::fopen(file.c_str(), "r");
    if(f == nullptr)
        throw std::runtime_error("Error while opening file");

    if(!PEM_read_X509(f, &cert, nullptr, nullptr))
        throw std::runtime_error("Certificate reading failed");

    readCertificateData(cert);
}

Certificate::Certificate(X509* c): cert(c)
{
    cert = X509_dup(c);
}

Certificate::~Certificate()
{
    X509_free(cert);
}

void Certificate::readCertificateData(X509* x)
{
    readSubject(x);
    readIssuer(x);
    readVersion(x);
    readSerial(x);
    readDates(x);
    readCA(x);
    readSignatureAlgorithm(x);
    readPublicKey(x);
}

void Certificate::readSubject(X509* x)
{
    BUF_MEM* buffer = nullptr;

    BIO* memBio = BIO_new(BIO_s_mem());
    int numRead = X509_NAME_print_ex(memBio, X509_get_subject_name(x),
           0, XN_FLAG_ONELINE);
    if(numRead > 0)
        BIO_get_mem_ptr(memBio, &buffer);

    subject.assign(buffer->data, buffer->length);
    BIO_free(memBio);
}

void Certificate::readIssuer(X509* x)
{
    BUF_MEM* buffer = nullptr;

    BIO* memBio = BIO_new(BIO_s_mem());
    int numRead = X509_NAME_print_ex(memBio, X509_get_issuer_name(x),
           0, XN_FLAG_ONELINE);
    if(numRead > 0)
        BIO_get_mem_ptr(memBio, &buffer);

    issuer.assign(buffer->data, buffer->length);
    BIO_free(memBio);
}

void Certificate::readVersion(X509* x)
{
    version = std::to_string(X509_get_version(x) + 1);
}

void Certificate::readSerial(X509* x)
{
    ASN1_INTEGER* s = X509_get_serialNumber(x);
    BIGNUM* bn = ASN1_INTEGER_to_BN(s, nullptr);
    char* hexStr = BN_bn2hex(bn);
    serial.assign(hexStr);

    OPENSSL_free(hexStr);
}

void Certificate::readDates(X509* x)
{
    BUF_MEM* buffer = nullptr;
    ASN1_TIME* nb = X509_get_notBefore(x);
    ASN1_TIME* na = X509_get_notAfter(x);

    BIO* memBio = BIO_new(BIO_s_mem());
    if(nb)
    {
        int br = ASN1_TIME_print(memBio, nb);
        if(br == 1)
        {
            BIO_get_mem_ptr(memBio, &buffer);
            notBefore.assign(buffer->data, buffer->length);
        }
    }

    int bret = BIO_reset(memBio);
    if(bret && na)
    {
        int br = ASN1_TIME_print(memBio, na);
        if(br == 1)
        {
            BIO_get_mem_ptr(memBio, &buffer);
            notAfter.assign(buffer->data, buffer->length);
        }
    }
    BIO_free(memBio);
}

void Certificate::readCA(X509* x)
{
    isCA = (X509_check_ca(x) != 0);
}

void Certificate::readSignatureAlgorithm(X509* x)
{
    BUF_MEM* buffer = nullptr;

    BIO* memBio = BIO_new(BIO_s_mem());
    EVP_PKEY* pkey = X509_get_pubkey(x);
    if(pkey)
    {
        X509_ALGOR *sigAlg = nullptr;
	ASN1_BIT_STRING* sig = nullptr;
	X509_get0_signature(&sig, &sigAlg, x);
        if(sigAlg)
        {
            i2a_ASN1_OBJECT(memBio, sigAlg->algorithm);
            BIO_get_mem_ptr(memBio, &buffer);
            signatureAlgorithm.assign(buffer->data, buffer->length);
        }
    }

    EVP_PKEY_free(pkey);
    BIO_free(memBio);
}

void Certificate::readPublicKey(X509* x)
{
    EVP_PKEY* pkey = X509_get_pubkey(x);
    if(pkey)
	publicKey.assign(BN_bn2hex(pkey->pkey.rsa->n));
}
