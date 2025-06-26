#include "BinarySearchTree.hpp"

int main()
{
    BinarySearchTree<int> bst;

    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(6);
    bst.insert(14);
    bst.insert(4);
    bst.insert(7);
    bst.insert(13);

    std::cout << "tree size: " << bst.size() << std::endl;

    bst.printInOrder();
    bst.printPostOrder();
    bst.printPreOrder();

    std::cout << "-------- removing 3 --------" << std::endl;
    bst.remove(3);
    std::cout << "tree size: " << bst.size() << std::endl;
    bst.printInOrder();
    bst.printPostOrder();
    bst.printPreOrder();

    std::cout << "-------- removing 14 --------" << std::endl;
    bst.remove(14);
    std::cout << "tree size: " << bst.size() << std::endl;
    bst.printInOrder();
    bst.printPostOrder();
    bst.printPreOrder();

    std::cout << "-------- removing 8 --------" << std::endl;
    bst.remove(8);
    std::cout << "tree size: " << bst.size() << std::endl;
    bst.printInOrder();
    bst.printPostOrder();
    bst.printPreOrder();

    return 0;
}