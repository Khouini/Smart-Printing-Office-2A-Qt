#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QSystemTrayIcon>
#include <QString>
class notifications
{
public:
    notifications();
    notifications(int, QString);
    void notificationsComptes();
private:
    int operationInt;
    QString Nom;
};

#endif // NOTIFICATIONS_H
