#ifndef SPEAK_H
#define SPEAK_H

#include "conf.h"
#include <iostream>
#include <string>
#include <string>
using namespace std; 



class Speaker : public Conf{
    public:
    Speaker();
    ~Speaker() override; 
    void set_name(const string& name);
    void set_vuz(const string& vuz);
    void set_report(const string& report);
    void set_annotacion(const string& annotacion);

    string get_name() const;
    string get_vuz()const;
    string get_report()const;
    string grt_annotacion()const;

    private:
        string  name;
        string vuz;
        string report;
        string annotacion;

}
#endif