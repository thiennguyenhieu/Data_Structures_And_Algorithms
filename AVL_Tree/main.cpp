#include "AVLTree.hpp"

int main()
{
    auto avlTree = new AVLTree<int>();
    avlTree->insert(25);
    avlTree->insert(5);
    avlTree->insert(10);
    avlTree->insert(0);
    avlTree->insert(6);
    avlTree->insert(11);
    avlTree->insert(-1);
    avlTree->insert(1);
    avlTree->insert(2);

    std::cout << "tree size "<< avlTree->size() << std::endl;

    avlTree->printInOrder();
    avlTree->printPostOrder();
    avlTree->printPreOrder();

    std::cout << "-------- removing 10 --------"<< std::endl;
    avlTree->remove(10);
    std::cout << "tree size "<< avlTree->size() << std::endl;
    avlTree->printInOrder();
    avlTree->printPostOrder();
    avlTree->printPreOrder();

        std::cout << "-------- removing 1 --------"<< std::endl;
    avlTree->remove(1);
    std::cout << "tree size "<< avlTree->size() << std::endl;
    avlTree->printInOrder();
    avlTree->printPostOrder();
    avlTree->printPreOrder();

    delete avlTree;

    return 0;
}