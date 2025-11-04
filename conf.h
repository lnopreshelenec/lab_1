#ifndef CONF_H
#define CONF_H

#include <QString>
// #include <QTextStream>


class Conf{
    public:
        Conf();
        // Conf(const QString& name);
        // Conf(const QString& other);
        ~Conf();

        virtual void display() const = 0;
        virtual QString toString() const = 0;
        // virtual Conf* clone() const = 0;

        QString get_name() const;
        void set_name(const QString& name);

    protected:
        QString nameT;
    private:

};
#endif
