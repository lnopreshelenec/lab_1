
#ifndef PROGRAM_H
#define PROGRAM_H


#include "conf.h"

class Program  : public Conf {
public:
     Program();
    ~Program();

     void display() const override;

     QString get_day() const;
     QString get_time() const;

     void set_day(const QString& day);
     void set_time(const QString& time);

private:
    QString dayT;
    QString timeT;

};
#endif
