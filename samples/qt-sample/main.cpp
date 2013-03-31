/**
 * This file is part of EasyLogging++ samples
 * Demonstration of multithreaded application in C++ (Qt)
 *
 * Compile this program using Qt
 *    qmake qt-sample.pro && make
 *
 * Revision: 1.1
 * @author mkhan3189
 */

#include "mythread.h"
#include "../../easylogging++.h"

_INITIALIZE_EASYLOGGINGPP
class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};


int main(int argc, char* argv[]) {
    _START_EASYLOGGINGPP(argc, argv)

    bool runThreads = true;

    if (runThreads) {
        for (int i = 1; i <= 1; ++i) {
            MyThread t(i);
            t.start();
            t.wait();
        }
    }
/*
    QVector<QString> stringList;
    stringList.push_back (QString("Test"));
    stringList.push_back (QString("Test 2"));
    LINFO << stringList;

    LVERBOSE(1) << "Verbose 1 ...";

    SDEBUG << "This is security logger for debug";

    BINFO << "This is a business logger";


    std::map<int, std::string> map_;
    map_.insert (std::pair<int, std::string>(1, "one"));
    map_.insert (std::pair<int, std::string>(2, "two"));
    LINFO << "Map: " << map_;


    QPair<QString, int> pair_;
    pair_.first = "test";
    pair_.second = 2;
    LINFO << pair_;

    QMap<QString, int> qmap_;
    qmap_.insert ("john", 100);
    qmap_.insert ("michael", 101);
    LINFO << qmap_;

    QMultiMap<QString, int> qmmap_;
    qmmap_.insert ("john", 100);
    qmmap_.insert ("michael", 101);
    LINFO << qmmap_;

    QSet<QString> set_;
    set_.insert ("test");
    set_.insert ("second");
    LINFO << set_;

    QVector<QString*> ptrList;
    ptrList.push_back (new QString("Test"));
    LINFO << ptrList;
    qDeleteAll(ptrList);

    QHash<QString, QString> hash_;
    hash_.insert ("john", "101fa");
    hash_.insert ("michael", "102mf");
    LINFO << hash_;

    QLinkedList<QString> llist_;
    llist_.push_back ("test");
    llist_.push_back ("test 2");
    LINFO << llist_ ;
*/
    std::queue<int> queue_;
    queue_.push(77);
    queue_.push(16);
    LINFO << queue_;

    std::bitset<10> bitset_ (std::string("100"));
    LINFO << bitset_;


    int myints[]= {10,60,50,20};

      std::priority_queue<int> first;
      std::priority_queue<int> second (myints,myints+4);
      std::priority_queue< int, std::vector<int>, std::greater<int> > third (myints,myints+4);
      LINFO << third;
      // using mycomparison:
      std::priority_queue< int, std::vector<int>, mycomparison > fourth(myints,myints+4);
      typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;
        mypq_type fifth (mycomparison());
        mypq_type sixth (mycomparison(true));
      LINFO << fourth;

      std::deque<int> mydeque_ (3,100);
      mydeque_.at(1) = 200;
      std::stack<int> stack_ (mydeque_);
      LINFO << stack_;
    return 0;

}
