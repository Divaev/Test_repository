#include <QCoreApplication>

#include <iostream>

#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include <functional>


class MyClass {
    int val;

public:
    MyClass(int v);
    MyClass& square();

    friend std::ostream& operator<<(std::ostream&, const MyClass&);

    static int sumFunc(const int&, const int&);
    int difFunc(const int&, const int&);

    int (*fPtr)(const int&, const int&);
};

class DerivedClass: public MyClass {
public:
    int (MyClass::*fPtr)(const int&,  const int&);
    DerivedClass(int v);
    void setFuncPtr(int (MyClass::*)(const int&, const int&));
};


int (*tripleSumPtr)(const int&, const int&, const int&);


int tripleSum(const int&, const int&, const int&);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::deque<MyClass> myDeque;

    for(int i = 0; i < 10; i++)
        myDeque.push_back(i * 10);

    std::cout << "Source deque:" << std::endl;

    copy(myDeque.begin(), myDeque.end(), std::ostream_iterator<MyClass>(std::cout, "\n"));



    transform(myDeque.begin(), myDeque.end(), myDeque.begin(), std::mem_fun_ref(&MyClass::square));


    std::cout << "Result deque:" << std::endl;

    copy(myDeque.begin(), myDeque.end(), std::ostream_iterator<MyClass>(std::cout, "\n"));

    std::cout << "Static function out:" << std::endl;
    std::cout << MyClass::sumFunc(5, 10) << std::endl;

    int (MyClass::*funcPtr)(const int&, const int&);                //указатель на метода
    funcPtr = &MyClass::difFunc;                                    //для того, чтобы инициализировать указатель на метод методом класса, необходимо использовать операцию взятия адреса
   // funcPtr = MyClass::sumFunc;

    MyClass myObj(13);
    MyClass* myObjPtr = &myObj;

    std::cout << "Pointer to method test:" << std::endl;
    std::cout << (myObjPtr->*funcPtr)(15, 12) << std::endl;                 //при помощи оператора ->* разыменовываем указатель на метод

    std::cout << (myObj.*funcPtr)(20, 11) << std::endl;                     //при помощи оператора .* разыменовываем указатель на  метод
    std::cout << "----------------------------------------" << std::endl;

    //myObj.fPtr = &MyClass::difFunc;

    DerivedClass dObj(33);

    dObj.setFuncPtr(funcPtr);


    tripleSumPtr = tripleSum;

    std::cout << (*tripleSumPtr)(10, 25, 30) << std::endl;


    std::cout << tripleSum(11, 12, 13) << std::endl;


  //  std::cout << myObj.funcPtr(20, 22) << std::endl;
 //  std::cout << dObj.fPtr(10, 22) << std::endl;

    std::vector<std::string> wordsVec = {"Once", "upon", "a", "time"};

    std::vector<int> wordsSizes;

    transform(wordsVec.begin(), wordsVec.end(), std::back_inserter(wordsSizes), std::mem_fun_ref(&std::string::size));

    std::cout << "Words sizes:" << std::endl;
    for(const auto& wordSize: wordsSizes)
        std::cout << wordSize << std::endl;

    return a.exec();
}


MyClass::MyClass(int v) : val(v) {

}


MyClass& MyClass::square() {
    val *= val;
    return *this;
}


std::ostream& operator<<(std::ostream& outStream,  const MyClass& myObj) {
    outStream << myObj.val;
    return outStream;

}

int MyClass::sumFunc(const int& x, const int& y) {
    return x + y;
}


int MyClass::difFunc(const int& x, const int& y) {
    return x - y;
}

DerivedClass::DerivedClass(int v) : MyClass(v) {

}

void DerivedClass::setFuncPtr(int (MyClass::*locFuncPtr)(const int &, const int &)) {
    fPtr = locFuncPtr;
}



int tripleSum(const int& x, const int& y, const int& z) {
    return x + y + z;
}



