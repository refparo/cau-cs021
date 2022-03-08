#include <iostream>

using namespace std;

class Invoice {
  string num, desc;
  int quant, price;
public:
  Invoice(
    string partNumber, string PartDescription,
    int quantity, int pricePerItem) {
    num = partNumber;
    desc = PartDescription;
    quant = quantity;
    price = pricePerItem;
  }
  string getPartNumber() const { return num; }
  void setPartNumber(string partNumber) { num = partNumber; }
  string getPartDescription() const { return desc; }
  void setPartDescription(string partDescription) { desc = partDescription; }
  int getQuantity() const { return quant; }
  void setQuantity(int quantity) {
    if (quantity < 0) {
      cout << "\nquantity cannot be negative. quantity set to 0.\n";
      quant = 0;
    } else quant = quantity;
  }
  int getPricePerItem() const { return price; }
  void setPricePerItem(int pricePerItem) {
    if (pricePerItem < 0) {
      cout << "\nprice per item cannot be negative. price per item set to 0.\n";
      price = 0;
    } else price = pricePerItem;
  }

  int getInvoiceAmount() const { return quant * price; }
};

//StudybarCommentBegin
int main() {
  Invoice invoice("12345", "Hammer", 100, 5);

  cout << "Part number: " << invoice.getPartNumber() << endl;
  cout << "Part description: " << invoice.getPartDescription() << endl;
  cout << "Quantity: " << invoice.getQuantity() << endl;
  cout << "Price per item: $" << invoice.getPricePerItem() << endl;
  cout << "Invoice amount: $" << invoice.getInvoiceAmount() << endl;

  invoice.setPartNumber("123456");
  invoice.setPartDescription("Saw");
  invoice.setQuantity(-5);
  invoice.setPricePerItem(10);
  cout << "\nInvoice data members modified.\n";

  cout << "Part number: " << invoice.getPartNumber() << endl;
  cout << "Part description: " << invoice.getPartDescription() << endl;
  cout << "Quantity: " << invoice.getQuantity() << endl;
  cout << "Price per item: $" << invoice.getPricePerItem() << endl;
  cout << "Invoice amount: $" << invoice.getInvoiceAmount() << endl;
  return 0;
}
//StudybarCommentEnd
