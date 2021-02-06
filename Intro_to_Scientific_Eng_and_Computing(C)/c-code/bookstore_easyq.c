#include <stdio.h>
#include <math.h>

#define SHIPPING_CHARGE_PER_UNIT 2
double get_price_of_an_order(double total_price, int number_of_the_books);

int main(int argc, char const *argv[])
{
    double total_price = 0;
    int number_of_the_books = 0;

    printf("Enter total price: ");
    scanf("%lf", &total_price);
    printf("Enter number of the books: ");
    scanf("%d", &number_of_the_books);
    
    double price = get_price_of_an_order(total_price, number_of_the_books);
    printf("Price is %lf \n", price);
    return 0;
}


double get_price_of_an_order(double total_price, int number_of_the_books)
{
    double price = 0;
    double tax = total_price * (7.5 / 100.0);
    double shipping_charge = number_of_the_books * SHIPPING_CHARGE_PER_UNIT;
    price = total_price + tax + shipping_charge;
    return price;
}