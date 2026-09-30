#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for (vector<Product*>::iterator it = products_.begin();
         it != products_.end(); ++it) {
        delete *it;
    }

    for (vector<User*>::iterator it = users_.begin();
         it != users_.end(); ++it) {
        delete *it;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> words = p->keywords();

    for (set<string>::iterator it = words.begin();
         it != words.end(); ++it) {

        keywordMap_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
}

User* MyDataStore::getUser(string username)
{
    string searchName = convToLower(username);

    for (vector<User*>::iterator it = users_.begin();
         it != users_.end(); ++it) {

        if (convToLower((*it)->getName()) == searchName) {
            return *it;
        }
    }

    return NULL;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> results;

    if (terms.size() == 0) {
        return results;
    }

    set<Product*> resultSet;

    if (type == 0) {
        // AND search

        map<string, set<Product*> >::iterator first =
            keywordMap_.find(convToLower(terms[0]));

        if (first == keywordMap_.end()) {
            return results;
        }

        resultSet = first->second;

        for (unsigned int i = 1; i < terms.size(); i++) {

            map<string, set<Product*> >::iterator found =
                keywordMap_.find(convToLower(terms[i]));

            if (found == keywordMap_.end()) {
                resultSet.clear();
                break;
            }

            resultSet =
                setIntersection(resultSet, found->second);
        }
    }
    else {
        // OR search

        for (unsigned int i = 0; i < terms.size(); i++) {

            map<string, set<Product*> >::iterator found =
                keywordMap_.find(convToLower(terms[i]));

            if (found != keywordMap_.end()) {
                resultSet =
                    setUnion(resultSet, found->second);
            }
        }
    }

    for (set<Product*>::iterator it = resultSet.begin();
         it != resultSet.end(); ++it) {
        results.push_back(*it);
    }

    return results;
}

void MyDataStore::addToCart(string username, Product* product)
{
    carts_[convToLower(username)].push_back(product);
}

vector<Product*> MyDataStore::getCart(string username)
{
    string name = convToLower(username);

    map<string, vector<Product*> >::iterator it =
        carts_.find(name);

    if (it == carts_.end()) {
        return vector<Product*>();
    }

    return it->second;
}

void MyDataStore::buyCart(string username)
{
    string name = convToLower(username);

    User* user = getUser(username);

    if (user == NULL) {
        return;
    }

    map<string, vector<Product*> >::iterator cartIt =
        carts_.find(name);

    if (cartIt == carts_.end()) {
        return;
    }

    vector<Product*>& cart = cartIt->second;
    vector<Product*> remaining;

    for (vector<Product*>::iterator it = cart.begin();
         it != cart.end(); ++it) {

        Product* product = *it;

        if (product->getQty() > 0 &&
            user->getBalance() >= product->getPrice()) {

            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        }
        else {
            remaining.push_back(product);
        }
    }

    cart = remaining;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (vector<Product*>::iterator it = products_.begin();
         it != products_.end(); ++it) {

        (*it)->dump(ofile);
    }

    ofile << "</products>" << endl;
    ofile << "<users>" << endl;

    for (vector<User*>::iterator it = users_.begin();
         it != users_.end(); ++it) {

        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}