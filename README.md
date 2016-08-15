#Cert Viewer
Gtk+3 based application for viewing SSL/TLS certificates (At the present stage it's not yet functional).

##Library dependencies
- gtkmm-3.0
- openssl

##Building on systems with gcc
Go to the build directory and execute:
```
cmake ..
make
```

##Running
The executable must be run from the paroject's parent directory that contains the
**ui/** directory with glade files:
```
build/certviewer
```
