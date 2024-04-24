#include "utility.h"
#include <QList>
#include <QString>
#include <sstream>

std::vector<std::string> splitString(const std::string &str, char delim) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (!item.empty()) {
      tokens.push_back(item);
    }
  }
  return tokens;
}

QList<QString> splitString(const QString str, char delim) {
  QList<QString> tokens;
  QString delimiter = QString(delim);
  int startIndex = 0;
  int endIndex = 0;

  while ((endIndex = str.indexOf(delimiter, startIndex)) != -1) {
    QString token = str.mid(startIndex, endIndex - startIndex);
    if (!token.isEmpty()) {
      tokens.append(token);
    }
    startIndex = endIndex + 1;
  }

  QString lastToken = str.mid(startIndex);
  if (!lastToken.isEmpty()) {
    tokens.append(lastToken);
  }

  return tokens;
}
