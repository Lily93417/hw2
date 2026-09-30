#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    virtual void addProduct(Product* p);
    virtual void addUser(User* u);

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    virtual void dump(std::ostream& ofile);

    void addToCart(std::string username, Product* product);
    std::vector<Product*> getCart(std::string username);
    void buyCart(std::string username);

    User* getUser(std::string username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;

    std::map<std::string, std::set<Product*> > keywordMap_;

    std::map<std::string, std::vector<Product*> > carts_;
};

#endif