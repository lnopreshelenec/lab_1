#ifndef CONF_H
#define CONF_H

#include <QString>



class Conf{
    public:
        Conf();
        ~Conf();

        // virtual void display(int index) const = 0;
        virtual QString toString() const = 0;
         virtual QString getType() const = 0;

        QString get_name() const;
        void set_name(const QString& name);

    protected:
        QString nameT;

};
#endif
