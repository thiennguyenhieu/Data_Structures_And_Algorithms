#include "LinkedList.hpp"

int main()
{
    LinkedList<int> list;

    list.push(2);
    list.push(-5);
    list.append(8);
    list.append(12);
    list.append(9);
    list.append(6);
    list.append(1);

    std::cout << "list size: " << list.size() << std::endl;
    list.print();

    std::cout << "---reverse---" << std::endl;
    list.reverse();
    list.print();

    list.removeByPos(7); // out-of-range test
    list.removeByPos(8); // out-of-range test

    std::cout << "---remove first ---" << std::endl;
    list.removeByPos(0);
    std::cout << "list size: " << list.size() << std::endl;
    list.print();

    std::cout << "---remove 3rd index ---" << std::endl;
    list.removeByPos(3);
    std::cout << "list size: " << list.size() << std::endl;
    list.print();

    std::cout << "---remove last ---" << std::endl;
    list.removeByPos(list.size() - 1);
    std::cout << "list size: " << list.size() << std::endl;
    list.print();

    return 0;
}