
#ifndef PROGRAM_H
#define PROGRAM_H


#include "conf.h"

class Program  : public Conf {
public:
     Program();
    ~Program();


     QString get_day() const;
     QString get_time() const;

     void set_day(const QString& day);
     void set_time(const QString& time);


     QString toString() const override;
     QString getType() const override { return "PROGRAM"; }



private:
    QString dayT;
    QString timeT;

};
#endif
