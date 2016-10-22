#Cert Viewer
Gtk+3 based application for viewing SSL/TLS certificates (At the present stage it's not yet functional).

##Library dependencies
- gtkmm-3.0
- openssl 1.0.2

##Building on systems with gcc
Create a directory named **build/** in the project's parent directory and execute:
```
cd build/
cmake ..
make
```

##Running
The executable must be run from the paroject's parent directory that contains the
**ui/** directory with glade files. Assuming that the project was build according to the instructions above, simply run:
```
build/certviewer
```
