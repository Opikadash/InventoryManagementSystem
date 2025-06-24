#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    int id;
    std::string name;
    int quantity;
    double price;
    std::string category;

public:
    Item(int id, std::string name, int quantity, double price, std::string category);
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::string getCategory() const { return category; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double pr) { price = pr; }
    void setCategory(std::string cat) { category = cat; }
};

#endif

