#ifndef SPEAK_H
#define SPEAK_H

#include "conf.h"


class Speaker : public Conf{
    public:
    Speaker();
    ~Speaker() ;
    Speaker(const QString& name, const QString& vuz, const QString& report, const QString& annotacion);



    void set_vuz(const QString& vuz);
    void set_report(const QString& report);
    void set_annotacion(const QString& annotacion);


    QString get_vuz()const;
    QString get_report()const;
    QString get_annotacion()const;

    QString toString() const override;
    QString getType() const override { return "SPEAKER"; }


    private:
        QString organization;
        QString reportT;
        QString annotationT;

};
#endif
