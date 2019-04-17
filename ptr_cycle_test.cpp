#include <iostream>
#include <memory>

// 原始指针实现

// class Child;
// class Parent;

// class Parent {
// private:
//     Child* myChild;
// public:
//     void setChild(Child* ch) {
//         this->myChild = ch;
//     }

//     void doSomething() {
//         if (this->myChild) {

//         }
//     }

//     ~Parent() {
//         delete myChild;
//     }
// };

// class Child {
// private:
//     Parent* myParent;
// public:
//     void setPartent(Parent* p) {
//         this->myParent = p;
//     }
//     void doSomething() {
//         if (this->myParent) {

//         }
//     }
//     ~Child() {
//         delete myParent;
//     }
// };

// int main() {
//     {
//         Parent* p = new Parent;
//         Child* c =  new Child;
//         p->setChild(c);
//         c->setPartent(p);
//         delete c;  //only delete one
//     }
//     return 0;
// }


// share_ptr 实现

// class Child;
// class Parent;

// class Parent {
// private:
//     std::shared_ptr<Child> ChildPtr;
// public:
//     void setChild(std::shared_ptr<Child> child) {
//         this->ChildPtr = child;
//     }

//     void doSomething() {
//         if (this->ChildPtr.use_count()) {

//         }
//     }

//     ~Parent() {
//     }
// };

// class Child {
// private:
//     std::shared_ptr<Parent> ParentPtr;
// public:
//     void setPartent(std::shared_ptr<Parent> parent) {
//         this->ParentPtr = parent;
//     }
//     void doSomething() {
//         if (this->ParentPtr.use_count()) {

//         }
//     }
//     ~Child() {
//     }
// };

// int main() {
//     std::weak_ptr<Parent> wpp;
//     std::weak_ptr<Child> wpc;
//     {
//         std::shared_ptr<Parent> p(new Parent);
//         std::shared_ptr<Child> c(new Child);
//         p->setChild(c);
//         c->setPartent(p);
//         wpp = p;
//         wpc = c;
//         std::cout << p.use_count() << std::endl; // 2
//         std::cout << c.use_count() << std::endl; // 2
//     }
//     std::cout << wpp.use_count() << std::endl;  // 1
//     std::cout << wpc.use_count() << std::endl;  // 1
//     return 0;
// }

#include <iostream>
#include <memory>

class Child;
class Parent;

class Parent {
private:
    //std::shared_ptr<Child> ChildPtr;
    std::weak_ptr<Child> ChildPtr;
public:
    void setChild(std::shared_ptr<Child> child) {
        this->ChildPtr = child;
    }

    void doSomething() {
        //new shared_ptr
        if (this->ChildPtr.lock()) {

        }
    }

    ~Parent() {
    }
};

class Child {
private:
    std::shared_ptr<Parent> ParentPtr;
public:
    void setPartent(std::shared_ptr<Parent> parent) {
        this->ParentPtr = parent;
    }
    void doSomething() {
        if (this->ParentPtr.use_count()) {

        }
    }
    ~Child() {
    }
};

int main() {
    std::weak_ptr<Parent> wpp;
    std::weak_ptr<Child> wpc;
    {
        std::shared_ptr<Parent> p(new Parent);
        std::shared_ptr<Child> c(new Child);
        p->setChild(c);
        c->setPartent(p);
        wpp = p;
        wpc = c;
        std::cout << p.use_count() << std::endl; // 2
        std::cout << c.use_count() << std::endl; // 1
    }
    std::cout << wpp.use_count() << std::endl;  // 0
    std::cout << wpc.use_count() << std::endl;  // 0
    return 0;
}
