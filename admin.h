#ifndef ADMIN_H
#define ADMIN_H


#include "conf.h"


class Admin : public Conf {
    public:
        Admin();
        ~Admin();

        QString toString() const override;
        QString getType() const override { return "ADMIN"; }


        QString get_position() const;
        QString get_responsibility() const;

        void set_position(const QString& position);
        void set_responsibility(const QString& responsibility);
    private:
        QString positionT;
        QString responsibilityT;
};
#endif
