
#include "util.hh"

QString Util::shortFilename(const QString &longName, int max)
{
    QString result = longName.trimmed();
    if (result.length() > max) {
        result = "..." + result.right(max - 3);
    }
    return result;
}

