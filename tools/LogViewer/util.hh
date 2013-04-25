#ifndef UTIL_HH
#define UTIL_HH

#include <QString>

class Static {
private:
    Static(void);
    Static(const Static&);
    Static& operator=(const Static&);
};

class Util : private Static
{
public:

    static QString shortFilename(const QString& longName, int max = 20);

    template <typename T>
    static void deletePtr(T*& pointer_)
    {
        if (pointer_ == 0) return;
        if (pointer_ != 0) {
            delete pointer_;
            pointer_ = 0;
        }
    }

};

#endif // UTIL_HH
