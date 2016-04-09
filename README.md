# Cert Viewer
Gtk+3 based application for viewing SSL/TLS certificates (At the present stage it's not yet functional).

##Building
g++ --std=c++11 main.cpp -o bin/certview \`pkg-config gtkmm-3.0 --cflags --libs\`
