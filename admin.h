#ifndef CONF_H
#define CONF_H


#include "conf.h"


class Admin : public Conf{
    public:
        Admin();
        ~Admin();
        Admin(const QString& name, const QString& position, const QString& responsibility);
        Admin(const Adminr& other);

        void display() const override;

        QString get_position() const;
        QString get_responsibility() const;

        void set_position(const QString& position);
        void set_responsibility(const QString& responsibility);
    private:
        // string fullName;
        QString position;
        QString responsibility;
};
#endif
