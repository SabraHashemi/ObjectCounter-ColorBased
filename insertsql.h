#ifndef INSERTSQL
#define INSERTSQL
#include "QThread"
class insertsql : public QThread
{
    Q_OBJECT
public:
    explicit insertsql();
    void run();
private:



private slots:

    //void agefinished(int face_num, int age);
};
#endif // INSERTSQL

