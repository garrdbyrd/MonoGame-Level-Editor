#ifndef UTILITY_H
#define UTILITY_H

#include <QList>
#include <QString>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string &str, char delim);
QList<QString> splitString(const QString str, char delim);

#endif // UTILITY_H
