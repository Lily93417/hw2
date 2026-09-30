#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty,
                   const std::string size, const std::string brand)
    : Product("clothing", name, price, qty),
      size_(size),
      brand_(brand)
{
}

set<string> Clothing::keywords() const
{
    set<string> keywords;

    set<string> nameWords = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);

    keywords.insert(nameWords.begin(), nameWords.end());
    keywords.insert(brandWords.begin(), brandWords.end());

    return keywords;
}

string Clothing::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Size: " << size_ << " Brand: " << brand_ << endl;
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    Product::dump(os);
    os << size_ << endl;
    os << brand_ << endl;
}