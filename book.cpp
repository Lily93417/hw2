#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string name, double price, int qty,
           const std::string isbn, const std::string author)
    : Product("book", name, price, qty),
      isbn_(isbn),
      author_(author)
{
}

set<string> Book::keywords() const
{
    set<string> keywords;

    set<string> nameWords = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);

    keywords.insert(nameWords.begin(), nameWords.end());
    keywords.insert(authorWords.begin(), authorWords.end());

    keywords.insert(convToLower(isbn_));

    return keywords;
}

string Book::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}